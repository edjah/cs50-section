#include "brute2.h"

int main(int argc, char *argv[]) {
    // ensuring correct usage
    if (argc < 2 || strcmp(argv[1], "-h") == 0) {
        printf("Usage: ./brute hash [max_len] [alphabet]\n");
        return 1;
    }

    // parsing command line arguments
    char *hashed_pass = argv[1];
    int max_password_length = 4;
    if (argc >= 3) {
        max_password_length = atoi(argv[2]);
    }
    if (argc >= 4) {
        alphabet = argv[3];
        alpha_size = strlen(alphabet);
    }

    // decrypting the hash
    printf("%s\n", brute_force(hashed_pass, max_password_length));
    return 0;
}
