#include "aiv_vector.h"
#include "aiv_list.h"
#include <stdio.h>
#include <stdlib.h>

int compare_int(void* item1, void* item2) {
    int v1 = *(int*)item1;
    int v2 = *(int*)item2;
    if (v1 < v2) return -1;
    else if (v1 == v2) return 0;
    else return 1;
}

void Vector_example() {
    // aiv_vector_t vector;
    // aiv_vector_init(&vector);
    aiv_vector_t vector = aiv_vector_new();


    
    int i10 = 10;
    aiv_vector_add(&vector, &i10);

    void* item0 = vector.items[0];
    int* item0_int_ptr = (int*)item0;
    int item0_value = *item0_int_ptr;

    int value = *(int*)vector.items[0];
    printf("Value 0: %d\n", item0_value);
    printf("Value 0: %d\n", value);
   
    int i20 = 20;
    aiv_vector_add(&vector, &i20);
    printf("Value 1: %d\n", *(int*)vector.items[1]);

    printf("Value 2: %s\n", aiv_vector_at(&vector, 2) == NULL ? "true" : "false");

    aiv_vector_destroy(&vector);

    int array[5] = {3, 5, 2, 1, 4};
    aiv_vector_t vector2 = aiv_vector_new();

    aiv_vector_is_empty(&vector2);

    aiv_vector_add(&vector2, &array[0]);
    aiv_vector_add(&vector2, &array[1]);
    aiv_vector_add(&vector2, &array[2]);
    aiv_vector_add(&vector2, &array[3]);
    aiv_vector_add(&vector2, &array[4]);

    aiv_vector_is_empty(&vector2);

    aiv_vector_sort_bubble(&vector2, compare_int);

    for(int i=0; i< aiv_vector_size(&vector2); ++i) {
        printf("vector2[%d] = %d\n", i, *(int*)aiv_vector_at(&vector2, i));
    }

    printf("\n");
    
    aiv_vector_remove(&vector2, 2); 

    for(int i=0; i< aiv_vector_size(&vector2); ++i) {
        printf("vector2[%d] = %d\n", i, *(int*)aiv_vector_at(&vector2, i));
    }

    printf("\n");

    int intnumber = 8;

    aiv_vector_insert(&vector2, 2, &intnumber);

    for(int i=0; i< aiv_vector_size(&vector2); ++i) {
        printf("vector2[%d] = %d\n", i, *(int*)aiv_vector_at(&vector2, i));
    }

    printf("\n");

    int n = sizeof(vector2) / sizeof(*(int*)vector.items[0]);

    printf("Original array: \n");
    for(int i=0; i< aiv_vector_size(&vector2); ++i) {
        printf("vector2[%d] = %d\n", i, *(int*)aiv_vector_at(&vector2, i));
    }

    quickSort(array, 0, n - 1);

    printf("Sorted array: \n");
    for(int i=0; i< aiv_vector_size(&vector2); ++i) {
        printf("vector2[%d] = %d\n", i, *(int*)aiv_vector_at(&vector2, i));
    }

    aiv_vector_destroy(&vector2);
}

int main() {
    aiv_list_t list = aiv_list_new();

    int i10 = 10;
    aiv_list_add(&list, &i10);

    int i20 = 20;
    aiv_list_add(&list, &i10);

    puts("sdfasdf");

    printf("head value: %d\n", *(int*)list.head->data);

    puts("=== CANARY ===");
    return 0;
}   


 /*
    //int array[10]; // int* array //con memoria di 10 elementi;

    //array[0] = 1;

    typedef void* gen_t;

    gen_t array[10];
    gen_t* array_ptr;

    void* * array_ptrptr;


    typedef char* string_t;
    char* * argv;

    string_t* argv_ptr;
`   */