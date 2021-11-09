#include <gtest/gtest.h>

extern "C" {
#include "memory.h"
#define SIZE 10000
#define N_PROCESSES 10
}

TEST(MEMORY_TEST, PROCESS_STRUCT_CREATE_TEST) {
    process *array = create_process_struct(N_PROCESSES);
    ASSERT_NE(array, nullptr);
    free(array);
}

TEST(MEMORY_TEST, MATRIX_CREATE_TEST) {
    int **matrix = create_matrix(SIZE);
    ASSERT_NE(matrix, nullptr);
    free_memory(matrix, nullptr, SIZE);
}

TEST(MEMORY_TEST, ARRAY_CREATE_TEST) {
    int *array = create_array(2 * SIZE - 1);
    ASSERT_NE(array, nullptr);
    free_memory(nullptr, array, SIZE);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}