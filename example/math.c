#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"

int int_add_int_int(int a, int b) {
    return (a + b);
}

double double_add_double_double(double a, double b) {
    return (a + b);
}

void void_loop_func_int(int size) {
    int i = 0;

    for (i = 0; i < size; i += 1) {
        printf("%s %d\n", "loop var", i);
    }
}

int main() {
    double double_value = 0.0;
    int int_value = 0;

    int_value = int_add_int_int(5, 10);
    double_value = double_add_double_double(5.0, 10.0);
    printf("%s %d %f\n", "values", int_value, double_value);
    void_loop_func_int(20);
    return 0;
}

