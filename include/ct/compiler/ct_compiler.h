#ifndef CTCOMPILER_H
#define CTCOMPILER_H

#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum class CTCellType {
  None,
  List,
  Symbol,
  Bool,
  Int,
  Double,
  Char,
  CharPointer,
  Array,
};

class CTCell {
 public:
  string file_name;
  CTCellType cell_type;
  string token;
  // sometimes the token is set for functions to the compiled function name.
  // this is the original token value before it is set.
  string original_token;
  // set and received by macros
  string macro_param_original_token;
  string variable_type;
  string dereferenced_variable_type;
  string array_elements_type;
  bool is_r_value;
  vector<CTCell> list;
  int line_number;
  int indent;
  CTCell();
  CTCell(CTCellType _cell_type, string _token, string &_file_name,
         int _line_number, int _indent);
};

class CTLine {
 public:
  string file_name;
  string line;
  vector<string> tokens;
  int line_number;
  int indent;
  CTLine();
  CTLine(string _line, vector<string> _tokens, string &_file_name,
         int _line_number, int _indent);
};

class CTFunction {
 public:
  string file_name;
  // possibly overloaded name
  string function_name;
  // the name that gets outputted to the target language.
  // usually is return_type_function_name_params
  string compiled_function_name;
  vector<CTCell> params;
  CTCell return_type;
  vector<CTCell> params_enforced_types;
  CTCell return_enforced_type;
  // one cell for each line in the function
  // so cells[0] is the first line of the function, cells[1] is the second line,
  // etc.
  vector<CTCell> cells;
  unordered_map<string, string> local_var_type_dict;
  // member func info
  bool is_member_func;
  string stacktrace_pretty_func_name;
  string member_func_of_class_name;
  // because for only member functions, the function name gets mangled before it
  // gets mangled again into the compiled function name, this is what its name
  // was before the original mangling.
  string original_function_name;
  // c_func info
  bool is_c_func;
  string h_func_str;
  string c_func_str;
  // c_library_func info
  bool is_c_library_func;
  CTFunction();
  CTFunction(string &_file_name);
};

class CTClass {
 public:
  string file_name;
  string class_name;
  string array_elements_type;
  string array_capacity;
  vector<CTCell> member_vars;
  int array_dimensions;
  CTClass();
  CTClass(string &_file_name);
};

class CTEvalStackTraceCall {
 public:
  string function_name;
  string called_from_file_name;
  int called_on_line_number;
  CTEvalStackTraceCall();
  CTEvalStackTraceCall(string _function_name, string _called_from_file_name,
                       int _called_on_line_number);
};

class CTCompiler {
 public:
  int indent_size;
  string files_base_directory;
  string h_files_base_directory;
  string c_files_base_directory;
  string file_name_with_base_directory;
  string file_name;
  string file_contents;
  string h_file_output;
  string c_file_output;
  vector<string> compiled_files;
  vector<CTLine> file_lines;
  vector<CTCell> file_cells;
  vector<string> imported_files;
  unordered_map<string, CTFunction> function_dict;
  unordered_map<string, CTClass> class_dict;
  unordered_map<string, vector<string>> class_member_func_dict;
  // holds the enum values like ImageName_Abilities
  // the value is the enum it belogns to. ImageName_Abilities is of type
  // ImageName. ImageName is the value.
  unordered_map<string, CTCell> enum_dict;
  // holds the higher level enum name, like ImageName - not ImageName_Abilities.
  // the value is a vector of all the enum values for this enum.
  unordered_map<string, vector<CTCell>> enum_name_dict;
  unordered_map<string, vector<string>> file_import_dict;
  unordered_map<string, vector<string>> file_weak_import_dict;
  vector<CTFunction> instantiated_functions;
  vector<CTClass> class_def_insertion_order;
  vector<CTFunction> func_def_insertion_order;
  unordered_map<string, vector<CTClass>> class_array_dict;
  unordered_map<string, unordered_map<string, bool>>
      function_param_types_in_file;
  unordered_map<string, int> ct_stacktrace_function_index_dict;
  vector<CTEvalStackTraceCall> eval_func_stacktrace;
  bool is_debug;
  CTCompiler();
  CTCompiler(bool _is_debug, string _files_base_directory,
             string _h_files_base_directory, string _c_files_base_directory);
  void compile_file(string _file_name,
                    unordered_map<string, string> &ct_file_content_dict);
  void output_bounds_checking(CTFunction &ct_func, vector<CTCell> &local_vars,
                              CTCell &cell);
  void output_null_checking_for_non_params(CTFunction &ct_func,
                                           vector<CTCell> &local_vars,
                                           CTCell &cell);
  void output_c_files();
  void output_c_from_cell(CTFunction &ct_func, vector<CTCell> &local_vars,
                          CTCell &cell, bool &is_semicolon_needed);
  bool local_var_exists_in_c_output(vector<string> &local_vars, string &var);
  void change_array_files_to_class_def_file();
  void eval_main();
  void change_array_class_to_make_array(CTCell &cell);
  CTFunction expand_macro(CTFunction macro_func, CTCell &macro_cell);
  void expand_macro_for_cell(CTFunction &macro_func, CTCell &macro_cell,
                             CTCell &cell);
  string get_class_member_func_name(string &class_name, string &function_name);
  string get_stacktrace_pretty_func_name(string &class_name,
                                         string &function_name);
  string get_array_elements_type_from_string_name(string _array_class_name);
  CTCell add_array_class(CTCell &cell, string _class_file_name);
  CTCell &get_member_var(CTFunction &ct_func, CTCell &cell, CTClass &ct_class,
                         string &member_var_token);
  void print_eval_func_stacktrace();
  void print_eval_cell_info(CTFunction &ct_func, CTCell &cell);
  string replace_addr(string &line);
  vector<string> tokenize_line(string &line);
  CTCell eval_function(CTFunction &ct_func, vector<CTCell> params,
                       string &called_from_file_name,
                       int called_on_line_number);
  CTCell eval_function_cell(CTFunction &ct_func, CTCell &return_type,
                            vector<CTCell> &local_vars, CTCell &cell);
  CTCell get_local_var(vector<CTCell> &local_vars, CTCell var);
  CTCell get_local_var(vector<CTCell> &local_vars, string var_token);
  bool is_local_var(vector<CTCell> &local_vars, CTCell var);
  CTCell get_dot_notation_var(CTFunction &ct_func, vector<CTCell> &local_vars,
                              CTCell var, bool do_local_var_lookup);
  int get_instantied_function_handle(CTFunction &eval_cell_func,
                                     CTCell &eval_cell_cell,
                                     string &function_name,
                                     vector<CTCell> &params);
  int get_instantied_function_compiled_name_handle(
      string &compiled_function_name, vector<CTCell> &params);
  void update_make_file();
  void get_file_cells();
  void get_imported_files();
  void get_functions();
  void get_classes();
  void get_enums();
  void parse_c_func(string &c_func_str, bool is_library_func);
  void parse_c_library_funcs(string &c_library_funcs_str);
  void print_cell(CTCell &cell);
  void print_function_dict();
  void print_function(CTFunction &ct_func);
  void print_class_dict();
  void print_class(CTClass &ct_class);
  bool is_primitive_type(string &variable_type);
  bool is_primitive_type(CTCell &ct_cell);
  bool is_class_type(CTCell &ct_cell);
  bool is_class_type(string variable_type);
  bool is_enum(CTCell &ct_cell);
  bool is_enum(string &variable_type);
  CTCell get_enum_value(CTCell &ct_cell);
  bool is_token_a_class_type(CTCell &ct_cell);
  bool is_number(CTCell &cell);
  bool is_number(string &variable_type);
  bool is_array(CTCell &cell);
  bool is_array(string &variable_type);
  bool is_pointer(string &variable_type);
  string get_array_capacity(CTCell &cell);
  string get_array_capacity(string &variable_type);
  string get_array_elements_type(string &array_class_name);
  bool already_compiled_file(string &_file_name);
  void add_n_leading_spaces(string &s, int leading_spaces);
  string to_uppercase(string s);
  string remove_ptr_substr_if_needed(string tok);
  string format_type_for_compiled_function(string variable_type);
  CTClass &get_class(string class_name);
  CTFunction &get_instantiated_func(string compiled_function_name);
  CTCell read_from_tokens(CTLine &line);
  void replaceAll(std::string &str, const std::string &from,
                  const std::string &to);
  vector<string> string_split(const string &s, char delim);
  int num_leading_spaces(string &s);
  int num_trailing_spaces(string &s);
  void remove_leading_spaces(string &s);
  void remove_trailing_spaces(std::string &s);
  void remove_trailing_spaces_only(string &s);
};

#endif  // CTCOMPILER_H
