#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

int main(int argc, char *argv[]) {
    // seeding the random number generator
    srand(time(NULL));

    // parsing command line arguments
    int max_val = 1000000;
    int num_vals = 1000000;
    if (argc >= 2)
        max_val = atoi(argv[1]);
    if (argc >= 3)
        num_vals = atoi(argv[2]);

    printf("Max val: %d\n", max_val);
    printf("Num vals: %d\n", num_vals);


    // inserting random numbers into the BST
    clock_t start = clock();
    for (int i = 0; i < num_vals; i++) {
        insert(rand() % max_val);
    }

    // searching for random numbers in the BST
    clock_t mid = clock();
    for (int i = 0; i < num_vals; i++) {
        search(rand() % max_val);
    }
    clock_t end = clock();

    // print results
    double insert_time = (double) (mid - start) / CLOCKS_PER_SEC;
    double contains_time = (double) (end - mid) / CLOCKS_PER_SEC;
    printf("Structure size: %d\n", size());
    printf("Time to insert: %f sec\n", insert_time);
    printf("Time to search: %f sec\n", contains_time);

    return 0;
}
