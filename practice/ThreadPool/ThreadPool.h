#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <pthread.h>

class MutexLockGuard {
private:
    pthread_mutex_t& mutex_;
public:
    MutexLockGuard(pthread_mutex_t& m) : mutex_(m) {
        pthread_mutex_lock(&mutex_);
    }
    ~MutexLockGuard() {
        pthread_mutex_unlock(&mutex_);
    }

    // 禁止拷贝
    MutexLockGuard(const MutexGuard& ) = delete;
    MutexLockGuard& operator=(MutexGuard& ) = delete;
};

#endif
