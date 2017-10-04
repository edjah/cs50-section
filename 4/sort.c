#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"

// pretty-prints an array
void print_list(int *a, int size) {
    if (size <= 10) {
        printf("[");
        for (int i = 0; i < size; i++) {
            printf("%d", a[i]);
            if (i != size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
    else {
        printf("[");
        for (int i = 0; i < 5; i++) {
            printf("%d", a[i]);
            if (i != 4) {
                printf(", ");
            }
        }
        printf(", ..., ");
        for (int i = size - 5; i < size; i++) {
            printf("%d", a[i]);
            if (i != size - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(int argc, char *argv[]) {
    // ensure correct usage
    if (argc != 4 || strncmp(argv[1], "-h", 2) == 0) {
        printf("Usage: ./sort alg size init\n");
        return 1;
    }

    // seeding the random number generator
    srand(time(NULL));

    // allocating space for an array of ints
    int size = atoi(argv[2]);
    int *a = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        a[i] = i;
    }

    // do nothing
    if (strcmp(argv[3], "sorted") == 0) {
    }

    // elements of array in reverse
    else if (strcmp(argv[3], "reverse") == 0) {
        for (int i = 0; i < size / 2; i++) {
            swap(a, i, size - i - 1);
        }
    }

    // elements of array are close to their correct position
    else if (strcmp(argv[3], "close") == 0) {
        for (int i = 1; i < size - 1; i++) {
            swap(a, i, i + rand() % 3 - 1);
        }
    }

    // random by default
    else {
        for (int i = 0; i < size - 1; i++) {
            swap(a, i, i + rand() % (size - i));
        }
    }

    // print list before sorting
    print_list(a, size);


    // run and benchmark the requested sorting algorithm
    clock_t start = clock();
    if (strcmp(argv[1], "quicksort") == 0) {
        quicksort(a, size);
    }
    else if (strcmp(argv[1], "builtinsort") == 0) {
        builtinsort(a, size);
    }
    else if (strcmp(argv[1], "mergesort") == 0) {
        mergesort(a, size);
    }
    else if (strcmp(argv[1], "insertionsort") == 0) {
        insertionsort(a, size);
    }
    else if (strcmp(argv[1], "selectionsort") == 0) {
        selectionsort(a, size);
    }
    else if (strcmp(argv[1], "bubblesort") == 0) {
        bubblesort(a, size);
    }
    else if (strcmp(argv[1], "randomquicksort") == 0) {
        randomized_quicksort(a, size);
    }

    // print sorted list
    print_list(a, size);

    // print benchmark results
    clock_t end = clock();
    printf("%s took %.4f sec to complete on %s input of size %d\n",
           argv[1], (double) (end - start) / CLOCKS_PER_SEC, argv[3], size);
}
