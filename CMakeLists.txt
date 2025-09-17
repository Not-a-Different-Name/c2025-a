cmake_minimum_required(VERSION 4.0)
project(c2025_challenge)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(p01_running_letter level1/p01_running_letter/main.c)

add_executable(p02_is_prime  level1/p02_is_prime/main.c)

add_executable(p03_all_primes  level1/p03_all_primes/main.c)

add_executable(p04_goldbach  level1/p04_goldbach/main.c)

add_executable(p05_encrypt_decrypt  level1/p05_encrypt_decrypt/main.c)

add_executable(p06_hanoi  level1/p06_hanoi/main.c)

add_executable(p07_maze  level1/p07_maze/generate_maze.c
        level1/p07_maze/maze_test.c)

add_executable(p08_push_boxes  level1/p08_push_boxes/push_process.c
        level1/p08_push_boxes/push_boxes.c
        level1/p08_push_boxes/box_test.h)

add_executable(p09_linked_list  level1/p09_linked_list/main.c)

add_executable(p10_warehouse  level1/p10_warehouse/main.c)

set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/level1/p08_push_boxes)
file(GLOB RESOURCE_FILES ${RESOURCE_DIR}/*.txt)
# 2. 查找资源文件
#file(GLOB RESOURCE_FILES
#        ${CMAKE_SOURCE_DIR}/1.txt
#        ${CMAKE_SOURCE_DIR}/2.txt
#        ${CMAKE_SOURCE_DIR}/3.txt
#)

# 3. 为每个资源文件添加构建后复制命令
#foreach(resource_file ${RESOURCE_FILES})
#    add_custom_command(
#            TARGET ${target_name} POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy
#            ${resource_file}
#            ${CMAKE_BINARY_DIR}
#            VERBATIM
#    )
#endforeach()
foreach(resource_file ${RESOURCE_FILES})
    # 提取文件名（不含路径）
    get_filename_component(resource_filename ${resource_file} NAME)

    # 为每个目标添加复制命令
    foreach(target_name
            p08_push_boxes
    )
        add_custom_command(
                TARGET ${target_name} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${resource_file}
                ${CMAKE_BINARY_DIR}/${resource_filename}  # 复制到构建根目录
                COMMENT "Copying ${resource_file} to build directory"
                VERBATIM
        )
    endforeach()
endforeach()
#foreach(target_name
##        p01_running_letter
##        p02_is_prime
##        p03_all_primes
##        p04_goldbach
##        p05_encrypt_decrypt
##        p06_hanoi
##        p07_maze
#        p08_push_boxes
##        p09_linked_list
##        p10_warehouse)
#
#    foreach(resource_file ${RESOURCE_FILES})
#        add_custom_command(
#                TARGET ${target_name} POST_BUILD  # <<< 改为每个具体的目标名
#                COMMAND ${CMAKE_COMMAND} -E copy
#                ${resource_file}
#                $<TARGET_FILE_DIR:${target_name}>
#                VERBATIM
#        )
#    endforeach()
#endforeach()