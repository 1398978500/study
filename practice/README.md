## 记录一下线程池学习

1. 写一个简单的线程池
```
typedef void(*TASK)();
// 任务队列
queue<TASK> taskQue;
// 工作线程
void* run(void*) {
    // 加锁
    lock();
    // 从任务队列取任务
    if(taskQue.empty()){
        unlock();
        continue;
    }

    task = taskQue.front();
    task.pop();
    unlock();
    // 执行任务
    task();
}
```
2. 加入条件变量
* 1中的线程池开的线程,一直在消耗资源,即使没有任务,也会频繁判断
* 使用cond,在没有任务的时候阻塞在pthread_cond_wait();减少资源消耗
* [示例代码](test/ThreadPoolTest2.cpp)

3. 将线程池封装一下
* 2中的线程池初步可用,但是如果想再次使用,需要重新把代码写一遍,所以考虑封装成类
* [示例代码](test/ThreadPoolTest2.cpp)

4. 封装锁和条件变量
* 3中的类,在析构时,难以控制锁销毁的时间
* 可以将锁和条件变量进行封装





