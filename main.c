#include <getopt.h>
#include <string.h>
#include "processing.h"

int main(int argc, char *argv[]) {

    const char *options = "-:s:h";

    int size = 0, opt;
    int **matrix = NULL;
    int *diag_sum_array = NULL;

    while ((opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
            case 's':
                size = atoi(optarg);
                if (!size) {
                    printf("Error: expected an argument [unsigned int] more than 0 for option -s!\n");
                    return EXIT_FAILURE;
                }
                matrix = get_random_matrix(size);
                if (matrix == NULL)
                    return EXIT_FAILURE;
                diag_sum_array = get_diagonal_sums(matrix, size);
                if (diag_sum_array == NULL) {
                    printf("Failure!\n");
                    return EXIT_FAILURE;
                }
                else
                    printf("Successfully!\n");
                break;
            case 'h':
                printf("-s -- size of matrix\n");
                printf("Example: -s [unsigned int]\n");
                return EXIT_SUCCESS;
            case '?':
                printf("Error: unknown option %c!\n", optopt);
                break;
            case ':':
                printf("Error: expected an argument [unsigned int] more than 0 for option -s!\n");
                break;
            case  1 :
                printf("Error: non-option argument %s!\n", optarg);
                break;
            default:
                break;
        }
    }

    free_memory(matrix, diag_sum_array, size);
    return EXIT_SUCCESS;
}
