set(SOURCES source/memory.c)

add_library(memory STATIC ${SOURCES})
target_include_directories(memory PUBLIC include/)
