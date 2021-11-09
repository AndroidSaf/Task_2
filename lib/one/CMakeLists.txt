set(SOURCES source/one.c)

add_library(one STATIC ${SOURCES})
target_include_directories(one PUBLIC include/)
target_link_libraries(one PUBLIC memory)