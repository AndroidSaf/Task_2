#ifndef MULTIPLE_H
#define MULTIPLE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "memory.h"

int **get_random_matrix(int size);
int get_processes_quantity();
int diagonal_sum(const char side, int index, int size, int **matrix);
int *get_diagonal_sums(int **matrix, int size);

#endif //MULTIPLE_H
