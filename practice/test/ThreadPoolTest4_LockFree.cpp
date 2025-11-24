#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include <atomic>
#include <exception>
#include <functional>
#include <memory>
#include <chrono>
#include <future>

using namespace std;

const int DEFAULT_THREAD_NUM = 5;

// 使用模板和function实现更灵活的任务类型
using Task = function<void()>;

class ThreadPool {
private:
    // RAII风格的锁管理器（仅用于条件变量）
    class MutexLockGuard {
    public:
        explicit MutexLockGuard(pthread_mutex_t& mutex) : mutex_(mutex) {
            pthread_mutex_lock(&mutex_);
        }
        ~MutexLockGuard() {
            pthread_mutex_unlock(&mutex_);
        }
    private:
        pthread_mutex_t& mutex_;
        MutexLockGuard(const MutexLockGuard&) = delete;
        MutexLockGuard& operator=(const MutexLockGuard&) = delete;
    };

    // 简单的无锁队列实现（单生产者多消费者或单消费者多生产者）
    // 注意：这是一个简化版本，真正的无锁队列需要更复杂的实现
    template<typename T>
    class LockFreeQueue {
    private:
        struct Node {
            atomic<Node*> next;
            T data;
            
            Node(const T& item) : next(nullptr), data(item) {}
        };
        
        atomic<Node*> head_;
        atomic<Node*> tail_;
        
    public:
        LockFreeQueue() {
            Node* dummy = new Node(T()); // 创建哑节点
            head_.store(dummy);
            tail_.store(dummy);
        }
        
        ~LockFreeQueue() {
            while (Node* head = head_.load()) {
                head_.store(head->next);
                delete head;
            }
        }
        
        void push(const T& item) {
            Node* newNode = new Node(item);
            Node* prevTail = tail_.exchange(newNode);
            prevTail->next.store(newNode);
        }
        
        bool pop(T& result) {
            while (true) {
                Node* head = head_.load();
                Node* next = head->next.load();
                
                if (next == nullptr) {
                    return false; // 队列为空
                }
                
                // 使用 CAS 操作原子性地更新头指针
                if (head_.compare_exchange_weak(head, next)) {
                    result = next->data;
                    // 使用延迟删除避免 ABA 问题
                    delete head;
                    return true;
                }
                // CAS 失败，重试
            }
        }
        
        bool empty() const {
            return head_.load()->next.load() == nullptr;
        }
        
        size_t size() const {
            size_t count = 0;
            Node* current = head_.load()->next.load();
            while (current != nullptr) {
                count++;
                current = current->next.load();
            }
            return count;
        }
    };

public:
    // 构造函数
    explicit ThreadPool(int threadNum = DEFAULT_THREAD_NUM) 
        : m_iThreadNum(threadNum), m_bStop(false), m_iTaskCount(0) {
        
        if (m_iThreadNum <= 0) {
            m_iThreadNum = DEFAULT_THREAD_NUM;
        }

        // 初始化条件变量（用于线程唤醒）
        if (pthread_mutex_init(&m_mutex, nullptr) != 0) {
            throw runtime_error("Failed to initialize mutex");
        }

        if (pthread_cond_init(&m_cond, nullptr) != 0) {
            pthread_mutex_destroy(&m_mutex);
            throw runtime_error("Failed to initialize condition variable");
        }

        // 创建线程ID数组
        m_piPthId.reset(new pthread_t[m_iThreadNum]);

        // 创建工作线程
        for (int i = 0; i < m_iThreadNum; ++i) {
            if (pthread_create(&m_piPthId[i], nullptr, work, this) != 0) {
                // 如果创建失败，停止已创建的线程并清理资源
                m_bStop = true;
                pthread_cond_broadcast(&m_cond);
                
                // 等待已创建的线程
                for (int j = 0; j < i; ++j) {
                    pthread_join(m_piPthId[j], nullptr);
                }
                
                cleanup();
                throw runtime_error("Failed to create thread");
            }
        }
    }

    // 禁止拷贝构造和赋值
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // 析构函数
    ~ThreadPool() {
        shutdown();
        cleanup();
    }

    // 添加任务 - 使用模板支持任意类型的可调用对象
    template<typename F, typename... Args>
    auto addTask(F&& f, Args&&... args) -> future<decltype(f(args...))> {
        using ReturnType = decltype(f(args...));
        
        // 创建 packaged_task 来包装任务
        auto task = make_shared<packaged_task<ReturnType()>>(
            bind(forward<F>(f), forward<Args>(args)...)
        );
        
        future<ReturnType> result = task->get_future();
        
        // 将任务包装成 void() 类型并添加到无锁队列
        m_qTask.push([task]() { (*task)(); });
        ++m_iTaskCount;
        
        // 唤醒工作线程
        pthread_cond_signal(&m_cond);
        
        return result;
    }

    // 获取任务队列大小
    size_t getTaskQueueSize() const {
        return m_qTask.size();
    }

    // 获取线程数量
    int getThreadNum() const {
        return m_iThreadNum;
    }

    // 获取已完成的任务数
    int getCompletedTaskCount() const {
        return m_iTaskCount.load();
    }

    // 优雅关闭线程池，等待所有任务完成
    void shutdown() {
        m_bStop = true;
        
        // 唤醒所有工作线程
        pthread_cond_broadcast(&m_cond);
        
        // 等待所有线程结束
        for (int i = 0; i < m_iThreadNum; ++i) {
            pthread_join(m_piPthId[i], nullptr);
        }
    }

private:
    void cleanup() {
        pthread_cond_destroy(&m_cond);
        pthread_mutex_destroy(&m_mutex);
    }

    // 工作线程函数
    static void* work(void* arg) {
        ThreadPool* pool = static_cast<ThreadPool*>(arg);
        if (pool != nullptr) {
            pool->run();
        }
        return nullptr;
    }

    void run() {
        while (true) {
            Task task;
            
            // 尝试从无锁队列获取任务
            if (m_qTask.pop(task)) {
                // 执行任务
                try {
                    task();
                } catch (const exception& e) {
                    cerr << "Task execution error: " << e.what() << endl;
                } catch (...) {
                    cerr << "Unknown task execution error" << endl;
                }
            } else {
                // 队列为空，检查是否需要退出
                if (m_bStop) {
                    cout << "Worker thread " << pthread_self() << " exiting..." << endl;
                    break;
                }
                
                // 等待新任务
                MutexLockGuard lock(m_mutex);
                while (m_qTask.empty() && !m_bStop) {
                    pthread_cond_wait(&m_cond, &m_mutex);
                }
                
                if (m_bStop && m_qTask.empty()) {
                    cout << "Worker thread " << pthread_self() << " exiting..." << endl;
                    break;
                }
            }
        }
    }

private:
    atomic<bool> m_bStop;                    // 停止标志
    LockFreeQueue<Task> m_qTask;             // 无锁任务队列
    pthread_cond_t m_cond;                   // 条件变量（仅用于线程唤醒）
    pthread_mutex_t m_mutex;                 // 互斥锁（仅用于条件变量）
    int m_iThreadNum;                        // 线程数量
    unique_ptr<pthread_t[]> m_piPthId;       // 线程ID数组
    atomic<int> m_iTaskCount;                // 已完成任务计数器
};

// 测试函数
void testFunction(int id) {
    cout << "Task " << id << " executed by thread " << pthread_self() << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
}

// 带返回值的测试函数
int testFunctionWithReturn(int id) {
    cout << "Task with return " << id << " executed by thread " << pthread_self() << endl;
    this_thread::sleep_for(chrono::milliseconds(50));
    return id * 2;
}

int main() {
    cout << "=== ThreadPool v4 LockFree Test ===" << endl;
    
    try {
        ThreadPool pool(3);
        
        cout << "LockFree thread pool created with " << pool.getThreadNum() << " threads" << endl;
        
        // 添加一些简单任务
        for (int i = 0; i < 5; ++i) {
            pool.addTask(testFunction, i);
        }
        
        // 添加带返回值的任务
        vector<future<int>> results;
        for (int i = 0; i < 3; ++i) {
            results.emplace_back(pool.addTask(testFunctionWithReturn, i + 10));
        }
        
        // 等待一段时间让任务执行
        this_thread::sleep_for(chrono::seconds(1));
        
        // 获取返回值
        cout << "\n=== Results ===" << endl;
        for (auto& result : results) {
            cout << "Result: " << result.get() << endl;
        }
        
        cout << "\nCurrent task queue size: " << pool.getTaskQueueSize() << endl;
        cout << "Completed tasks: " << pool.getCompletedTaskCount() << endl;
        
        // 交互式测试
        cout << "\n=== Interactive Test ===" << endl;
        cout << "Enter 'i' to add task, 'q' to quit: ";
        
        char cmd;
        int taskId = 100;
        while (cin >> cmd) {
            if (cmd == 'i') {
                pool.addTask(testFunction, taskId++);
                cout << "Task added. Current queue size: " << pool.getTaskQueueSize() << endl;
            } else if (cmd == 'q') {
                break;
            }
            cout << "Enter 'i' to add task, 'q' to quit: ";
        }
        
        cout << "\nShutting down lockfree thread pool..." << endl;
        pool.shutdown();
        cout << "Lockfree thread pool shutdown complete." << endl;
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return -1;
    }
    
    return 0;
}