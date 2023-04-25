cmake_minimum_required(VERSION 3.20)
project(Task_2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -Wpedantic)

set(INPUT ${CMAKE_CURRENT_SOURCE_DIR}/data/input.txt)
set(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/data/output.txt)

option(MULTIPLE "multiple process library")
option(ONE "one process library")
option(UTESTS "unit tests")

add_subdirectory(lib/)

if (UTESTS)
    set(${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${CMAKE_BINARY_DIR})
    enable_testing()
    add_subdirectory(tests/)
    return()
endif()

add_executable(main main.c)

if (MULTIPLE)
    target_link_libraries(main multiple)
elseif (ONE)
    target_link_libraries(main one)
else ()
    target_link_libraries(main one)
endif ()
