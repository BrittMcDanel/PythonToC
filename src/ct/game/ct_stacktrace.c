#include "ct_stacktrace.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ct_stacktrace_init(CT_StackTrace* ct_stacktrace) {
  ct_stacktrace->funcs_size = 0;
  ct_stacktrace->funcs_capacity = CT_FUNC_CAPACITY;
  ct_stacktrace->func_calls_size = 0;
  ct_stacktrace->func_calls_capacity = CT_STACKTRACE_CAPACITY;
}

void ct_stacktrace_add_function(CT_StackTrace* ct_stacktrace, char* _file_name,
                                char* _function_name) {
  if (ct_stacktrace->funcs_size > ct_stacktrace->funcs_capacity - 1) {
    printf(
        "CT_StackTrace::ct_stacktrace_add_function. size is > capacity - 1.\n");
    exit(1);
  }
  CT_Func ct_func;
  strncpy(ct_func.file_name, _file_name, CT_FUNC_FILE_NAME_CAPACITY - 1);
  strncpy(ct_func.function_name, _function_name,
          CT_FUNC_FUNCTION_NAME_CAPACITY - 1);
  ct_stacktrace->funcs[ct_stacktrace->funcs_size] = ct_func;
  ct_stacktrace->funcs_size += 1;
}

void ct_stacktrace_push(CT_StackTrace* ct_stacktrace, int ct_func_idx,
                        int _line_number) {
  // printf("push %d %d\n", ct_stacktrace->func_calls_size, ct_func_idx);
  if (ct_stacktrace->func_calls_size > ct_stacktrace->func_calls_capacity - 1) {
    printf("CT_StackTrace::ct_stacktrace_push. size is > capacity - 1.\n");
    exit(1);
  }
  CT_FuncCall func_call;
  func_call.ct_func_idx = ct_func_idx;
  func_call.line_number = _line_number;
  ct_stacktrace->func_calls[ct_stacktrace->func_calls_size] = func_call;
  ct_stacktrace->func_calls_size += 1;
}

void ct_stacktrace_pop(CT_StackTrace* ct_stacktrace) {
  // printf("pop %d\n", ct_stacktrace->func_calls_size);
  if (ct_stacktrace->func_calls_size == 0) {
    printf("CT_StackTrace::ct_stacktrace_pop. size is < 0.\n");
    exit(1);
  }
  ct_stacktrace->func_calls_size -= 1;
}

void ct_stacktrace_print(CT_StackTrace* ct_stacktrace) {
  printf("CT exit called.\n");
  for (int i = ct_stacktrace->func_calls_size - 1; i >= 0; i--) {
    CT_FuncCall* func_call = &ct_stacktrace->func_calls[i];
    int func_idx = func_call->ct_func_idx;
    if (func_idx < 0 || func_idx > ct_stacktrace->funcs_size - 1) {
      printf(
          "CT_StackTrace::ct_stacktrace_print. Func idx is out of bounds.\n");
      exit(1);
    }
    CT_Func* func = &ct_stacktrace->funcs[func_idx];
    printf("  at %s(%s:%d)\n", func->function_name, func->file_name,
           func_call->line_number + 1);
  }
}