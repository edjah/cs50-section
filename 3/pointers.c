#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int main(int argc, char *argv[]) {
    // ensuring correct usage
    if (argc != 2) {
        printf("Usage: ./pointers num\n");
        return 1;
    }

    // parsing command line arguments
    int num = atoi(argv[1]);

    // allocating space for `num` ints
    int *garbage = malloc(sizeof(int) * num);

    // clearing out the space for `num` ints first
    int *cleared = calloc(num, sizeof(int));
    for (int i = 0; i < num; i++) {
        assert(cleared[i] == 0);
    }

    // freeing up unused space
    free(garbage);
    free(cleared);

    // allocating a total of over 2 TB of memory
    size_t tot = 0;
    for (int i = 0; i < 6150; i++) {
        int *ptr = malloc(0xfffff * i);
        tot += 0xfffff * i;
        free(ptr);
    }
    printf("tot: %zu GB\n", tot / (1024 * 1024 * 1024));

    // pointer tests
    int a = 10;
    int *b = &a;
    int **c = &b;
    int ***d = &c;
    printf("a = %d\n", a);
    printf("*b = %d\n", *b);
    printf("*(*c) = %d\n", *(*c));
    printf("*(*(*d)) = %d\n", *(*(*d)));

}
