#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct node {
    struct node* next;
} node;

typedef struct {
    double create;
    double free;
} benchmark;

benchmark test1(int num_nodes) {
    // timing the process
    clock_t start = clock();

    // creating a linked list
    node *root = NULL;
    for (int i = 0; i < num_nodes; i++) {
        node *new_node = malloc(sizeof(node));
        new_node->next = root;
        root = new_node;
    }
    clock_t mid = clock();

    // traversing across the linked list to free all of the nodes in it
    node *tmp;
    while (root != NULL) {
        tmp = root->next;
        free(root);
        root = tmp;
    }
    clock_t end = clock();

    // calculating the time it to allocate and free
    benchmark time;
    time.create = (double) (mid - start) / CLOCKS_PER_SEC;
    time.free = (double) (end - mid) / CLOCKS_PER_SEC;
    return time;
}

benchmark test2(int num_nodes) {
    // timing the process
    clock_t start = clock();

    // creating a linked list
    node *prealloc = malloc(sizeof(node) * num_nodes);
    node *root = NULL;
    for (int i = 0; i < num_nodes; i++) {
        node *new_node = prealloc + i; // same as &prealloc[i]
        new_node->next = root;
        root = new_node;
    }
    clock_t mid = clock();

    // freeing the preallocated nodes all at once
    free(prealloc);
    clock_t end = clock();

    // calculating the time it to allocate and free
    benchmark time;
    time.create = (double) (mid - start) / CLOCKS_PER_SEC;
    time.free = (double) (end - mid) / CLOCKS_PER_SEC;
    return time;
}


int main(int argc, char *argv[]) {
    // ensuring correct usage
    if (argc != 3) {
        printf("Usage: ./memory mode size\n");
        return 1;
    }

    // parsing command line args
    int mode = atoi(argv[1]);
    int size = atoi(argv[2]);

    // obtaining results and displaying them
    benchmark res;
    if (mode == 0) {
        printf("Multiple mallocs\n----------------\n");
        res = test1(size);
    }
    else {
        printf("Single malloc\n-------------\n");
        res = test2(size);
    }
    printf("Create: %.5f sec\nFree: %.5f sec\n", res.create, res.free);
}
