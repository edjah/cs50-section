#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

int* mystery() {
    int size = rand() % 100000;
    int *result = calloc(size + 1, sizeof(int));
    result[0] = size;
    for (int i = 1; i <= size; i++) {
        result[i] = (i - 1) * (i - 1);
    }

    return result + 1;
}


void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


int main(void) {
    int a = 10;
    int b = 69;

    printf("%d %d\n", a, b);

    unsigned long aa = &a;
    unsigned long bb = &b;

    int x[10];

    printf("%p\n", &x);
    printf("%p\n", &x[0]);


    swap(aa, bb);

    printf("%d %d\n", a, b);
}
