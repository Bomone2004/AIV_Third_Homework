#include "mylib.h"
#include <stdio.h>
#include "aiv-unit.h"

#define TO_STRING(value) #value
//printf("Value to string: %s\n", TO_STRING(100));

/*
void assert_int_eq(int expected, int actual) {
    if (expected != actual) {
        printf("%s: expected %d but was %d [%s@%d]\n", __FUNCTION__, expected, actual, __FILE__, __LINE__);
        //puts("FAIL: test_sum_positives");
    }
}
*/
    
void test_sum_positives() {

    int expect = 3;
    int actual = sum(1, 2);

    if (expect != actual) {
        printf("%s: expected %d but was %d [%s@%d]\n", __FUNCTION__, expect, actual, __FILE__, __LINE__);

        //puts("FAIL: test_sum_positives");
    } 
}

void test_sum_negatives() {

    int expect = -3;
    int actual = sum(-1, -2);

    //test_sum_negatives: expected -3 but was 0 [src\main.c@27]
    /*
    if (expect != actual) {
        //puts("FAIL: test_sum_negatives");
        //printf("FAIL: %s\n", __FUNCTION__);
        //printf("%s: expected %d but was %d\n", __FUNCTION__, expect, actual);
        //printf("%s: expected %d but was %d [%s]\n", __FUNCTION__, expect, actual, __FILE__);
        printf("%s: expected %d but was %d [%s@%d]\n", __FUNCTION__, expect, actual, __FILE__, __LINE__);
    }
    */
   //assert_int_eq(expect, actual);
   AIV_UNIT_INT_EQ(expect, actual);
}

AIV_UNIT_TEST(test_is_a_min_b) {

//void test_is_a_min_b() {
    /*
    bool expect = true;
    bool actual = is_min(1, 2);

    if (expect != actual) {
        printf("%s: expected %s but was %s [%s@%d]\n", __FUNCTION__, "true", "false", __FILE__, __LINE__);
    }
    */
    AIV_UNIT_IS_TRUE(is_min(10, 2));
}

AIV_UNIT_RUNNER(
    test_sum_positives,
    test_sum_negatives,
    test_is_a_min_b
)

/*
int main() {

    int array[] = {1, 2, 3};

    1, 2, 3
    test_sum_positives, test_sum_negatives, test_is_a_min_b

    void (*myfunc)() = test_sum_positives

    // int result = sum(1, 2);
    // if (result == 3) puts("OK");
    // else puts("FAILEd");

    test_sum_positives();
    test_sum_negatives();
    test_is_a_min_b();
}
*/