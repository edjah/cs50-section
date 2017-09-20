#define _XOPEN_SOURCE
#define MAX_LEN 4
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>

// all of the characters that could be used in a password
char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int alpha_size = 52;

/**
 * Recursively test all possible passwords up to length 'len'
 */
void decrypt(char *pass, int idx, int len, char *salt, char *hash) {
    if (strcmp(crypt(pass, salt), hash) == 0) {
        printf("%s\n", pass);
        exit(0);
    }
    else if (idx == len) {
        return;
    }
    else {
        for (int i = 0; i < alpha_size; i++) {
            pass[idx] = alphabet[i];
            decrypt(pass, idx + 1, len, salt, hash);
            pass[idx + 1] = '\0';
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    char *hash = argv[1];
    char pass[MAX_LEN + 1] = {0};
    char salt[3] = {hash[0], hash[1], '\0'};
    decrypt(pass, 0, MAX_LEN, salt, hash);
}
