#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


bool rec(char last, const char *word) {
    if (*word == '\0') {
        return true;
    }
    else if (tolower(last) > tolower(*word) || !isalpha(*word)) {
        return false;
    }
    return rec(*word, word + 1);
}

bool upword(const char *word) {
    if (word == NULL) {
        return false;
    }
    return rec(*word, word);
}
