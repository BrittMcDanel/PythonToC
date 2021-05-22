#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <vector>

int main() {
  // make compiler
  // system("make -j8");
  int compile_status = system("./ctmain");
  printf("ct compile status %d\n", compile_status);
  if (compile_status == 0) {
    // after cpp files are generated make again to make them
    // then run the generated main file.
    system("make -j8");
    system("./game_main");
  }
}