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
