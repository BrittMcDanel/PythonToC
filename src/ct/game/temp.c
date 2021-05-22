#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "temp.h"
#include "sprite.h"

Unit Unit_get_unit() {
    Array_Sprite_5 sprite_arr = {0};
    Unit u = {0};
    return u;
}

Array_Unit_20 Array_Unit_20_array_func() {
    Array_Unit_20 arr = {0};
    return arr;
}

Sprite Sprite_return_val_Sprite(Sprite unit) {
    int first = 10;
    for (int i = 0; i < 10; i++) {
        int myvar = i;
    }
    int a = 2;
    int b = 4;
    return unit;
}

Array_Unit_20 Array_Unit_20_return_val_Array_Unit_20(Array_Unit_20 unit) {
    int first = 10;
    for (int i = 0; i < 10; i++) {
        int myvar = i;
    }
    int a = 2;
    int b = 4;
    return unit;
}

char* char_ptr_return_val_char_ptr(char* unit) {
    int first = 10;
    for (int i = 0; i < 10; i++) {
        int myvar = i;
    }
    int a = 2;
    int b = 4;
    return unit;
}

double double_return_test_Unit_ptr(Unit* val) {
    return val->sprite.anim_speed;
}

double double_return_test_Unit(Unit val) {
    return val.sprite.anim_speed;
}

Unit Unit_arr_test_Array_Unit_30_ptr(Array_Unit_30* arr) {
    Unit arr_element = arr->arr[0];
    return arr_element;
}

