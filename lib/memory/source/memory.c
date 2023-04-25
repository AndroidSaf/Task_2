#include "memory.h"

int **create_matrix(int size) {
    int **matrix = (int **) calloc(size, sizeof(int *));
    for (int i = 0; i < size; ++i) {
        matrix[i] = (int *) calloc(size, sizeof(int));
    }
    return matrix;
}

int *create_array(int size) {
    return (int *) calloc(size, sizeof(int));
}

void free_memory(int **matrix, int *array, int size) {
    if (matrix != NULL) {
        for (int i = 0; i < size; ++i) {
            free(matrix[i]);
        }
        free(matrix);
    }

    if (array != NULL) {
        free(array);
    }
}
