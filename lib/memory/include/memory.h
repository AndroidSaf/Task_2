#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <stdio.h>

typedef struct process {
    int id;
    int index;
}  process;

process *create_process_struct(int size);
int **create_matrix(int size);
int *create_array(int size);
void free_memory(int **matrix, int *array, int size);


#endif //MEMORY_H