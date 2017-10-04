#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
    // ensure correct usage
    if (argc != 2 || strncmp(argv[1], "-h", 2) == 0) {
        printf("Usage: ./find_seed target\n");
        return 1;
    }

    // verify that the target is all alphabetical
    char *target = argv[1];
    int n = strlen(target);
    for (int i = 0; i < n; i++) {
        target[i] = toupper(target[i]);
        if (!isalpha(target[i])) {
            printf("`target` must be all alpha\n");
            return 1;
        }
    }

    // trying various seeds
    int found = 0;
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
