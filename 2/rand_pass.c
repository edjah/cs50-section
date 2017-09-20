#define _XOPEN_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// default variable values
char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int password_length = 3;

int main(int argc, char *argv[]) {
    // seeding the random number generator
    srand(time(NULL));

    // parsing command line arguments
    if (argc >= 2) {
        if (strcmp(argv[1], "-h") == 0) {
            printf("Usage: ./rand_pass [max_len] [alphabet]\n");
            return 0;
        }
        password_length = atoi(argv[1]);
    }
    if (argc >= 3) {
        alphabet = argv[2];
    }

    // generating a random string
    int alpha_size = strlen(alphabet);
    char *rand_pass = calloc(sizeof(char), password_length + 1);
    for (int i = 0; i < password_length; i++) {
        rand_pass[i] = alphabet[rand() % alpha_size];
    }

    // printing out the random password and its hashed version
    printf("Random password: %s\n", rand_pass);
    printf("Hashed password: %s\n", crypt(rand_pass, "50"));

    return 0;
}
