#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bst.h"

// type definition for a binary search tree node
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
} node;


// declaring the root of the tree
node *root = NULL;

// size of the tree
int tree_size = 0;

// determine whether a value is in the tree
bool search(node *n, int i) {
    if (n == NULL) {
        return false;
    }
    else if (i > n->val) {
        return search(n->right, i);
    }
    else if (i < n->val) {
        return search(n->left, i);
    }
    return true;
}

// recursively find a place to put a value in the tree
node* put(node *n, int i) {
    if (n == NULL) {
        node *new_node = calloc(1, sizeof(node));
        new_node->val = i;
        tree_size++;
        return new_node;
    }
    if (i < n->val) {
        n->left = put(n->left, i);
    }
    else if (i > n->val) {
        n->right = put(n->right, i);
    };
    return n;
}

// determine whether or not a value in the BST
bool contains(int i) {
    return search(root, i);
}

// insert a value into the BST
void insert(int i) {
    root = put(root, i);
}

// the size of the BST
int size() {
    return tree_size;
}
