#include "mylib.h"

int sum(int a, int b) {
    if (a < 0) return 0;
    return a + b;
}

bool is_min(int a, int b) {
    return a < b;
}
