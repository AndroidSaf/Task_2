#include "processing.h"

int **get_random_matrix(int size) {
    int **matrix = create_matrix(size);
    if (matrix == NULL) {
        printf("Error: cannot create matrix!\n");
        return NULL;
    }

    srand(666);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = -10 + rand() % 21;
        }
    }
    return matrix;
}

int diagonal_sum(const char side, int index, int size, int **matrix) {
    int sum = 0;

    switch (side) {
        case 'l':
            for (int i = index; i < size; ++i) {
                for (int j = 0; j <= (size - 1) - index; ++j) {
                    if ((i - j) == index && (i - j) > 0)
                        sum += matrix[i][j];
                }
            }
            return sum;
        case 'r':
            for (int j = index; j < size; ++j) {
                for (int i = 0; i <= size - index - 1; ++i) {
                    if ((j - i) == index && (j - i) >= 0)
                        sum += matrix[i][j];
                }
            }
            return sum;
        default:
            exit(EXIT_FAILURE);
    }
}

int *get_diagonal_sums(int **matrix, int size) {
    int *array = create_array(2 * size - 1);
    if (array == NULL) {
        printf("Error: cannot create an array!\n");
        return NULL;
    }

    printf("Working processes: 1\n");
    int index = 0;
    for (int i = size - 1; i > 0; --i) {
        array[index++] = diagonal_sum('l', i, size, matrix);
        printf("\r%.2lf%c", (double) index / (2 *size - 1) * 100, '%');
        fflush(stdout);
    }
    for (int j = 0; j < size; ++j) {
        array[index++] = diagonal_sum('r', j, size, matrix);
        printf("\r%.2lf%c", (double) index / (2 * size - 1) * 100, '%');
        fflush(stdout);
    }
    printf("\n");
    return array;
}
