#include <cstdio>
#include <gtest/gtest.h>

extern "C" {
#include "processing.h"
}

#define BUFFER_SIZE 255
#define SIZE 13
#define INPUT "/home/dominik/Task_2/tests/data/input.txt"
#define OUTPUT "/home/dominik/Task_2/tests/data/output.txt"

TEST(MULTI_PROCESS_TEST, ANSWER_ARRAY_TEST) {
    FILE *input = fopen(INPUT, "rt");
    FILE *output = fopen(OUTPUT, "rt");

    char buffer[BUFFER_SIZE];

    fgets(buffer, BUFFER_SIZE, input);

    int **matrix = create_matrix(SIZE);
    int *diagonal_sums_array = nullptr;
    int *array = create_array(2 * SIZE - 1);

    int value;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            fgets(buffer, BUFFER_SIZE, input);
            sscanf(buffer, "%d", &value);
            matrix[i][j] = value;
        }
    }

    for (int i = 0; i < 2 * SIZE - 1; ++i) {
        fgets(buffer, BUFFER_SIZE, output);
        sscanf(buffer, "%d", &value);
        array[i] = value;
    }

    diagonal_sums_array = get_diagonal_sums(matrix, SIZE);
    for (int i = 0; i < 2 * SIZE - 1; ++i) {
        ASSERT_EQ(array[i], diagonal_sums_array[i]);
    }

    fclose(input);
    fclose(output);
    free(diagonal_sums_array);
    free_memory(matrix, array, SIZE);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}