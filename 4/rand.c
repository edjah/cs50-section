#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "seed.h"
#define MAX_NUM 100000

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
    if (argc < 2 || strncmp(argv[1], "-h", 2) == 0) {
        printf("Usage: ./rand seed\n");
        return 1;
    }

    srand(atoi(argv[1]));

    int *a = calloc(sizeof(int), MAX_NUM);
    for (int i = 0; i < MAX_NUM; i++) {
        a[rand() % MAX_NUM]++;
    }

    int max = 0;
    int tot_nonzero = 0;
    int non_zero = 0;

    for (int i = 0; i < MAX_NUM; i++) {
        if (a[i] != 0) {
            non_zero++;
            tot_nonzero += a[i];
        }

        if (a[i] > max) {
            max = a[i];
        }
    }

    printf("Max: %d\n", max);
    printf("Nonzero: %d\n", non_zero);
    printf("Avg nonzero: %.4f\n", (double) tot_nonzero / non_zero);

}
