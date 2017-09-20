#define MAX_LEN 4
#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "brute.h"

char* dictionary_attack(char *hash, FILE *fp) {
    char *buffer = malloc(100);
    char salt[3] = {hash[0], hash[1], '\0'};
    while (fgets(buffer, 100, fp)) {
        buffer[strlen(buffer) - 1] = '\0';
        if (strcmp(crypt(buffer, salt), hash) == 0) {
            return buffer;
        }

    }
    return NULL;
}

int main(int argc, char *argv[]) {
    // ensure correct usage
    if (argc < 2 || strcmp(argv[1], "-h") == 0) {
        printf("Usage: ./crack hash [dictionary]\n");
        return 1;
    }

    // parse command line args
    char *hash = argv[1];
    char *dictionary = argc >= 3 ? argv[2] : "dictionary.txt";

    // attempt a dictionary attack
    if (dictionary) {
        FILE *fp = fopen(dictionary, "r");
        if (!fp) {
            printf("Failed to open %s\n", dictionary);
        }
        else {
            char *result = dictionary_attack(hash, fp);
            fclose(fp);
            if (result) {
                printf("%s\n", result);
                return 0;
            }
            printf("Dictionary attack failed. Attempting brute force.\n");
        }
    }

    printf("%s\n", brute_force(hash, MAX_LEN));
}
