#ifndef ONE_H
#define ONE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "memory.h"

int **get_random_matrix(int size);
int *get_diagonal_sums(int **matrix, int size);

#endif //ONE_H
