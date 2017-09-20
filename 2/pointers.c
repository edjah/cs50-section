#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void) {
    int a = 2;
    int b = 3;
    printf("Previous: a = %d | b = %d\n", a, b);
    swap(&a, &b);
    printf("After swap: a = %d | b = %d\n", a, b);
}
