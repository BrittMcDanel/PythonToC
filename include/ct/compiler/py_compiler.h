#ifndef PYCOMPILER_H
#define PYCOMPILER_H

#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class PYCell {
 public:
  bool is_func;
  string tok;
  vector<PYCell> list;
  PYCell();
  PYCell(bool _is_func, string _tok, vector<PYCell> _list);
};

class PYLine {
 public:
  string file_name;
  string line;
  string s_expr;
  vector<string> tokens;
  int line_number;
  int indent;
  PYLine();
  PYLine(string _line, string _s_expr, vector<string> _tokens,
         string &_file_name, int _line_number, int _indent);
};

class PYFuncArgs {
 public:
  string func_name;
  int num_args;
  int num_parenths;
  PYFuncArgs();
  PYFuncArgs(string _func_name);
};

class PYCompiler {
 public:
  string files_base_directory;
  string ct_files_base_directory;
  string file_name;
  string file_contents;
  string current_enum_string;
  int line_number;
  unordered_map<string, bool> compiled_files;
  vector<PYLine> file_lines;
  vector<PYCell> output_stack;
  vector<PYCell> operator_stack;
  vector<PYFuncArgs> func_args;
  vector<PYFuncArgs> temp_func_args;
  unordered_map<string, bool> enum_values_dict;
  PYCompiler();
  PYCompiler(string _files_base_directory, string _ct_files_base_directory);
  string shunting_yard_s_expr(vector<string> &tokens, string &line);
  void set_func_args_for_line(vector<string> &tokens);
  bool is_number(string token);
  bool is_primitive_type(string &variable_type);
  void compile_file(string _file_name,
                    unordered_map<string, string> &ct_file_content_dict);
  bool is_function(string &s);
  void get_cells(vector<string> &tokens, PYCell &cell, bool do_recur_call);
  void post_process_params(PYCell &cell, PYCell &output_cell);
  void print_cell(PYCell &cell);
  void exit_if_parenths_dont_match(string &s);
  vector<string> tokenize_line(const string &line);
  string compile_enum(string line, vector<string> tokens);
  string compile_enum_member_var(string line, vector<string> tokens);
  string compile_class(string line, vector<string> tokens);
  string compile_class_member_var(string line, vector<string> tokens);
  string compile_conditional(string line, vector<string> tokens);
  string compile_for(string line, vector<string> tokens);
  string compile_while(string line, vector<string> tokens);
  string compile_import(string line, vector<string> tokens, bool is_weak_import,
                        unordered_map<string, string> &ct_file_content_dict);
  string compile_return(string line, vector<string> tokens);
  string compile_equals(string line, vector<string> tokens);
  string math_to_s_expression(string s);
  string math_to_s_expression(vector<pair<bool, string>> vals);
  string compile_function_def(string line);
  int get_num_negatives(vector<string> &tokens);
  int get_num_nots(vector<string> &tokens);
  void replace_arrays_with_make_array(vector<string> &tokens);
  void replace_first_negative_with_func(vector<string> &tokens);
  void replace_all_negatives(vector<string> &tokens);
  void replace_first_not_with_func(vector<string> &tokens);
  void replace_all_nots(vector<string> &tokens);
  bool contains_math(string &s);
  void cell_to_s_expression(PYCell &cell, string &output);
  void cell_to_s_expression(PYCell &cell, string &output, bool s_expr_math,
                            bool is_initial_cell);
  bool string_is_alpha(string &s);
  bool isOperator(char c);
  int getPriority(char c);
  bool isOperator(string s);
  int getPriority(string &s);
  string infixToPostfix(string infix);
  string infixToPrefix(string infix);
  string prefixToSExpression(vector<string> &prefix);
  vector<string> infixToPostfixStr(string infix);
  vector<string> infixToPrefixStr(string infix);
  vector<string> infixToPostfixStr(vector<pair<bool, string>> infix);
  vector<string> infixToPrefixStr(vector<pair<bool, string>> infix);
  void replaceAll(std::string &str, const std::string &from,
                  const std::string &to);
  vector<string> string_split(const string &s, char delim);
  int num_leading_spaces(string &s);
  void remove_leading_spaces(string &s);
  void remove_trailing_spaces(std::string &s);
};

#endif  // PYCOMPILER_H
