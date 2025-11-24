cmake_minimum_required(VERSION 3.5) # 设置CMake最小版本

project(practice) # 设置工程名

# add_executable(${PROJECT_NAME} main.cpp) # 生成可执行文件

# target_link_libraries(${PROJECT_NAME}
#     pthread
# )

add_subdirectory(test)
add_subdirectory(ThreadPool)