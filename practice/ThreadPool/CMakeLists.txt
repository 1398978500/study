add_library(ThreadPool STATIC
    ThreadPool.cpp
    TaskQueue.cpp
)

target_link_libraries(ThreadPool
    pthread
)