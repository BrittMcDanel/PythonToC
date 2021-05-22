#include "test_file.h"

int test_add(int a, int b) { return test_add_2(&a) + b; }

int test_add_2(int* a) { return *a + 2; }