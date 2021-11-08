cmake_minimum_required(VERSION 3.20)
project(Task_2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -Wpedantic)

option(MULTIPLE "link multiple process library")
option(ONE "link one process library")

add_executable(main main.c)

add_library(memory lib/memory/source/memory.c)
target_include_directories(memory PUBLIC lib/memory/include)

add_library(one lib/one/source/one.c)
target_include_directories(one PUBLIC lib/one/include)

add_library(multiple lib/multiple/source/multiple.c)
target_include_directories(multiple PUBLIC lib/multiple/include)

target_link_libraries(one memory)
target_link_libraries(multiple memory)

if (MULTIPLE)
    target_link_libraries(main multiple)
elseif (ONE)
    target_link_libraries(main one)
else ()
    target_link_libraries(main one)
endif ()
