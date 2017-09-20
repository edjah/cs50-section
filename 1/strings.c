#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void) {
    string a = "i am a happy kid";
    int tot = 1;

    for (int i = 0, n = strlen(a); i < n; i++) {
        tot *= a[i];
    }

    printf("Prod: %d\n", tot);

}
