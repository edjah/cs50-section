/**
 * An interface for inserting and searching for integers
 * into a data structure
 */
#include <stdbool.h>

/* Returns true if `i` is in the data structure otherwise false */
bool search(int i);

/* Inserts `i` into the data structure if it doesn't already exist there */
void insert(int i);

/* Returns the number of items in the data strcture */
int size();
