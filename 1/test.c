#include <stdio.h>

int main(void) {
    long tot = 0;
    for (int i = 0; i < 1000000001; i++) {
        tot += i;
    }
    printf("%ld\n", tot);
}
