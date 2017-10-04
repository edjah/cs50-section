#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 10000000

int x[ARRAY_SIZE];

int main(void) {
    clock_t start = clock();
    clock_t end = clock();
    printf("%.5f ms\n", 1000.0 * (end - start) / CLOCKS_PER_SEC);
}
