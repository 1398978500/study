function(gen_exe test_name include_name lib_name)
    # 可执行文件
    add_executable(${test_name} ${test_name}.cpp)

    # 有目录则包含
    if(NOT ${include_name} EQUAL "")
        target_include_directories(${test_name}
            PRIVATE ${PROJECT_SOURCE_DIR}/${include_name}

            if(${include_name} EQUAL "queueList")
                PRIVATE ${PROJECT_SOURCE_DIR}/linkedList
            endif()
        )
    endif()

    # 有库则连接
    if(NOT ${lib_name} EQUAL "")
        target_link_libraries(${test_name}
            ${lib_name}
        )
    endif()

    target_link_libraries(${test_name}
        pthread
    )
endfunction()


gen_exe("ThreadPoolTest2"  "" "")
gen_exe("ThreadPoolTest3"  "" "")


