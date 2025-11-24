## 记录一下线程池学习

### 1. 写一个简单的线程池
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

### 2. 加入条件变量
* 1中的线程池开的线程,一直在消耗资源,即使没有任务,也会频繁判断
* 使用cond,在没有任务的时候阻塞在pthread_cond_wait();减少资源消耗
* [示例代码](test/ThreadPoolTest2.cpp)

### 3. 将线程池封装一下
* 2中的线程池初步可用,但是如果想再次使用,需要重新把代码写一遍,所以考虑封装成类
* [示例代码](test/ThreadPoolTest3.cpp)

### 4. 现代化线程池实现
* **主要改进**：
  - **任务类型灵活性**：使用 `std::function<void()>` 和模板，支持任意类型的可调用对象
  - **异步任务支持**：使用 `std::future` 和 `std::packaged_task`，支持带返回值的任务
  - **资源管理优化**：使用 RAII 风格的锁管理器和 `std::unique_ptr`
  - **线程安全增强**：实现线程安全队列模板类，任务执行在锁外进行
  - **异常安全性**：完善的异常处理和资源清理机制
  - **接口设计优化**：提供状态查询接口和优雅的关闭机制

* **技术特点**：
  - C++14 标准（支持 `std::make_unique`）
  - 智能的线程唤醒策略
  - 支持获取任务执行结果
  - 线程安全的任务计数器
  - 禁止拷贝构造和赋值

* [示例代码](test/ThreadPoolTest4.cpp)

* **封装锁和条件变量**：
* 3中的类,在析构时,难以控制锁销毁的时间
* 可以将锁和条件变量进行封装
* 在 v4 中已实现 RAII 风格的 `MutexLockGuard` 类

#### 编译要求
- CMake 3.5+
- C++14 标准
- pthread 库

#### 使用示例
```cpp
ThreadPool pool(3);  // 创建3个工作线程

// 添加无返回值任务
pool.addTask(testFunction, 42);

// 添加带返回值任务
auto result = pool.addTask(testFunctionWithReturn, 100);
int value = result.get();  // 获取返回值

// 查询状态
cout << "Queue size: " << pool.getTaskQueueSize() << endl;
cout << "Completed tasks: " << pool.getCompletedTaskCount() << endl;
```





