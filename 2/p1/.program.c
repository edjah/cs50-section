#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./program num\n");
        return 1;
    }
    int size = atoi(argv[1]);
    int *a = malloc(size);

    int sum = 0;
    for (int i = 0; i < size; i++) {
        a[i] = i * i;
    }
    for (int i = 0; i < size; i++) {
        printf("a[%d] = %d\n", i, a[i]);
        sum += a[i];
    }
    printf("Sum: %d\n", sum);
}
