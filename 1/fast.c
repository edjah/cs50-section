#include <stdio.h>

int main(void) {
    long tot = 1;
    for (int i = 0; i < 1000000001; i++) {
        tot *= i;
    }
    printf("%ld\n", tot);
}
