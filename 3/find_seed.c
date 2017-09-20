#define NENYA_SEED 11179885
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./random target\n");
        return 1;
    }

    char *target = argv[1];
    int n = strlen(target);
    for (int i = 0; i < n; i++) {
        target[i] = toupper(target[i]);
        if (!isalpha(target[i])) {
            printf("`target` must be all alpha\n");
            return 1;
        }
    }

    char str[n + 1];
    int found = 0;
    str[n] = '\0';

    for (int seed = 0; seed < RAND_MAX; seed++) {
        srand(seed);
        found = 1;
        for (int j = 0; j < n; j++) {
            if ('A' + (rand() % 26) != target[j]) {
                found = 0;
                break;
            }
        }
        if (found) {
            printf("Found it: %s (SEED: %d)\n", target, seed);
            return 1;
        }
    }

    printf(":( Could not find a seed for \"%s\"\n", target);
}
