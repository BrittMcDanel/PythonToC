#ifndef GAME_TEMP
#define GAME_TEMP

#include <SDL.h>
#include <stdbool.h>
#include "sprite.h"

typedef struct Unit {
  int hp;
  int attack;
  Sprite sprite;
} Unit;

typedef struct Array_Unit_30 {
  Unit arr[30];
  int size;
  int capacity;
} Array_Unit_30;

typedef struct Array_Unit_20 {
  Unit arr[20];
  int size;
  int capacity;
} Array_Unit_20;

Unit Unit_get_unit();
Array_Unit_20 Array_Unit_20_array_func();
Sprite Sprite_return_val_Sprite(Sprite unit);
Array_Unit_20 Array_Unit_20_return_val_Array_Unit_20(Array_Unit_20 unit);
char* char_ptr_return_val_char_ptr(char* unit);
double double_return_test_Unit_ptr(Unit* val);
double double_return_test_Unit(Unit val);
Unit Unit_arr_test_Array_Unit_30_ptr(Array_Unit_30* arr);

#endif // GAME_TEMP
