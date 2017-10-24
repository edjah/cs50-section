#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>



char* mystery() {
    char *y = malloc(30 * sizeof(char));
    for (int i = 0; i < 30; i++) {
        y[i] = 'a';
    }
    return y;
}


int main(void) {
    char *s = mystery();
    printf("%s\n", s);
}
