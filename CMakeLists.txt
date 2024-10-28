cmake_minimum_required(VERSION 3.27)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled mainlab1.c
        array.c
        number.c
        mystring.c
        tests.c
        menu.c
        field_Info.c
)
