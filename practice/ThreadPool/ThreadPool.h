#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>

using Task = std::function<void()>;

template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue_;

    mutable std::mutex mutex_;

public:
    void push(const T& item)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
    }

    bool pop(T& item)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return false;
        }

        item = queue_.front();
        queue_.pop();
        return true;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    size_t size() const
    {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    // 禁止拷贝
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;
};

class ThreadPool {
private:
    ThreadSafeQueue<Task> taskQueue_;

    std::vector<std::thread> threads_;

    std::condition_variable cv_;

    bool stop_;

public:
    explicit ThreadPool(size_t threadNum);
    ~ThreadPool();

    // 禁止拷贝
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    void addTask(const Task& task);

    void waitAllTasks();
};

#endif