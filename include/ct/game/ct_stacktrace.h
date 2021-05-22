#ifndef GAME_CT_STACKTRACE
#define GAME_CT_STACKTRACE

#define CT_FUNC_CAPACITY 1000
#define CT_FUNC_FILE_NAME_CAPACITY 250
#define CT_FUNC_FUNCTION_NAME_CAPACITY 250
#define CT_STACKTRACE_CAPACITY 300

typedef struct CT_Func {
  char file_name[CT_FUNC_FILE_NAME_CAPACITY];
  char function_name[CT_FUNC_FUNCTION_NAME_CAPACITY];
} CT_Func;

typedef struct CT_FuncCall {
  int ct_func_idx;
  int line_number;
} CT_FuncCall;

typedef struct CT_StackTrace {
  CT_Func funcs[CT_STACKTRACE_CAPACITY];
  CT_FuncCall func_calls[CT_STACKTRACE_CAPACITY];
  int funcs_size;
  int funcs_capacity;
  int func_calls_size;
  int func_calls_capacity;
} CT_StackTrace;

void ct_stacktrace_init(CT_StackTrace* ct_stacktrace);
void ct_stacktrace_add_function(CT_StackTrace* ct_stacktrace, char* _file_name,
                                char* _function_name);
void ct_stacktrace_push(CT_StackTrace* ct_stacktrace, int ct_func_idx,
                        int _line_number);
void ct_stacktrace_pop(CT_StackTrace* ct_stacktrace);
void ct_stacktrace_print(CT_StackTrace* ct_stacktrace);

#endif  // GAME_CT_STACKTRACE
