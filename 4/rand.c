#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "seed.h"

unsigned x;

void mysrand(unsigned seed) {
    x = seed;
}

unsigned myrand() {
    x = 1103515245 * x + 12345;
    return x;
}

int main(int argc, char *argv[]) {
    // ensuring correct usage
    if (argc < 3 || strncmp(argv[1], "-h", 2) == 0) {
        printf("Usage: ./rand seed num\n");
        return 1;
    }

    int seed = atoi(argv[1]);
    int size = atoi(argv[2]);
    srand(seed);

    unsigned char *a = calloc(size, sizeof(unsigned char));
    for (int i = 0; i < size; i++) {
        a[rand() % size]++;
    }

    int max = 0;
    int tot_nonzero = 0;
    int non_zero = 0;

    for (int i = 0; i < size; i++) {
        if (a[i] != 0) {
            non_zero++;
            tot_nonzero += a[i];
        }

        if (a[i] > max) {
            max = a[i];
        }
    }

    printf("Max: %d\n", max);
    printf("Nonzero: %.5f\n", (double) non_zero / size);
    printf("Avg nonzero: %.4f\n", (double) tot_nonzero / non_zero);

}
