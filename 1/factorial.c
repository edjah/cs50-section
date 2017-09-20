#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[]) {
    long tot = 0;
    for (int i = 0; i < 1000000000; i++) {
        tot += i;
    }
    printf("%li\n", tot);
}

