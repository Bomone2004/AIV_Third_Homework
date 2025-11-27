#include "aiv_vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

aiv_vector_t aiv_vector_new() {
    aiv_vector_t vector;
    vector.count = 0;
    vector.capacity = 10;
    vector.items = malloc(sizeof(void*) * vector.capacity);
    return vector;
}

void aiv_vector_destroy(aiv_vector_t* vector) {
    if (!vector->items) return;
    
    free(vector->items);
    vector->items = NULL;
    vector->count = 0;
    vector->capacity = 0;
}

void aiv_vector_add(aiv_vector_t* vector, void* item) {
    aiv_vector_reallocate(vector);

    size_t new_index = vector->count;
    vector->count++;
    //vector->items = realloc(vector->items, sizeof(void*) * vector->count);
    vector->items[new_index] = item;
}

void* aiv_vector_at(aiv_vector_t* vector, size_t index) {
    if (index >= vector->count) {
        return NULL;
    }
    return vector->items[index];
}

/*
void aiv_vector_sort_bubble(
    aiv_vector_t* vector, 
    int (*comparator)(void*, void*) ) {

        for(size_t i = 0; i < vector->count; ++i) {       // COUNT
            //void* item1 = vector->items[i]; //BUG

            for(size_t j = 0; j < vector->count; ++j) {      // COUNT  
                void* item1 = vector->items[i];                // 1
                void* item2 = vector->items[j];                // 1

                int res = comparator(item1, item2);            // 1
                if (res > 0) {                                 // 1
                    void* temp = item1;                        // 1
                    vector->items[i] = item2;                  // 1
                    vector->items[j] = temp;                   // 1
                 }
            }    
        }  
}

   6 * COUNT * COUNT 

   6 * N * N => 6 * N^2 ~ N^2 => O(N^2)
*/

void aiv_vector_sort_bubble(aiv_vector_t *vector,
                       int (*comparator)(void *, void *)) {
  for (size_t i = 0; i < vector->count; i++) {
    for (size_t j = i+1; j < vector->count; j++) {
      int comp = comparator(vector->items[i], vector->items[j]);  
      if (comp < 0) {
        void *tmp = vector->items[i];
        vector->items[i] = vector->items[j];
        vector->items[j] = tmp;
      }
    }
  }
}

void aiv_vector_remove(aiv_vector_t* vector, size_t index) {
    if (index >= vector->count) {
        return;
    }

    for (size_t i = index; i < vector->count - 1; i++) {
        vector->items[i] = vector->items[i + 1];
    }

    vector->count--;
}

void aiv_vector_insert(aiv_vector_t* vector, size_t index, void* item) {
    if (index > vector->count) {
        return;
    }

    aiv_vector_reallocate(vector);

    for (size_t i = vector->count; i > index; i--) {
        vector->items[i] = vector->items[i - 1];
        printf("Shifting index %zu to index %zu\n", i - 1, i);
    }

    vector->items[index] = item;
    vector->count++;
}

int aiv_vector_size(aiv_vector_t* vector) {
    return vector->count;
}

void aiv_vector_reallocate(aiv_vector_t* vector) {
    if (aiv_vector_size(vector) == vector->capacity) {
        return;
    }

    vector->capacity *= 2;
    vector->items = realloc(vector->items, sizeof(void*) * vector->capacity);
}

int aiv_vector_is_empty(aiv_vector_t* vector) {
    if (aiv_vector_size(vector) == 0) {
        printf("Vector is empty\n");
        return 1;
    } else {
        printf("Vector is not empty\n");
        return 0;
    }
}

#define quick_Sort arr_quickSort
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function that selects a pivot element and arranges the array
// such that elements smaller than the pivot are on the left and larger ones on the right
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // pivot is the last element
    int i = low - 1;  // Index of smaller element

    for (int j = low; j < high; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Swap the pivot element with the element at index i+1
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);  // Return the partitioning index
}

// The quicksort function that recursively sorts the subarrays
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partitioning index, arr[p] is now at the correct position
        int pi = partition(arr, low, high);

        // Recursively sort the elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

#undef quick_Sort
