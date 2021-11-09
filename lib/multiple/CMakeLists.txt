set(SOURCES source/multiple.c)

add_library(multiple STATIC ${SOURCES})
target_include_directories(multiple PUBLIC include/)
target_link_libraries(multiple PUBLIC memory)
