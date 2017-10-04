#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void qsort_rec(int *a, int start, int end) {
    if (end - start <= 1) {
        return;
    }

    // partition the array by a pivot
    int pivot = a[start];
    int head = start + 1;
    int tail = end - 1;
    while (head <= tail) {
        if (a[head] > pivot) {
            swap(a, head, tail--);
        } else {
            head++;
        }
    }

    // put the pivot in the middle of the two halves
    swap(a, start, head - 1);

    // sort the left and right halves recursively
    qsort_rec(a, start, head - 1);
    qsort_rec(a, head, end);

}

void quicksort(int *a, int size) {
    qsort_rec(a, 0, size);
}

void randomized_quicksort(int *a, int size) {
    for (int i = 0; i < size - 1; i++) {
        swap(a, i, i + rand() % (size - i));
    }
    quicksort(a, size);
}

void msort_rec(int *a, int *buffer, int start, int end) {
    // base case is sort one or two elements
    if (end - start <= 1) {
        return;
    }

    // sort the two halves
    int middle = (start + end) / 2;
    msort_rec(a, buffer, start, middle);
    msort_rec(a, buffer, middle, end);

    // merge the two halves
    int length = end - start;
    memcpy(buffer, a + start, sizeof(int) * length);
    int x = 0, y = length / 2;
    while (x < length / 2 && y < length) {
        if (buffer[x] < buffer[y]) {
            a[start++] = buffer[x++];
        }
        else {
            a[start++] = buffer[y++];
        }
    }

    // get any of the remaining elements from either half
    while (x < length / 2) {
        a[start++] = buffer[x++];
    }
    while (y < length) {
        a[start++] = buffer[y++];
    }
}

void mergesort(int *a, int size) {
    int *buffer = malloc(sizeof(int) * size);
    msort_rec(a, buffer, 0, size);
    free(buffer);
}


int compare(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

void builtinsort(int *a, int size) {
    qsort(a, size, sizeof(int), compare);
}

void insertionsort(int *a, int size) {
    int j, key;
    for (int i = 1; i < size; i++) {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j--];
        }
        a[j + 1] = key;
    }
}

void selectionsort(int *a, int size) {
    int min_idx;
    for (int i = 0; i < size - 1; i++) {
        min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        swap(a, min_idx, i);
    }
}

void bubblesort(int *a, int size) {
    int swapped = 1;
    while (swapped) {
        swapped = 0;
        for (int i = 0; i < size - 1; i++)  {
            if (a[i] > a[i + 1]) {
               swap(a, i, i + 1);
               swapped = 1;
            }
        }
    }
}
