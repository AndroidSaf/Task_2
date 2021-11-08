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
    int *array = create_array(2 *size - 1);
    if (array == NULL) {
        printf("Error: cannot create an array!\n");
        return NULL;
    }

    int n_processes = (int) sysconf(_SC_NPROCESSORS_ONLN) * 2;
    if (n_processes <= 0) {
        printf("Error: no processors are available to this task!\n");
        exit(EXIT_FAILURE);
    }

    if (size <= n_processes)
        n_processes = size;
    printf("Working processes: %d\n", n_processes);

    process *process_array = create_process_struct(n_processes);
    if (process_array == NULL) {
        printf("Error: cannot create an array!\n");
        return NULL;
    }

    int fd[n_processes][2];
    pid_t pid = getppid();
    pid_t wait();
    for (int i = 0; i < n_processes; ++i) {

        if (pipe(fd[i]) < 0) {
            exit(EXIT_FAILURE);
        }

        if (pid != 0) {
            pid = fork();
            if (pid == -1) {
                printf("Error: cannot create a new one!\n");
                exit(EXIT_FAILURE);
            }
            process_array[i].id = getpid();
            process_array[i].index = i;
        }
    }

    if (pid == 0) {
        int process_index;
        for (int i = 0; i < n_processes; ++i) {
            if (getpid() == process_array[i].id) {
                process_index = process_array[i].index;
                close(fd[i][0]);
            } else {
                close(fd[i][1]);
                close(fd[i][0]);
            }
        }

        int result[2];
        int right_index = process_index;
        int left_index = (size - 1) - right_index;

        while (left_index > 0) {
            result[1] = diagonal_sum('l', left_index, size, matrix);
            result[0] = right_index;
            if (write(fd[process_index][1], result, sizeof(int) * 2) < 0) {
                printf("Error: cannot write the pipe!\n");
                exit(EXIT_FAILURE);
            }
            left_index -= n_processes;
            right_index += n_processes;
        }

        right_index = process_index;
        while (right_index < size) {
            result[1] = diagonal_sum('r', right_index, size, matrix);
            result[0] = (size - 1) + right_index;
            if (write(fd[process_index][1], result, sizeof(int) * 2) < 0) {
                printf("Error: cannot write the pipe!\n");
                exit(EXIT_FAILURE);
            }
            right_index += n_processes;
        }
        close(fd[process_index][1]);
        exit(EXIT_SUCCESS);
    } else {
        for (int i = 0; i < n_processes; ++i) {
            close(fd[i][1]);
        }

        int index = 0, process_index = 0;
        int result[2];
        while (index < 2 * size - 1) {
            if (read(fd[process_index][0], result, sizeof(int) * 2) < 0) {
                printf("Error: cannot read the pipe!\n");
                continue;
            }
            array[result[0]] = result[1];
            index++;
            process_index++;
            if (process_index == n_processes)
                process_index = 0;
            printf("\r%.2lf%c", (double) index / (2 * size - 1) * 100, '%');
            fflush(stdout);
        }
        printf("\n");

        for (int i = 0; i < n_processes; ++i) {
            close(fd[i][0]);
        }

        while (wait(NULL) != -1);
    }
    free(process_array);

    return array;
}
