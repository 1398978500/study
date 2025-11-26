add_library(ThreadPool STATIC
    ThreadPool.cpp
)

target_link_libraries(ThreadPool
    pthread
)