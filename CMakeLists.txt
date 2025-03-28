cmake_minimum_required(VERSION 3.30)
project(zyk_notes_on_data_structure C)

set(CMAKE_C_STANDARD 99)

include_directories(LinearDS)

add_executable(zyk_notes_on_data_structure
        main.c
        LinearDS/sequential_linear_list.h
        LinearDS/sequential_linear_list.c
        LinearDS/linked_linear_list.h
        LinearDS/linked_linear_list.c
        LinearDS/sequential_stacks.h
        LinearDS/sequential_stacks.c
        LinearDS/linked_stacks.c
        LinearDS/linked_stacks.h
        LinearDS/sequential_queues.c
        LinearDS/sequential_queues.h
        LinearDS/linked_queues.c
        LinearDS/linked_queues.h
        LinearDS/warning.c
        LinearDS/warning.h)
