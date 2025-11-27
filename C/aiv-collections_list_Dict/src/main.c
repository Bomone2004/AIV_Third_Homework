#include <stdio.h>
#include <stdlib.h>
#include "aiv_vector.h"
#include "aiv_list.h"
#include "aiv_dict.h"

int compare_int(void* item1, void* item2) {
    int v1 = *(int*)item1;
    int v2 = *(int*)item2;
    if (v1 < v2) return -1;
    else if (v1 == v2) return 0;
    else return 1;
}

void vector_examples() {
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

    aiv_vector_add(&vector2, &array[0]);
    aiv_vector_add(&vector2, &array[1]);
    aiv_vector_add(&vector2, &array[2]);
    aiv_vector_add(&vector2, &array[3]);
    aiv_vector_add(&vector2, &array[4]);

    aiv_vector_sort_bubble(&vector2, compare_int);

    for(int i=0; i< 5; ++i) {
        printf("vector2[%d] = %d\n", i, *(int*)aiv_vector_at(&vector2, i));
    }

}

void list_examples() {
    aiv_list_t list = aiv_list_new();
    
    int i10 = 10;
    aiv_list_add(&list, &i10);

    int i20 = 20;
    aiv_list_add(&list, &i20);

    printf("Head: %d\n", *(int*)list.head->data);
    printf("Tail: %d\n", *(int*)list.tail->data);

    aiv_list_remove(&list, list.head);

    aiv_list_set_item_at(&list, 0, &i20);

    for (size_t i = 0; i < list.count; i++)
    {
        printf("Item %zu: %d\n", i, *(int*)aiv_list_get_item_at(&list, i, NULL));
    }

    aiv_list_remove_at(&list, 0);

    printf("\n");

    int i30 = 30;
    aiv_list_add(&list, &i30);

    for (size_t i = 0; i < list.count; i++)
    {
        printf("Item %zu: %d\n", i, *(int*)aiv_list_get_item_at(&list, i, NULL));
    }
}

void dict_examples() {
    aiv_dict_t dict = aiv_dict_new();

    int key1 = 1;
    int val1 = 10;

    int key2 = 2;

    aiv_dict_put(&dict, &key1, sizeof(int), &val1);
    
    printf("Dict key 1 contains: %d\n", *(int*)aiv_dict_get(&dict, &key1, sizeof(int)));
    
    printf("Dict size: %d\n", aiv_dict_get_size(&dict));

    aiv_dict_contains_key(&dict, &key1, sizeof(int)) ? 
        printf("Dict contains key\n") : 
        printf("Dict does not contain key\n");

    aiv_dict_remove(&dict, &key1, sizeof(int));

    printf("Dict size: %d\n", aiv_dict_get_size(&dict));

    aiv_dict_contains_key(&dict, &key2, sizeof(int)) ? 
        printf("Dict contains key\n") : 
        printf("Dict does not contain key\n");

    aiv_dict_destroy(&dict);
}


size_t dummy_hash(void *key, size_t keylen) {
    return 0;
}

int main() {
    
    dict_examples();

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