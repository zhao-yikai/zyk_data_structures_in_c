cmake_minimum_required(VERSION 3.20)
project(ZYK_Data_Structures_In_C LANGUAGES C)

# 基础配置
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # 为CLion生成编译命令数据库

# 全局头文件库
add_library(dsc_headers INTERFACE)
target_include_directories(dsc_headers INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/dsc>
        $<INSTALL_INTERFACE:include/dsc>
)

# 编译警告模块（作为基础工具库）
add_library(warning STATIC
        src/warning.c
        include/dsc/warning.h
)
target_link_libraries(warning PUBLIC dsc_headers)

# 数据结构模块化编译
function(add_data_structure_target target_name)
    add_library(${target_name} STATIC
            src/${target_name}.c
            include/dsc/${target_name}.h
    )
    target_link_libraries(${target_name}
            PUBLIC
            dsc_headers
            PRIVATE
            warning
    )
endfunction()

# 声明所有数据结构模块
set(DATA_STRUCTURES
        sequential_linear_list
        linked_linear_list
        sequential_stacks
        linked_stacks
        sequential_queues
        linked_queues
)

foreach (ds ${DATA_STRUCTURES})
    add_data_structure_target(${ds})
endforeach ()

# 主可执行文件
add_executable(${PROJECT_NAME}
        main.c
)

# 链接所有数据结构模块
target_link_libraries(${PROJECT_NAME} PRIVATE
        ${DATA_STRUCTURES}
        warning
)

# 安装规则（可选）
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
install(DIRECTORY include/dsc/ DESTINATION include/dsc)