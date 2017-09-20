#include <stdio.h>
#include <cs50.h>

int fib(int n) {

    int prev = 1;
    int curr = 0;

    for (int i = 0; i < n; i++) {
        int tmp = prev;
        prev = curr;
        curr = tmp + curr;
    }

    return curr;
}

string main(void) {
    for (int i = 0; i < 11; i++) {
        int n = fib(i);
        printf("Fib(%d) = %d\n", i, n);
    }
}
