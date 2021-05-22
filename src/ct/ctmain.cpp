#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <chrono>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "compiler/ct_compiler.h"
#include "compiler/py_compiler.h"
using namespace std;

int main() {
  auto t1 = std::chrono::high_resolution_clock::now();
  // create a dict with the file name and ct file contents so that the
  // python compiler doens't need to write the ct file and the ct compiler
  // doesn't need to read the ct file, can just reuse the string.
  auto ct_file_content_dict = unordered_map<string, string>();
  auto py_compiler = PYCompiler("../src/ct/src/", "../src/ct/ct_src/");
  py_compiler.compile_file("game_main", ct_file_content_dict);
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
  std::cout << "Compiled py files in: " << (duration / 1000.0) << "s" << endl;
  auto t3 = std::chrono::high_resolution_clock::now();
  auto compiler = CTCompiler(true, "../src/ct/ct_src/", "../include/ct/game/",
                             "../src/ct/game/");
  compiler.compile_file("game_main", ct_file_content_dict);
  compiler.eval_main();
  compiler.output_c_files();
  compiler.update_make_file();
  auto t4 = std::chrono::high_resolution_clock::now();
  duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count();
  std::cout << "Compiled ct files in: " << (duration / 1000.0) << "s" << endl;
  duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t1).count();
  std::cout << "Compiled all files in: " << (duration / 1000.0) << "s" << endl;
  return 0;
}