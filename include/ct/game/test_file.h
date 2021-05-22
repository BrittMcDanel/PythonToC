#ifndef GAME_TEST_FILE
#define GAME_TEST_FILE

#include <SDL.h>

typedef struct TestStruct {
  int a;
} TestStruct;

typedef struct MyStruct20 {
  int val;
} MyStruct20;

int test_add(int a, int b);
int test_add_2(int* a);

#endif  // GAME_TEST_FILE