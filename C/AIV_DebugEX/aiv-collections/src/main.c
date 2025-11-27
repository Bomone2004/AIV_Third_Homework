#include <stdio.h>
#include <stdlib.h>
#include "aiv_vector.h"
#include "aiv_list.h"
#include "aiv_dict.h"

#include "aiv-unit.h"

AIV_UNIT_TEST(test_list_new) {
    // Initialization
    aiv_list_t list = aiv_list_new();
    //int i1 = 1; //error generator
    //aiv_list_add(&list, &i1); error generator

    // Assertion
    AIV_UNIT_PTR_IS_NULL(list.head); // implemented AIV_UNIT_IS_NULL
    AIV_UNIT_PTR_IS_NULL(list.tail);
    AIV_UNIT_SIZE_EQ(0, list.count);   // implemented AIV_UNIT_SIZET_EQ
}

AIV_UNIT_TEST(test_list_destroy) { 
    // Initialization
    aiv_list_t list = aiv_list_new();

    // Execution
    int i1 = 1;
    aiv_list_add(&list, &i1);
    aiv_list_add(&list, &i1);
    aiv_list_add(&list, &i1);
    aiv_list_add(&list, &i1);

    aiv_list_destroy(&list);

    // Assertion
    AIV_UNIT_SIZE_EQ(0,list.count);
    AIV_UNIT_PTR_IS_NULL(list.head);
    AIV_UNIT_PTR_IS_NULL(list.tail);
}

AIV_UNIT_TEST(test_list_add_one_item) {
    //  Initialization
    aiv_list_t list = aiv_list_new();
    
    // Execution
    int i1 = 1;
    aiv_list_add(&list, &i1);
    //list.tail = NULL; //error creator

    // Assertion
    AIV_UNIT_PTR_EQ(list.head,list.tail); // implemented AIV_UNIT_PTR_EQ
    AIV_UNIT_SIZE_EQ(1,list.count);
    AIV_UNIT_PTR_IS_NULL(list.head->prev);
    AIV_UNIT_PTR_IS_NULL(list.head->next);
    AIV_UNIT_IS_TRUE(list.head->data == &i1);
}

AIV_UNIT_TEST(test_list_add_two_items) {
    //  Initialization
    aiv_list_t list = aiv_list_new();
    int i1 = 1;
    aiv_list_add(&list, &i1);
    
    // Execution
    int i2 = 2;
    aiv_list_add(&list, &i2);

    // Assertion
    AIV_UNIT_IS_TRUE(list.head->data == &i1);
    AIV_UNIT_IS_TRUE(list.tail->data == &i2);
    AIV_UNIT_SIZE_EQ(2,list.count);
    AIV_UNIT_PTR_IS_NULL(list.head->prev);
    AIV_UNIT_PTR_EQ(list.head->next, list.tail);
    AIV_UNIT_PTR_EQ(list.tail->prev, list.head);
    AIV_UNIT_PTR_IS_NULL(list.tail->next);
}

AIV_UNIT_RUNNER(
    test_list_new,
    test_list_add_one_item,
    test_list_add_two_items,
    test_list_destroy
)