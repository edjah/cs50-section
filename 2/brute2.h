#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>

// all of the characters that could be used in a password
char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int alpha_size = 52;


/**
 * Decrypts a password that was hashed using the crypt function
 */
char* brute_force(char *hash, int max_len) {
    char salt[3] = {hash[0], hash[1], '\0'};
    char *pass = calloc(max_len + 1, sizeof(char));
    int places[max_len];
    memset(places, 0, sizeof(int) * max_len);

    unsigned long num_iters = 0;
    for (int i = 1; i <= max_len; i++) {
        num_iters += pow(alpha_size, i);
    }
    size_t iters = 0;
    for (unsigned long attempt = 0; attempt < num_iters; attempt++) {
        iters++;
        pass[0] = alphabet[places[0]++];
        if (strcmp(crypt(pass, salt), hash) == 0) {
            printf("%zu iterations\n", iters);
            return pass;
        }
        if (places[0] == alpha_size) {
            int i = 0;
            while (places[i] == alpha_size) {
                places[i] = 0;
                pass[i] = alphabet[places[i]];
                pass[++i] = alphabet[places[i]++];
            }
        }
    }
    printf("%s\n", pass);

    return NULL;
}
