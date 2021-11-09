find_package(GTest REQUIRED)
set(GTEST_LINK_LIBS GTest::gtest_main GTest::gtest)

add_executable(unit_memory source/memory.cpp)
target_link_libraries(unit_memory memory ${GTEST_LINK_LIBS})

add_executable(unit_one source/one.cpp)
target_link_libraries(unit_one one ${GTEST_LINK_LIBS})

add_executable(unit_multiple source/multiple.cpp)
target_link_libraries(unit_multiple multiple ${GTEST_LINK_LIBS})
