#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include <atomic>
#include <exception>

using namespace std;

const int DEFAULT_THREAD_NUM = 5;

typedef void (*TASK)(int);
class ThreadPool {
private:
    void beforeException(pthread_mutex_t *mutex=nullptr, pthread_cond_t *cond=nullptr, 
                pthread_t *piPthId=nullptr) {
        if(mutex != nullptr) {
            pthread_mutex_destroy(mutex);
        }

        if(cond != nullptr) {
            pthread_cond_destroy(cond);
        }

        if(piPthId != nullptr) {
            delete [] piPthId;
        }
    }
public:
    void addTask(TASK task) {
        bool bNotifyAll = false;
        pthread_mutex_lock(&m_mutex);

        m_qTask.push(task);
        if(m_qTask.size() >= m_iThreadNum) {
            bNotifyAll = true;
        }

        pthread_mutex_unlock(&m_mutex);

        if(bNotifyAll) {
            pthread_cond_broadcast(&m_cond);
        } else {
            pthread_cond_signal(&m_cond);
        }
    }

    // 构造函数
    ThreadPool(int iThreadNum = DEFAULT_THREAD_NUM) : m_iThreadNum(iThreadNum) {
        if(m_iThreadNum <= 0) {
            m_iThreadNum = DEFAULT_THREAD_NUM;
        }

        if(0 != pthread_mutex_init(&m_mutex, NULL)) {
            perror("pthread_mutex_init  ");
            throw exception();
        }

        if(0 != pthread_cond_init(&m_cond, NULL)) {
            perror("pthread_cond_init  ");
            beforeException(&m_mutex);
            throw exception();
        }

        m_piPthId = new pthread_t[m_iThreadNum];
        if(m_piPthId == nullptr) {
            cerr << "m_piPthId is NULL" << endl;
            beforeException(&m_mutex, &m_cond);
            throw exception();
        }

        // 创建线程
        for(int i = 0; i < m_iThreadNum; i++) {
            if(0 != pthread_create(&m_piPthId[i], NULL, work, this)
                || 0 != pthread_detach(m_piPthId[i])) {
                perror("pthread_create  ");
                beforeException(&m_mutex, &m_cond, m_piPthId);
                throw exception();
            }
        }
    }

    ~ThreadPool() {
        delete [] m_piPthId;

        m_bStop = true;
        // 销毁cond前需要广播,放开所有cond
        int iRet = pthread_cond_broadcast(&m_cond);
        iRet = pthread_cond_destroy(&m_cond);

        iRet = pthread_mutex_destroy(&m_mutex);
    }

    // 线程函数
    static void* work(void* arg) {
        ThreadPool *pool = (ThreadPool*)arg;
        if(pool != nullptr) {
            pool->run();
        }

        return NULL;
    }

    void run() {
        while(1) {
            pthread_mutex_lock(&m_mutex);

            if(m_qTask.empty()) {
                // 工作队列是空的,就等待唤醒
                pthread_cond_wait(&m_cond, &m_mutex);
                // 被唤醒了,发现没任务
                if(m_qTask.empty()) {
                    pthread_mutex_unlock(&m_mutex);

                    // 要停止,就退出循环
                    if(m_bStop) {
                        cout << "exit ..." << endl;
                        break;
                    }

                    continue;
                }
            }

            // 任务队列不是空的,取出一个任务执行
            TASK f = m_qTask.front();
            m_qTask.pop();
            // 实际工作函数需要锁的话要定义工作函数自己的锁
            f(m_iNum++);
            pthread_mutex_unlock(&m_mutex);
        }
    }


private:
    atomic<bool> m_bStop;       // 停止标志
    queue<TASK> m_qTask;        // 任务队列

    pthread_cond_t m_cond;      // 条件变量
    pthread_mutex_t m_mutex;    // 任务队列的锁

    int m_iThreadNum;           // 线程数量
    pthread_t *m_piPthId;       // 存储线程ID

    int m_iNum; // 打印出来好看
};

void haha(int a) {
    cout << "hahah " << a << endl;
}


int main(int argc, char* argv[]) {
    ThreadPool pool;

    char a = 0;
    while(1) {
        cin >> a;
        if(a == 'i') {
            pool.addTask(haha);
        } else {
            cout << "end ......." << endl;
            break;
        }
    }

    return 0;
}

