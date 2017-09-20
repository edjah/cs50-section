#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// all of the characters that could be used in a password
char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int alpha_size = 52;

/**
 * Recursively test all possible passwords of length 'len'
 */
char* test(int n, int len, char *salt, char *pass, char *hash) {
    if (n == len) {
        if (strcmp(crypt(pass, salt), hash) == 0) {
            return pass;
        }
    } else {
        for (int i = 0; i < alpha_size; i++) {
            pass[n] = alphabet[i];
            char *result = test(n + 1, len, salt, pass, hash);
            if (result) {
                return result;
            }
        }
    }
    return NULL;
}

/**
 * Decrypts a password that was hashed using the crypt function
 */
char* brute_force(char *hash, int max_len) {
    char salt[3] = {hash[0], hash[1], '\0'};
    char *pass = malloc(max_len * sizeof(char) + 1);

    for (int len = 0; len <= max_len; len++) {
        pass[len] = '\0';
        char *result = test(0, len, salt, pass, hash);
        if (result) {
            return result;
        }
    }

    return NULL;
}
