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

/*
    PYCompiler compiles files into the AST format called ct.
    CTCompiler compiles ct strings into c.
*/
int main() {
  auto ct_file_content_dict = unordered_map<string, string>();
  auto py_compiler = PYCompiler("../src/example/", "../src/example/");
  py_compiler.compile_file("math", ct_file_content_dict);
  auto compiler = CTCompiler(false, "../src/example/", "../src/example/", "../src/example/");
  compiler.compile_file("math", ct_file_content_dict);
  compiler.eval_main();
  compiler.output_c_files();
  return 0;
}