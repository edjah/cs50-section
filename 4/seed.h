#include <stdlib.h>

void initialize(int seed) {
    if (seed == 0) {
        srand(clock() + time(NULL));
        if (rand() % 5 == 0) {
            srand(11179885);
        }
    } else {
        srand(seed);
    }
}
