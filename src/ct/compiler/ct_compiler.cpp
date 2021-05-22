#include "ct_compiler.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <streambuf>
#include <string>

CTCell::CTCell() {
  cell_type = CTCellType::None;
  token = string("");
  original_token = string("");
  macro_param_original_token = string("");
  variable_type = string("undefined");
  dereferenced_variable_type = string("undefined");
  array_elements_type = string("undefined");
  is_r_value = true;
  list = vector<CTCell>();
  line_number = -1;
  indent = -1;
}

CTCell::CTCell(CTCellType _cell_type, string _token, string &_file_name,
               int _line_number, int _indent) {
  cell_type = _cell_type;
  token = _token;
  original_token = _token;
  macro_param_original_token = string("");
  variable_type = string("undefined");
  dereferenced_variable_type = string("undefined");
  array_elements_type = string("undefined");
  is_r_value = true;
  list = vector<CTCell>();
  file_name = _file_name;
  line_number = _line_number;
  indent = _indent;
}

CTLine::CTLine() {
  line = string("");
  line_number = -1;
  indent = -1;
}

CTLine::CTLine(string _line, vector<string> _tokens, string &_file_name,
               int _line_number, int _indent) {
  line = _line;
  tokens = _tokens;
  file_name = _file_name;
  line_number = _line_number;
  indent = _indent;
}

CTFunction::CTFunction() {
  file_name = string("");
  function_name = string("");
  stacktrace_pretty_func_name = string("");
  params = vector<CTCell>();
  return_type = CTCell();
  cells = vector<CTCell>();
  local_var_type_dict = unordered_map<string, string>();
  params_enforced_types = vector<CTCell>();
  return_enforced_type = CTCell();
  is_member_func = false;
  member_func_of_class_name = string("");
  original_function_name = string("");
  is_c_func = false;
  h_func_str = string("");
  c_func_str = string("");
  is_c_library_func = false;
}

CTFunction::CTFunction(string &_file_name) {
  file_name = _file_name;
  function_name = string("");
  stacktrace_pretty_func_name = string("");
  params = vector<CTCell>();
  return_type = CTCell();
  cells = vector<CTCell>();
  local_var_type_dict = unordered_map<string, string>();
  params_enforced_types = vector<CTCell>();
  return_enforced_type = CTCell();
  is_member_func = false;
  member_func_of_class_name = string("");
  original_function_name = string("");
  is_c_func = false;
  h_func_str = string("");
  c_func_str = string("");
  is_c_library_func = false;
}

CTClass::CTClass() {
  file_name = string("");
  class_name = string("");
  array_elements_type = string("undefined");
  array_capacity = string("capacity-undefined");
  member_vars = vector<CTCell>();
  array_dimensions = 0;
}

CTClass::CTClass(string &_file_name) {
  file_name = _file_name;
  class_name = string("");
  array_elements_type = string("undefined");
  array_capacity = string("capacity-undefined");
  member_vars = vector<CTCell>();
  array_dimensions = 0;
}

CTEvalStackTraceCall::CTEvalStackTraceCall() {
  function_name = string("");
  called_from_file_name = string("");
  called_on_line_number = -1;
}

CTEvalStackTraceCall::CTEvalStackTraceCall(string _function_name,
                                           string _called_from_file_name,
                                           int _called_on_line_number) {
  function_name = _function_name;
  called_from_file_name = _called_from_file_name;
  called_on_line_number = _called_on_line_number;
}

CTCompiler::CTCompiler() {
  is_debug = true;
  indent_size = 4;
  files_base_directory = string("");
  h_files_base_directory = string("");
  c_files_base_directory = string("");
  file_name = string("");
  file_name_with_base_directory = string("");
  file_contents = string("");
  compiled_files = vector<string>();
  file_lines = vector<CTLine>();
  file_cells = vector<CTCell>();
  function_dict = unordered_map<string, CTFunction>();
  class_dict = unordered_map<string, CTClass>();
  class_member_func_dict = unordered_map<string, vector<string>>();
  enum_dict = unordered_map<string, CTCell>();
  enum_name_dict = unordered_map<string, vector<CTCell>>();
  file_import_dict = unordered_map<string, vector<string>>();
  file_weak_import_dict = unordered_map<string, vector<string>>();
  imported_files = vector<string>();
  instantiated_functions = vector<CTFunction>();
  class_def_insertion_order = vector<CTClass>();
  func_def_insertion_order = vector<CTFunction>();
  class_array_dict = unordered_map<string, vector<CTClass>>();
  function_param_types_in_file =
      unordered_map<string, unordered_map<string, bool>>();
  ct_stacktrace_function_index_dict = unordered_map<string, int>();
  eval_func_stacktrace = vector<CTEvalStackTraceCall>();
  h_file_output = string("");
  c_file_output = string("");
}

CTCompiler::CTCompiler(bool _is_debug, string _files_base_directory,
                       string _h_files_base_directory,
                       string _c_files_base_directory) {
  is_debug = _is_debug;
  indent_size = 4;
  files_base_directory = _files_base_directory;
  h_files_base_directory = _h_files_base_directory;
  c_files_base_directory = _c_files_base_directory;
  file_name = string("");
  file_name_with_base_directory = string("");
  file_contents = string("");
  compiled_files = vector<string>();
  file_lines = vector<CTLine>();
  file_cells = vector<CTCell>();
  function_dict = unordered_map<string, CTFunction>();
  class_dict = unordered_map<string, CTClass>();
  class_member_func_dict = unordered_map<string, vector<string>>();
  enum_dict = unordered_map<string, CTCell>();
  enum_name_dict = unordered_map<string, vector<CTCell>>();
  file_import_dict = unordered_map<string, vector<string>>();
  file_weak_import_dict = unordered_map<string, vector<string>>();
  imported_files = vector<string>();
  instantiated_functions = vector<CTFunction>();
  class_def_insertion_order = vector<CTClass>();
  func_def_insertion_order = vector<CTFunction>();
  class_array_dict = unordered_map<string, vector<CTClass>>();
  function_param_types_in_file =
      unordered_map<string, unordered_map<string, bool>>();
  ct_stacktrace_function_index_dict = unordered_map<string, int>();
  eval_func_stacktrace = vector<CTEvalStackTraceCall>();
  h_file_output = string("");
  c_file_output = string("");
}

CTCell &CTCompiler::get_member_var(CTFunction &ct_func, CTCell &cell,
                                   CTClass &ct_class,
                                   string &member_var_token) {
  for (auto &member_var : ct_class.member_vars) {
    if (member_var.token == member_var_token) {
      return member_var;
    }
  }
  printf(
      "CTClass::get_member_var. Member var '%s' for class '%s' is undefined.\n",
      member_var_token.c_str(), ct_class.class_name.c_str());
  print_eval_cell_info(ct_func, cell);
  abort();
  return ct_class.member_vars.at(0);
}

void CTCompiler::compile_file(
    string _file_name, unordered_map<string, string> &ct_file_content_dict) {
  if (already_compiled_file(_file_name)) {
    // printf("Already compiled top file %s, returning.\n", _file_name.c_str());
    return;
  }
  // make sure the py compiler compiled the file into ct
  if (ct_file_content_dict.find(_file_name) == ct_file_content_dict.end()) {
    printf(
        "CTCompiler::compile_file. File name is not in the "
        "ct_file_content_dict. File name: '%s'\n",
        _file_name.c_str());
    abort();
  }
  file_name = _file_name;
  // printf("ct - compiling file_name %s\n", _file_name.c_str());
  // clear previous compilation data from a different file
  file_lines.clear();
  file_cells.clear();
  imported_files.clear();
  function_param_types_in_file[_file_name] = unordered_map<string, bool>();

  file_name_with_base_directory = files_base_directory + _file_name + ".ct";
  compiled_files.push_back(_file_name);
  /*ifstream inFile;
  inFile.open(file_name_with_base_directory.c_str());
  if (!inFile.good()) {
    printf("CTCompiler - file not found. file_name: %s\n",
           file_name_with_base_directory.c_str());
    abort();
  }*/
  auto imported_dict_it = file_import_dict.find(file_name);
  if (imported_dict_it == file_import_dict.end()) {
    file_import_dict[file_name] = vector<string>();
  }
  auto imported_weak_dict_it = file_weak_import_dict.find(file_name);
  if (imported_weak_dict_it == file_weak_import_dict.end()) {
    file_weak_import_dict[file_name] = vector<string>();
  }

  istringstream f(ct_file_content_dict[file_name]);
  string line;
  int line_number = 0;
  auto parsing_c_func = false;
  auto parsing_c_library_funcs = false;
  string c_func_str = "";
  string c_library_funcs_str = "";
  while (getline(f, line, '\n')) {
    if (line == "<c_func>" && parsing_c_func) {
      printf(
          "CTCompiler::compile_file. Cannot nest <c_func> tags. filename: %s\n",
          file_name.c_str());
      abort();
    } else if (line == "</c_func>" && !parsing_c_func) {
      printf(
          "CTCompiler::compile_file. Found closing </c_func> tag, but had no "
          "matching <c_func> tag. filename: %s\n",
          file_name.c_str());
      abort();
    } else if (line == "<c_func>") {
      parsing_c_func = true;
      line_number += 1;
      continue;
    } else if (line == "</c_func>") {
      parsing_c_func = false;
      line_number += 1;
      parse_c_func(c_func_str, false);
      c_func_str.clear();
      continue;
    } else if (parsing_c_func) {
      c_func_str += line;
      line_number += 1;
      continue;
    } else if (line == "<c_library_funcs>" && parsing_c_library_funcs) {
      printf(
          "CTCompiler::compile_file. Cannot nest <c_library_funcs> tags. "
          "filename: %s\n",
          file_name.c_str());
      abort();
    } else if (line == "</c_library_funcs>" && !parsing_c_library_funcs) {
      printf(
          "CTCompiler::compile_file. Found closing </c_library_funcs> tag, but "
          "had no "
          "matching <c_library_funcs> tag. filename: %s\n",
          file_name.c_str());
      abort();
    } else if (line == "<c_library_funcs>") {
      parsing_c_library_funcs = true;
      line_number += 1;
      continue;
    } else if (line == "</c_library_funcs>") {
      parsing_c_library_funcs = false;
      line_number += 1;
      parse_c_library_funcs(c_library_funcs_str);
      c_library_funcs_str.clear();
      continue;
    } else if (parsing_c_library_funcs) {
      c_library_funcs_str += line;
      line_number += 1;
      continue;
    }

    auto indent = num_leading_spaces(line);
    remove_leading_spaces(line);
    // just in case there were any trailing spaces
    remove_trailing_spaces(line);
    if (line.size() > 0 && line.at(0) == ';') {
      line_number += 1;
      continue;
    }
    // empty lines need parenths
    if (line.size() == 0) {
      line.insert(0, 1, '(');
      line.push_back(')');
    }
    replaceAll(line, "(", "( ");
    replaceAll(line, ")", " )");
    // replaces empty lists with a single space, because the replaces above will
    // add two spaces ("(  )" => "( )"). empty param lists need a single space,
    // not two spaces - defun my_func ()
    replaceAll(line, "(  )", "( )");
    file_lines.push_back(
        CTLine(line, tokenize_line(line), file_name, line_number, indent));
    line_number += 1;
  }
  // push one empty line at the end so that scopes can close
  file_lines.push_back(
      CTLine("( )", string_split("( )", ' '), file_name, line_number, 0));

  /*stringstream strStream;
  strStream << inFile.rdbuf();
  file_contents = strStream.str();*/

  /*for (auto &l : file_lines) {
    printf("%d - %d - %s\n", l.line_number, l.indent, l.line.c_str());
  }
  for (auto &l : file_lines) {
    printf("tokens %d - %d - ", l.line_number, l.indent);
    for (auto &token : l.tokens) {
      printf("%s ", token.c_str());
    }
    printf("\n");
  }*/

  get_file_cells();
  get_imported_files();
  get_enums();
  get_classes();
  get_functions();
  // print_class_dict();
  // print_function_dict();

  // make a copy of imported files because when the imported file is compiled
  // the imported files will be cleared in order to process the new file.
  auto imported_files_copy = imported_files;
  for (auto &imported_file : imported_files_copy) {
    if (already_compiled_file(imported_file)) {
      // printf("Already compiled %s - continuing\n", imported_file.c_str());
      continue;
    }
    compile_file(imported_file, ct_file_content_dict);
  }
}

void CTCompiler::eval_main() {
  // printf("\n-- Evaluating main function --\n\n");
  auto params = vector<CTCell>();
  auto called_from_file_name = string("game_main");
  auto return_type =
      eval_function(function_dict["main"], params, called_from_file_name, 0);
  auto instantiated_func = function_dict["main"];
  instantiated_func.compiled_function_name = "main";
  return_type = CTCell(CTCellType::Int, "0", instantiated_func.file_name, 0, 0);
  return_type.variable_type = "int";
  instantiated_func.return_type = return_type;
  instantiated_functions.push_back(instantiated_func);
}

void CTCompiler::parse_c_library_funcs(string &c_library_funcs_str) {
  auto func_str = string("");
  for (int i = 0; i < c_library_funcs_str.size(); i++) {
    auto c = c_library_funcs_str[i];
    if (c == ';') {
      parse_c_func(func_str, true);
      func_str.clear();
    } else {
      func_str.push_back(c);
    }
  }
}

void CTCompiler::parse_c_func(string &c_func_str, bool is_library_func) {
  auto signature_str = string("");
  // if the function signature is multiline, the spaces up until the next part
  // of the signature can contain many spaces, we only want one space at a time,
  // not two spaces at a time as it will mess up the string split. Example:
  // func(int a, int b,
  //      int c)
  // before int c there are many spaces
  bool prev_char_was_space = false;
  for (int i = 0; i < c_func_str.size(); i++) {
    auto c = c_func_str.at(i);
    if (prev_char_was_space && c == ' ') {
      continue;
    }
    if (c == ' ') {
      prev_char_was_space = true;
    } else {
      prev_char_was_space = false;
    }
    // prevent unnecessary space in the header file before the ';'
    if ((i <= c_func_str.size() - 2 && c == ' ' &&
         c_func_str.at(i + 1) == '{') ||
        c == '{') {
      break;
    } else {
      signature_str.push_back(c);
    }
  }

  auto signature_str_cpy = signature_str;
  replaceAll(signature_str, "(", " ( ");
  replaceAll(signature_str, ")", " ) ");
  auto signature_split = string_split(signature_str, ' ');
  auto signature_split_cpy = signature_split;

  // add struct for pointer params (i.e Game* game becomes struct Game* game)
  for (int i = signature_split_cpy.size() - 1; i > -1; i--) {
    auto &tok = signature_split_cpy.at(i);
    if (tok.find("*") != string::npos) {
      // struct is not needed for char or primitives passed by pointer
      auto value = tok;
      value.pop_back();
      // if the value without a pointer is a primitive don't do struct
      if (!(is_primitive_type(tok) || is_primitive_type(value))) {
        signature_split_cpy.insert(signature_split_cpy.begin() + i, "struct");
      }
    }
  }
  auto rebuilt_h_signature = string("");
  for (int i = 0; i < signature_split_cpy.size(); i++) {
    auto &tok = signature_split_cpy.at(i);
    // printf("%ld %s\n", tok.size(), tok.c_str());
    rebuilt_h_signature += tok;
    // don't add a space if the next tok is a parenths (continue)
    if (i <= signature_split_cpy.size() - 2) {
      auto &next_tok = signature_split_cpy.at(i + 1);
      if (next_tok == "(" || next_tok == ")") {
        continue;
      }
    }
    if (tok == "(" || tok == ")") {
      continue;
    }
    rebuilt_h_signature += " ";
  }
  // printf("rebuilt h str: %s\n", rebuilt_h_signature.c_str());
  auto func_it = function_dict.find(signature_split.at(1));
  if (func_it != function_dict.end()) {
    printf(
        "CTCompiler::parse_c_func. c_func '%s' has already been defined. Make "
        "sure c blocks are executed before intellisense only functions.\n",
        signature_split.at(1).c_str());
    abort();
  }
  auto ct_func = CTFunction();
  ct_func.is_c_library_func = is_library_func;
  ct_func.is_c_func = !is_library_func;
  ct_func.h_func_str = rebuilt_h_signature;
  ct_func.c_func_str = c_func_str;
  ct_func.file_name = file_name;
  ct_func.compiled_function_name = signature_split.at(1);
  ct_func.function_name = signature_split.at(1);
  ct_func.return_type =
      CTCell(CTCellType::Symbol, signature_split.at(0), file_name, -1, -1);
  ct_func.return_type.variable_type = signature_split.at(0);
  ct_func.return_enforced_type =
      CTCell(CTCellType::Symbol, signature_split.at(0), file_name, -1, -1);
  ct_func.return_enforced_type.variable_type = signature_split.at(0);

  auto iters = 0;
  auto idx = 3;
  CTCell variable_cell = CTCell(CTCellType::Symbol, "", file_name, -1, -1);
  while (idx <= signature_split.size() - 1 &&
         signature_split.at(idx).find(")") == string::npos) {
    iters += 1;
    if (iters > 500) {
      printf("CTCompiler::parse_c_func. iters > 500.\n");
      abort();
    }
    if (signature_split.at(idx).size() == 0) {
      // this happens when a function has no params, i'm not sure if it happens
      // on multiline function signatures, but I think I fixed that. Fix later
      // if it becomes a problem. I'm not sure its a problem right now.
      /*printf(
          "CTCompiler::parse_c_func. A token in the function signature has "
          "size 0. The entire signature must be on one line. %s\n",
          signature_str.c_str());*/
      // abort();
    }
    if (idx % 2 == 0) {
      variable_cell.token = signature_split.at(idx);
      if (variable_cell.token.size() > 0 && variable_cell.token.at(0) == '*') {
        printf(
            "CTCompiler::parse_c_func. Func signature error: Pointer types "
            "needs to be on the type, "
            "not the variable. I.e. char* val instead of char * val.\n "
            "Variable name: %s\n",
            variable_cell.token.c_str());
        abort();
      }
      ct_func.params.push_back(variable_cell);
      ct_func.params_enforced_types.push_back(variable_cell);
    } else {
      variable_cell.variable_type = signature_split.at(idx);
      if (variable_cell.variable_type.find("const") != string::npos) {
        printf(
            "CTCompiler::parse_c_func. Func signature error: Don't use const "
            "in c func blocks. I am "
            "not parsing that yet.\n ");
        abort();
      }
    }
    idx += 1;
  }

  // add c func to function dict and insertion order dict
  instantiated_functions.push_back(ct_func);
  function_dict[ct_func.function_name] = ct_func;
  func_def_insertion_order.push_back(ct_func);
}

string CTCompiler::replace_addr(string &line) { return string(""); }

vector<string> CTCompiler::tokenize_line(string &line) {
  auto toks = vector<string>();
  auto split = string_split(line, ' ');
  auto char_ptr_str = string("");
  auto parsing_char_ptr = false;
  // parsing strings into a single tok even if they contain spaces
  for (auto &s : split) {
    if (s.size() == 0) {
      continue;
    }
    if (s.at(0) == '"') {
      parsing_char_ptr = true;
    }
    if (parsing_char_ptr) {
      char_ptr_str += s;
    } else {
      toks.push_back(s);
    }
    if (parsing_char_ptr && s.at(s.size() - 1) == '"') {
      parsing_char_ptr = false;
      toks.push_back(char_ptr_str);
      char_ptr_str = "";
    } else if (parsing_char_ptr) {
      char_ptr_str += " ";
    }
  }

  // arr idxing arr[0]
  for (int i = toks.size() - 1; i > -1; i--) {
    auto &tok = toks.at(i);
    if (tok.size() == 0) {
      printf("CTCompiler::tokenize_line. tok size is '0'.\n");
      abort();
    }
    // min size is v[0] - 4 tokens with a 1 char var name
    if (tok.size() >= 4 && tok.at(tok.size() - 1) == ']') {
      auto contains_l_parenths = tok.find('(') != string::npos;
      auto contains_r_parenths = tok.find(')') != string::npos;
      if (contains_l_parenths || contains_r_parenths) {
        printf(
            "CTCompiler::tokenize_line. [] syntax for arrays cannot operate on "
            "a function. For example, (func_call a b)[0] is not allowed. only "
            "arr[0] is.\n");
        abort();
      }
      auto t = tok;
      auto t_first_char = string("") + t.at(0);
      auto is_addr_or_deref = t.at(0) == '&' || t.at(0) == '*';
      if (is_addr_or_deref) {
        t.erase(t.begin());
      }
      auto t_split = string_split(t, '[');
      auto arr = t_split.at(0);
      auto number_str = string("");
      auto parsing_num = false;
      for (auto c : t) {
        if (c == '[') {
          parsing_num = true;
          continue;
        }
        if (c == ']') {
          parsing_num = false;
          break;
        }
        if (parsing_num) {
          number_str += c;
        }
      }

      toks.erase(toks.begin() + i);
      toks.insert(toks.begin() + i, ")");
      toks.insert(toks.begin() + i, number_str);
      toks.insert(toks.begin() + i, arr + ".arr");
      toks.insert(toks.begin() + i, "value_at");
      if (is_addr_or_deref) {
        toks.insert(toks.begin() + i, t_first_char + "(");
      } else {
        toks.insert(toks.begin() + i, "(");
      }
    }
  }

  /*
    commenting this out for now becaue the * was causing problems for pointers
    in classes if a mistake was made.

    Example:
    SDL_Window *window;

    will try to deref the window. The base langauge should just auto put the
    deref function call instead of * when compiling into ct, so this should be
    fine.
  */
  // addrs
  /*for (int i = toks.size() - 1; i > -1; i--) {
    auto &tok = toks.at(i);
    if (tok.size() == 0) {
      printf("CTCompiler::tokenize_line. tok size is '0'.\n");
      abort();
    }
    if (tok.at(0) == '&' && tok.size() > 1) {
      auto is_function_addr = tok.at(1) == '(';
      if (!is_function_addr) {
        tok += " )";
      }
      tok.erase(tok.begin());
      tok.insert(0, "( & ");
      auto tok_split = string_split(tok, ' ');
      // delete tok with spaces in it
      toks.erase(toks.begin() + i);
      // replace with each str in the split of the tok, backwards because
      // the first token needs to appear first in the vec.
      for (int j = tok_split.size() - 1; j > -1; j--) {
        toks.insert(toks.begin() + i, tok_split.at(j));
      }
      // this case is &(some_func p1 p2 ...)
      // start at the first parenths and go until you reach the closing parenths
      // for it. Then add another closing parenths for the newly formed "( & "
      // tok.
      if (is_function_addr) {
        auto parenths = 1;
        // i + 1 to start at the func call list
        for (int s = i + 1; s < toks.size(); s++) {
          auto &t = toks.at(s);
          if (t == "(") {
            parenths += 1;
          } else if (t == ")") {
            parenths -= 1;
          }
          if (parenths == 0) {
            toks.insert(toks.begin() + s, ")");
            break;
          }
        }
      }
    }
  }

  // derefs
  for (int i = toks.size() - 1; i > -1; i--) {
    auto &tok = toks.at(i);
    if (tok.size() == 0) {
      printf("CTCompiler::tokenize_line. tok size is '0'.\n");
      abort();
    }
    // tok size > 1 to differentiate it from muls ( * 2 3 4 5 ),
    // where the first mul token will be by itself with size 1.
    if (tok.at(0) == '*' && tok.size() > 1) {
      auto is_function_addr = tok.at(1) == '(';
      if (!is_function_addr) {
        tok += " )";
      }
      // erase first * char
      tok.erase(tok.begin());
      tok.insert(0, "( * ");
      auto tok_split = string_split(tok, ' ');
      // delete tok with spaces in it
      toks.erase(toks.begin() + i);
      // replace with each str in the split of the tok, backwards because
      // the first token needs to appear first in the vec.
      for (int j = tok_split.size() - 1; j > -1; j--) {
        toks.insert(toks.begin() + i, tok_split.at(j));
      }
      // this case is &(some_func p1 p2 ...)
      // start at the first parenths and go until you reach the closing parenths
      // for it. Then add another closing parenths for the newly formed "( & "
      // tok.
      if (is_function_addr) {
        auto parenths = 1;
        // i + 1 to start at the func call list
        for (int s = i + 1; s < toks.size(); s++) {
          auto &t = toks.at(s);
          if (t == "(") {
            parenths += 1;
          } else if (t == ")") {
            parenths -= 1;
          }
          if (parenths == 0) {
            toks.insert(toks.begin() + s, ")");
            break;
          }
        }
      }
    }
  }*/

  return toks;
}

void CTCompiler::get_file_cells() {
  for (auto &l : file_lines) {
    // printf("%d - %d - %s\n", l.line_number, l.indent, l.line.c_str());
    auto l_cpy = l;
    auto cell = read_from_tokens(l_cpy);
    change_array_class_to_make_array(cell);
    // print_cell(cell);
    file_cells.push_back(cell);
  }
}

void CTCompiler::change_array_class_to_make_array(CTCell &cell) {
  if (cell.cell_type == CTCellType::List) {
    if (cell.list.size() > 0) {
      auto &first_cell = cell.list.at(0);
      for (int i = 0; i < cell.list.size(); i++) {
        auto &c = cell.list.at(i);
        if (first_cell.token.find("Array") != string::npos) {
          if (cell.list.size() != 2) {
            printf(
                "CTCompiler::change_array_class_to_make_array. Expected a list "
                "of size '2' when 'Array' is the first token in the list "
                "(ArrayType capacity). "
                "Found size '%ld'\n",
                cell.list.size());
            abort();
          }
          auto arr_idx = first_cell.token.find("Array");
          auto type_str = first_cell.token.substr(0, arr_idx);
          first_cell.token = "make_array";
          cell.list.insert(cell.list.begin() + 1,
                           CTCell(CTCellType::Symbol, type_str, cell.file_name,
                                  cell.line_number, cell.indent));
        } else {
          change_array_class_to_make_array(c);
        }
      }
    }
  } else {
  }
}

// pass a copy of params because the variable name token will be changed to
// match the function's variable name parameter
CTCell CTCompiler::eval_function(CTFunction &ct_func, vector<CTCell> params,
                                 string &called_from_file_name,
                                 int called_on_line_number) {
  auto function_dict_it = function_dict.find(ct_func.function_name);
  if (function_dict_it == function_dict.end()) {
    printf("CTCompiler::eval_function. function '%s' is undefined.\n",
           ct_func.function_name.c_str());
    print_eval_func_stacktrace();
    abort();
  }
  if (ct_func.params.size() != params.size()) {
    printf(
        "CTCompiler::eval_function. %s expects '%ld' params, found '%ld' "
        "params.\n",
        ct_func.function_name.c_str(), ct_func.params.size(), params.size());
    print_eval_func_stacktrace();
    abort();
  }
  // make passed in params have the same variable name as the function params
  for (int i = 0; i < params.size(); i++) {
    auto &param = params.at(i);
    param.token = ct_func.params.at(i).token;
    ct_func.local_var_type_dict[param.token] = param.variable_type;
  }
  auto return_type =
      CTCell(CTCellType::None, "return type", ct_func.file_name, 0, 0);
  return_type.variable_type = "void";
  auto indent = 0;
  eval_func_stacktrace.push_back(
      CTEvalStackTraceCall(ct_func.stacktrace_pretty_func_name,
                           called_from_file_name, called_on_line_number));
  // start at 1 to skip the defun line
  for (int i = 1; i < ct_func.cells.size(); i++) {
    auto &cell = ct_func.cells.at(i);
    // print_cell(cell);
    // printf("\n");
    if (cell.cell_type != CTCellType::List) {
      printf("CTCompiler::eval_function. Cell was not a list.\n");
      abort();
    }
    if (cell.list.size() == 0) {
      printf("CTCompiler::eval_function. List size is '0'.\n");
      abort();
    }
    indent = cell.indent;
    eval_function_cell(ct_func, return_type, params, ct_func.cells.at(i));
  }
  eval_func_stacktrace.pop_back();
  return return_type;
}

void CTCompiler::print_eval_func_stacktrace() {
  printf("--CTCompiler::print_eval_func_stacktrace--\n");
  for (int i = eval_func_stacktrace.size() - 1; i > -1; i--) {
    auto &f = eval_func_stacktrace.at(i);
    printf("  at %s(%s:%d)\n", f.function_name.c_str(),
           f.called_from_file_name.c_str(), f.called_on_line_number);
  }
}

bool CTCompiler::is_number(CTCell &cell) {
  return cell.variable_type == "int" || cell.variable_type == "Uint8" ||
         cell.variable_type == "Uint32" || cell.variable_type == "Uint64" ||
         cell.variable_type == "long unsigned int" ||
         cell.variable_type == "double";
}

bool CTCompiler::is_number(string &variable_type) {
  return variable_type == "int" || variable_type == "Uint8" ||
         variable_type == "Uint32" || variable_type == "Uint64" ||
         variable_type == "long unsigned int" || variable_type == "double";
}

void CTCompiler::print_eval_cell_info(CTFunction &ct_func, CTCell &cell) {
  printf("file name: '%s'\nfunction name: '%s'\nline: '%d'\n",
         ct_func.file_name.c_str(), ct_func.function_name.c_str(),
         cell.line_number);
  print_eval_func_stacktrace();
}

CTCell CTCompiler::eval_function_cell(CTFunction &ct_func, CTCell &return_type,
                                      vector<CTCell> &local_vars,
                                      CTCell &cell) {
  if (cell.cell_type == CTCellType::List) {
    if (cell.list.size() == 0) {
      printf("CTCompiler::eval_function_cell. List size is '0'.\n");
      print_eval_cell_info(ct_func, cell);
      abort();
    }
    // be careful when you use first_cell or first_cell.token as the cell
    // list it belongs to can be modified in the function call sequence below.
    // if else chaining is fine because it isn't modified yet.
    auto &first_cell = cell.list.at(0);
    if (first_cell.cell_type != CTCellType::Symbol) {
      printf(
          "CTCompiler::eval_function_cell. First cell in list is not a "
          "symbol.\n");
      print_eval_cell_info(ct_func, cell);
      abort();
    }
    if (first_cell.token == "=" || first_cell.token == "set") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. '=' expects a list of size '3'. "
            "(= variable-name variable-value). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      // i'm guessing this is for 'at' function call
      if (cell.list.at(1).cell_type == CTCellType::List) {
        auto var = eval_function_cell(ct_func, return_type, local_vars,
                                      cell.list.at(1));
        auto val = eval_function_cell(ct_func, return_type, local_vars,
                                      cell.list.at(2));
        if (var.variable_type != val.variable_type &&
            (!(is_number(var) && is_number(val)) &&
             (!(is_pointer(var.variable_type) && val.token == "NULL")))) {
          printf(
              "CTCompiler::eval_function_cell. '='. '%s' expects type '%s', "
              "found "
              "type '%s'.\n",
              var.token.c_str(), var.variable_type.c_str(),
              val.variable_type.c_str());
          print_eval_cell_info(ct_func, cell);
          abort();
        }
        auto compiler_builtin_cell =
            CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                   ct_func.file_name, 0, 0);
        compiler_builtin_cell.variable_type =
            "Compiler-BuiltInFunction-NoReturnType.";
        return compiler_builtin_cell;
      }
      if (cell.list.at(1).cell_type != CTCellType::Symbol) {
        printf(
            "CTCompiler::eval_function_cell. '=' expects the second cell to be "
            "a "
            "symbol, found cell with type '%d'.\n",
            (int)cell.list.at(1).cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto var = cell.list.at(1);
      auto value = cell.list.at(2);
      // make a cpy of the token as var is reset below, the copy is used for the
      // local var dict.
      auto var_token = var.token;
      auto contains_dot = var.token.find('.') != string::npos;
      if (contains_dot && value.cell_type == CTCellType::Symbol &&
          is_token_a_class_type(value)) {
        printf(
            "CTCompiler::eval_function_cell. '='. cannot set a dot notation "
            "var to "
            "a class literal value. "
            "var is '%s' and class literal is '%s'\n",
            var_token.c_str(), value.token.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      var = get_dot_notation_var(ct_func, local_vars, var, false);
      auto variable_type =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      // add the vars type (even dot notation vars like sprite.anim_speed)
      // into the local var dict so that outputting to c is easier, just a type
      // lookup.
      /*printf("file %s: entering into local var dict %s %s\n",
             ct_func.file_name.c_str(), var_token.c_str(),
             variable_type.variable_type.c_str());*/
      ct_func.local_var_type_dict[var_token] = variable_type.variable_type;
      // if contains dot then it is something like = u.hp 20. Just need to
      // check that the assignemnt is of the correct types, i.e. u.hp is an
      // int and 20 is an int. Do not need to add to local vars in this case,
      // because u is already a local var.

      if (contains_dot) {
        if (var.variable_type != variable_type.variable_type &&
            (!(is_number(var) && is_number(variable_type)) &&
             (!(is_pointer(var.variable_type) &&
                variable_type.token == "NULL")))) {
          printf(
              "CTCompiler::eval_function_cell. '='. '%s' expects type '%s', "
              "found "
              "type '%s'.\n",
              cell.list.at(1).token.c_str(), var.variable_type.c_str(),
              variable_type.variable_type.c_str());
          print_eval_cell_info(ct_func, cell);
          abort();
        }
      } else {
        // if already defined
        auto is_already_defined = is_local_var(local_vars, var);
        if (is_already_defined) {
          // check to make sure its not being set to a different type
          auto local_var = get_local_var(local_vars, var);
          if (local_var.variable_type != variable_type.variable_type) {
            printf(
                "CTCompiler::eval_function_cell. '='. invalid redefinition of "
                "var "
                "'%s', "
                "expects type '%s', found "
                "type '%s'.\n",
                cell.list.at(1).token.c_str(), local_var.variable_type.c_str(),
                variable_type.variable_type.c_str());
            print_eval_cell_info(ct_func, cell);
            abort();
          }
        } else {
          var.variable_type = variable_type.variable_type;
          if (variable_type.variable_type == "array") {
            var.array_elements_type = variable_type.array_elements_type;
          }
          // value is now bound to a var, so it is an l-value
          var.is_r_value = false;
          local_vars.push_back(var);
        }
      }
      // basically is a function that has no return type, so you can't use
      // it in a nested list.
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "==") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. '==' expects a list of size '3'. "
            "(== variable-name variable-value). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto cmp1 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto cmp2 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      if (!(is_primitive_type(cmp1) || is_pointer(cmp1.variable_type) ||
            is_enum(cmp1.variable_type))) {
        printf(
            "CTCompiler::eval_function_cell. '==' requires first param to "
            "be a primitive, pointer, or enum, found type '%s'.\n",
            cmp1.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      } else if (!(is_primitive_type(cmp2) || is_pointer(cmp2.variable_type) ||
                   is_enum(cmp2.variable_type))) {
        printf(
            "CTCompiler::eval_function_cell. '==' requires second param to "
            "be a primitive, pointer, or enum, found type '%s'.\n",
            cmp1.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      } else if (cmp1.variable_type != cmp2.variable_type) {
        printf(
            "CTCompiler::eval_function_cell. '==' expects both params to be "
            "the same type, found type1: '%s', type2: '%s'.\n",
            cmp1.variable_type.c_str(), cmp2.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto return_cell =
          CTCell(CTCellType::Symbol, "compiler-bool-return-type",
                 ct_func.file_name, cell.line_number, cell.indent);
      return_cell.variable_type = "bool";
      return return_cell;
    } else if (first_cell.token == "!=") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. '!=' expects a list of size '3'. "
            "(!= variable-name variable-value). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto cmp1 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto cmp2 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      if (!(is_primitive_type(cmp1) || is_pointer(cmp1.variable_type) ||
            is_enum(cmp1.variable_type))) {
        printf(
            "CTCompiler::eval_function_cell. '!=' requires first param to "
            "be a primitive, pointer, or enum, found type '%s'.\n",
            cmp1.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      } else if (!(is_primitive_type(cmp2) || is_pointer(cmp2.variable_type) ||
                   is_enum(cmp2.variable_type))) {
        printf(
            "CTCompiler::eval_function_cell. '!=' requires second param to "
            "be a primitive, pointer, or enum, found type '%s'.\n",
            cmp1.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      } else if (cmp1.variable_type != cmp2.variable_type) {
        printf(
            "CTCompiler::eval_function_cell. '!=' expects both params to be "
            "the same type, found type1: '%s', type2: '%s'.\n",
            cmp1.variable_type.c_str(), cmp2.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto return_cell =
          CTCell(CTCellType::Symbol, "compiler-bool-return-type",
                 ct_func.file_name, cell.line_number, cell.indent);
      return_cell.variable_type = "bool";
      return return_cell;
    } else if (first_cell.token == "return") {
      if (cell.list.size() > 2) {
        printf(
            "CTCompiler::eval_function_cell. 'return' expects a list of at "
            "least size "
            "'2'. "
            "(return) or (return value). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      // (return) with no args returns void
      if (cell.list.size() == 1) {
        auto compiler_builtin_cell =
            CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                   ct_func.file_name, 0, 0);
        // an empty return returns void.
        compiler_builtin_cell.variable_type = "void.";
        return compiler_builtin_cell;
      }
      auto new_return_type =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      // returned values are always r-values, waiting to be bound to some
      // l-value. It is possible for it to be bound to an l-value (multiple
      // vars using the same pointer), but returned values are r-values, they
      // are not the var that is set to the pointer, they are the pointer
      // itself.
      new_return_type.is_r_value = true;
      if (return_type.variable_type == "void") {
        return_type = new_return_type;
      } else if (new_return_type.variable_type != return_type.variable_type) {
        printf(
            "CTCompiler::eval_function_cell. Function '%s' - found different "
            "return types. return "
            "type 1 is '%s' and return type 2 is '%s'.\n",
            ct_func.function_name.c_str(), return_type.variable_type.c_str(),
            new_return_type.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "cast") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. 'cast' expects a list of size "
            "'2'. "
            "(cast value newtype). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto var_type = cell.list.at(2).token;
      replaceAll(var_type, "\"", "");
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-Cast.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type = var_type;
      return compiler_builtin_cell;
    }
    // this is literally only so that array.arr is treated as a pointer.
    // to make it easy to get arr[0] types early on in the compiler, arr
    // was set to the array struct's name. This has the unfortunate effect
    // that array.arr is of the type Array_char_50 instead of char*. So,
    // this hack fixes that, array_get_buffer(array) compiles into
    // array.arr or array->arr but the type is char* instead of Array_char_50.
    else if (first_cell.token == "array_get_buffer") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::eval_function_cell. 'array_get_buffer' expects a list "
            "of "
            "size "
            "'2'. "
            "(array_get_buffer array). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto param1 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      if (!is_array(param1.variable_type)) {
        printf(
            "CTCompiler::eval_function_cell. 'array_get_buffer' expects the "
            "first "
            "param "
            "to be an array, found variable type "
            "'%s'.\n",
            param1.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-strncpy.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          get_array_elements_type_from_string_name(param1.variable_type) + "*";
      return compiler_builtin_cell;
    } else if (first_cell.token == "sizeof") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::eval_function_cell. 'sizeof' expects a list of "
            "size "
            "'2'. "
            "(sizeof struct). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(1).cell_type != CTCellType::List) {
        printf(
            "CTCompiler::eval_function_cell. 'sizeof' expects the first "
            "param "
            "to be a 'list', found celltype of '%d'.\n",
            (int)cell.list.at(1).cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto type_cell = cell.list.at(1).list.at(0);
      type_cell.variable_type = "long unsigned int";
      return type_cell;
    } else if (first_cell.token == "malloc") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. 'malloc' expects a list of "
            "size "
            "'3'. "
            "(malloc struct size). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(1).cell_type != CTCellType::List) {
        printf(
            "CTCompiler::eval_function_cell. 'malloc' expects the first "
            "param "
            "to be a 'list', found celltype of '%d'.\n",
            (int)cell.list.at(1).cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(2).cell_type != CTCellType::Int) {
        printf(
            "CTCompiler::eval_function_cell. 'malloc' expects the second "
            "param "
            "to be an 'int', found celltype of '%d'.\n",
            (int)cell.list.at(1).cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto type_cell = cell.list.at(1).list.at(0);
      type_cell.variable_type = type_cell.token + "*";
      return type_cell;
    } else if (first_cell.token == "free") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::eval_function_cell. 'free' expects a list of "
            "size "
            "'2'. "
            "(free struct). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(1).cell_type != CTCellType::Symbol) {
        printf(
            "CTCompiler::eval_function_cell. 'free' expects the first param "
            "to be a 'symbol', found celltype of '%d'.\n",
            (int)cell.list.at(1).cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "memset") {
      if (cell.list.size() != 4) {
        printf(
            "CTCompiler::eval_function_cell. 'memset' expects a list of "
            "size "
            "'4'. "
            "(memset struct_ptr memset_with_value mul_struct_size_by_n). Found "
            "a list with "
            "size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(1).cell_type == CTCellType::List) {
        if (cell.list.at(1).list.size() == 0) {
          printf(
              "CTCompiler::eval_function_cell. If the first param is a list, "
              "it must be a list > size of 0. Found size '%ld'",
              cell.list.at(1).list.size());
          print_eval_cell_info(ct_func, cell);
          abort();
        }
        if (cell.list.at(1).list.at(0).token != "addr") {
          printf(
              "CTCompiler::eval_function_cell. If the first param is a list, "
              "it must be a function call to 'addr' only for now. I might fix "
              "this later. Found function '%s'.\n",
              cell.list.at(1).list.at(0).token.c_str());
          print_eval_cell_info(ct_func, cell);
          abort();
        }
      }
      auto ptr_cell =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto memset_val_cell =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      auto type_mul_cell =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(3));
      if (!is_pointer(ptr_cell.variable_type)) {
        printf(
            "CTCompiler::eval_function_cell. 'memset' expects the first param "
            "to be a pointer, found type of '%s'.\n",
            ptr_cell.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(2).cell_type != CTCellType::Int) {
        printf(
            "CTCompiler::eval_function_cell. 'memset' expects the second "
            "param "
            "to be an 'int', found celltype of '%d'.\n",
            (int)cell.list.at(2).cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(3).cell_type != CTCellType::Int) {
        printf(
            "CTCompiler::eval_function_cell. 'memset' expects the third "
            "param "
            "to be an 'int', found celltype of '%d'.\n",
            (int)cell.list.at(3).cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto type_cell = cell.list.at(1).list.at(0);
      type_cell.variable_type = type_cell.token + "*";
      return type_cell;
    } else if (first_cell.token == "sprintf") {
      if (cell.list.size() < 3) {
        printf(
            "CTCompiler::eval_function_cell. 'sprintf' expects a list of "
            "at least size "
            "'3'. "
            "(sprintf buf format_str ...). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto buffer_cell =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto format_str =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      if (!is_array(buffer_cell)) {
        printf(
            "CTCompiler::eval_function_cell. 'sprintf' expects the first "
            "param "
            "to be an array of char, found type '%s'.\n",
            buffer_cell.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (get_array_elements_type_from_string_name(buffer_cell.variable_type) !=
          "char") {
        printf(
            "CTCompiler::eval_function_cell. 'sprintf' expects the first "
            "param "
            "to be an array with elements of type 'char', found an array with "
            "elements of type '%s'.\n",
            buffer_cell.array_elements_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (format_str.variable_type != "char*") {
        printf(
            "CTCompiler::eval_function_cell. 'sprintf' expects the second "
            "param "
            "to be of type 'char*, found type type '%s'.\n",
            format_str.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "last_enum_int") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::eval_function_cell. 'last_enum_int' expects a list of "
            "size "
            "'2'. "
            "(last_enum_int enum). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(1).cell_type != CTCellType::Symbol) {
        printf(
            "CTCompiler::eval_function_cell. 'last_enum_int' expects the first "
            "param "
            "to be a 'symbol', found celltype of '%d'.\n",
            (int)cell.list.at(1).cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (!is_enum(cell.list.at(1))) {
        printf(
            "CTCompiler::eval_function_cell. 'last_enum_int' expects the first "
            "param "
            "to be an enum. cell token: '%s'.\n",
            cell.list.at(1).token.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (enum_name_dict.find(cell.list.at(1).token) == enum_name_dict.end()) {
        printf(
            "CTCompiler::eval_function_cell. 'last_enum_int'. Enum '%s' is not "
            "in the enum name dict.\n",
            cell.list.at(1).token.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto int_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-LastEnumInt.",
                 ct_func.file_name, 0, 0);
      int_cell.variable_type = "int";
      return int_cell;
    } else if (first_cell.token == "continue") {
      if (cell.list.size() != 1) {
        printf(
            "CTCompiler::eval_function_cell. 'continue' expects a list of "
            "size "
            "'1'. "
            "(continue). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "break") {
      if (cell.list.size() != 1) {
        printf(
            "CTCompiler::eval_function_cell. 'break' expects a list of "
            "size "
            "'1'. "
            "(break). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "not") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::eval_function_cell. 'not' expects a list of "
            "size "
            "'2'. "
            "(not value). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto not_value_cell =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      if (not_value_cell.variable_type != "bool") {
        printf(
            "CTCompiler::eval_function_cell. "
            "'not' expects the first param to "
            "be of type 'bool', found type "
            "'%s'.\n",
            not_value_cell.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      return not_value_cell;
    } else if (first_cell.token == "for" || first_cell.token == "forrev") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. 'for/forrev' expects a list of "
            "size "
            "'3'. "
            "(for loopvar (range start end step)). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(1).cell_type != CTCellType::Symbol) {
        printf(
            "CTCompiler::eval_function_cell. 'for/forrev' expects the second "
            "item in the "
            "list to be a symbol. Found type '%d'.\n",
            (int)cell.cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(2).cell_type != CTCellType::List) {
        printf(
            "CTCompiler::eval_function_cell. 'for/forrev' expects the third "
            "item in the "
            "list to be a list. Found type '%d'.\n",
            (int)cell.cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      // don't eval this cell because the loop var will be undefined, it is
      // defined here.
      auto loop_var = cell.list.at(1);
      auto loop_range_list = cell.list.at(2);
      auto loop_start = CTCell(CTCellType::Int, "0", ct_func.file_name,
                               cell.line_number, cell.indent);
      auto loop_end = CTCell(CTCellType::Int, "0", ct_func.file_name,
                             cell.line_number, cell.indent);
      auto loop_step = CTCell(CTCellType::Int, "1", ct_func.file_name,
                              cell.line_number, cell.indent);
      loop_start.variable_type = "int";
      loop_end.variable_type = "int";
      loop_step.variable_type = "int";
      if (loop_range_list.list.size() == 4) {
        loop_start = eval_function_cell(ct_func, return_type, local_vars,
                                        loop_range_list.list.at(1));
        loop_end = eval_function_cell(ct_func, return_type, local_vars,
                                      loop_range_list.list.at(2));
        loop_step = eval_function_cell(ct_func, return_type, local_vars,
                                       loop_range_list.list.at(3));
      } else if (loop_range_list.list.size() == 3) {
        loop_start = eval_function_cell(ct_func, return_type, local_vars,
                                        loop_range_list.list.at(1));
        loop_end = eval_function_cell(ct_func, return_type, local_vars,
                                      loop_range_list.list.at(2));
      } else if (loop_range_list.list.size() == 2) {
        loop_end = eval_function_cell(ct_func, return_type, local_vars,
                                      loop_range_list.list.at(1));
      }
      if (loop_start.variable_type != "int") {
        printf(
            "CTCompiler::eval_function_cell. 'for/forrev' expects the loop "
            "start value (range start end step) in "
            "the list to be an 'int'. Found type '%s'\n.",
            loop_start.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (loop_end.variable_type != "int") {
        printf(
            "CTCompiler::eval_function_cell. 'for/forrev' expects the loop "
            "end value (range start end step) in "
            "the list to be an 'int'. Found type '%s'\n.",
            loop_end.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (loop_step.variable_type != "int") {
        printf(
            "CTCompiler::eval_function_cell. 'for/forrev' expects the loop "
            "step value (range start end step) in "
            "the list to be an 'int'. Found type '%s'\n.",
            loop_step.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      // define loop var
      loop_var.variable_type = "int";
      loop_var.is_r_value = false;
      local_vars.push_back(loop_var);
      ct_func.local_var_type_dict[loop_var.token] = loop_var.variable_type;
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "while") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::eval_function_cell. 'while' expects a list of "
            "size "
            "'2'. "
            "(while condition). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto cond_cell =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      if (cond_cell.variable_type != "bool") {
        printf(
            "CTCompiler::eval_function_cell. 'while' expects the first param "
            "to be of type 'bool', found type '%s'.\n",
            cond_cell.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      return cond_cell;
    } else if (first_cell.token == "foreach") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. 'foreach' expects a list of "
            "size "
            "'3'. "
            "(foreach loop_var array). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(1).cell_type != CTCellType::Symbol) {
        printf(
            "CTCompiler::eval_function_cell. 'foreach' expects the second "
            "item in the "
            "list to be a symbol. Found type '%d'.\n",
            (int)cell.cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto loop_var = cell.list.at(1);
      auto loop_arr =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      if (!is_array(loop_arr.variable_type)) {
        printf(
            "CTCompiler::eval_function_cell. 'foreach' expects third param to "
            "be of type 'array', found type '%s'.\n",
            loop_arr.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto &arr_ct_class = get_class(loop_arr.variable_type);
      // loop var becomes a pointer as it is expanded in the c file output as
      // a ptr
      auto loop_index_var = CTCell(CTCellType::Symbol, "i", ct_func.file_name,
                                   cell.line_number, cell.indent);
      loop_index_var.variable_type = "int";
      loop_var.variable_type = arr_ct_class.array_elements_type + "*";
      local_vars.push_back(loop_var);
      local_vars.push_back(loop_index_var);
      ct_func.local_var_type_dict[loop_var.token] = loop_var.variable_type;
      ct_func.local_var_type_dict[loop_index_var.token] =
          loop_index_var.variable_type;
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "map") {
      if (cell.list.size() != 4) {
        printf(
            "CTCompiler::eval_function_cell. 'map' expects a list of "
            "size "
            "'4'. "
            "(map idx_var element_var array). Found a list with size "
            "'%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(1).cell_type != CTCellType::Symbol) {
        printf(
            "CTCompiler::eval_function_cell. 'map' expects the second "
            "item in the "
            "list to be a symbol. Found type '%d'.\n",
            (int)cell.list.at(1).cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.at(2).cell_type != CTCellType::Symbol) {
        printf(
            "CTCompiler::eval_function_cell. 'foreach' expects the third "
            "item in the "
            "list to be a symbol. Found type '%d'.\n",
            (int)cell.list.at(2).cell_type);
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto loop_var = cell.list.at(1);
      auto element_var = cell.list.at(2);
      auto loop_arr =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(3));
      if (!is_array(loop_arr.variable_type)) {
        printf(
            "CTCompiler::eval_function_cell. 'foreach' expects third param to "
            "be of type 'array', found type '%s'.\n",
            loop_arr.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      // loop var becomes a pointer as it is expanded in the c file output as
      // a ptr
      loop_var.variable_type = "int";
      auto &arr_ct_class = get_class(loop_arr.variable_type);
      element_var.variable_type = arr_ct_class.array_elements_type + "*";
      local_vars.push_back(loop_var);
      local_vars.push_back(element_var);
      ct_func.local_var_type_dict[loop_var.token] = loop_var.variable_type;
      ct_func.local_var_type_dict[element_var.token] =
          element_var.variable_type;
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "if") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::eval_function_cell. 'if' expects a list of size "
            "'2'. "
            "(if cond). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto cond_value =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      if (cond_value.variable_type != "bool") {
        printf(
            "CTCompiler::eval_function_cell. 'if' expects the second item in "
            "the list to be a 'bool'. Found type '%s'\n.",
            cond_value.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "elif") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::eval_function_cell. 'elif' expects a list of size "
            "'2'. "
            "(if cond). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto cond_value =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      if (cond_value.variable_type != "bool") {
        printf(
            "CTCompiler::eval_function_cell. 'elif' expects the second item "
            "in "
            "the list to be a 'bool'. Found type '%s'\n.",
            cond_value.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "else") {
      if (cell.list.size() != 1) {
        printf(
            "CTCompiler::eval_function_cell. 'else' expects a list of size "
            "'1'. "
            "(else). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "exit") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::eval_function_cell. 'exit' expects a "
            "list of "
            "size "
            "'2'. "
            "(exit). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto exit_val =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      if (exit_val.variable_type != "int") {
        printf(
            "CTCompiler::eval_function_cell. 'exit' expects a "
            "the second parameter to be of type 'int', found type '%s'.\n",
            exit_val.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else if (first_cell.token == "array_capacity") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::eval_function_cell. 'array_capacity' expects a "
            "list of "
            "size "
            "'2'. "
            "(array_capacity arr). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto arr =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      if (!is_array(arr.variable_type)) {
        printf(
            "CTCompiler::eval_function_cell. 'array_capacity' expects first "
            "param to be an array, instead found type '%s'\n",
            arr.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto capacity_cell = CTCell(CTCellType::Int, "CompilerArrCapacity",
                                  ct_func.file_name, 0, 0);
      capacity_cell.variable_type = "int";
      return capacity_cell;
    } else if (first_cell.token == "make_array") {
      return add_array_class(cell, ct_func.file_name);
    } else if (first_cell.token == "value_at") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. 'value_at' expects a list of "
            "size "
            "'3'. "
            "(value_at arr idx). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto arr =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto idx =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      if (!is_array(arr.variable_type)) {
        printf(
            "CTCompiler::eval_function_cell. 'value_at' expects the first "
            "param "
            "to be an 'array', found type '%s'.\n",
            arr.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (idx.variable_type != "int") {
        printf(
            "CTCompiler::eval_function_cell. 'value_at' expects the second "
            "param "
            "to be an 'int', found type '%s'.\n",
            idx.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto &arr_ct_class = get_class(arr.variable_type);
      auto element = CTCell(CTCellType::Symbol, "Compiler-ArrayIdx",
                            ct_func.file_name, 0, 0);
      element.variable_type = arr_ct_class.array_elements_type;
      return element;
    } else if (first_cell.token == "at") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. 'at' expects a list of "
            "size "
            "'3'. "
            "(at arr idx). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto arr =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto idx =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      if (!is_array(arr.variable_type)) {
        printf(
            "CTCompiler::eval_function_cell. 'at' expects the first "
            "param "
            "to be an 'array', found type '%s'.\n",
            arr.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (idx.variable_type != "int") {
        printf(
            "CTCompiler::eval_function_cell. 'at' expects the second "
            "param "
            "to be an 'int', found type '%s'.\n",
            idx.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto &arr_ct_class = get_class(arr.variable_type);
      auto element = CTCell(CTCellType::Symbol, "Compiler-ArrayIdx",
                            ct_func.file_name, 0, 0);
      element.variable_type = arr_ct_class.array_elements_type + "*";
      return element;
    } else if (first_cell.token == "&" || first_cell.token == "addr") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::eval_function_cell. '&' expects a list of "
            "size "
            "'2'. "
            "(& var). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto variable_type =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      variable_type.variable_type += "*";
      return variable_type;
    } else if (first_cell.token == "*" || first_cell.token == "deref") {
      if (cell.list.size() < 2) {
        printf(
            "CTCompiler::eval_function_cell. '*' expects a list of "
            "at least size "
            "'2'. "
            "(* var) for deref or (* a b ...) for mul. Found a list with "
            "size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.size() == 2) {
        auto variable_type = eval_function_cell(ct_func, return_type,
                                                local_vars, cell.list.at(1));
        // remove first occurence of "*", deref only one pointer
        auto it = find(variable_type.variable_type.begin(),
                       variable_type.variable_type.end(), '*');
        if (it != variable_type.variable_type.end()) {
          variable_type.variable_type.erase(it);
          return variable_type;
        } else {
          printf(
              "CTCompiler::eval_function_cell. '*' (deref) expects a "
              "pointer, "
              "found type '%s'.\n",
              variable_type.variable_type.c_str());
          print_eval_cell_info(ct_func, cell);
          abort();
        }
      } else {
        if (cell.list.size() < 3) {
          printf(
              "CTCompiler::eval_function_cell. '*' (mul) expects a list of "
              "at "
              "least "
              "size "
              "'3'. "
              "(* a b ...). Found a list with size '%ld'\n",
              cell.list.size());
          print_eval_cell_info(ct_func, cell);
          abort();
        }
        if (first_cell.token == "deref") {
          printf(
              "CTCompiler::eval_function_cell. '*' (mul) has three params "
              "but "
              "found 'deref' as the function name. 'deref' can only be used "
              "with '1' param.\n");
          print_eval_cell_info(ct_func, cell);
          abort();
        }
        auto mul_return_cell = CTCell(CTCellType::None, "mul-return-type",
                                      ct_func.file_name, 0, 0);
        for (int i = 1; i < cell.list.size(); i++) {
          auto variable_type = eval_function_cell(ct_func, return_type,
                                                  local_vars, cell.list.at(i));
          if (!is_number(variable_type)) {
            printf(
                "CTCompiler::eval_function_cell. '*' expects types 'number', "
                "found '%s'.\n",
                variable_type.variable_type.c_str());
            print_eval_cell_info(ct_func, cell);
            abort();
          }
          // all non-doubles get turned into an int (example Uint64, Uint32, and
          // Uint8).
          else if (variable_type.variable_type != "double") {
            if (mul_return_cell.variable_type != "double") {
              mul_return_cell.variable_type = "int";
            }
          } else if (variable_type.variable_type == "double") {
            mul_return_cell.variable_type = "double";
          }
        }
        if (mul_return_cell.variable_type == "undefined") {
          printf(
              "CTCompiler::eval_function_cell. '*''s (mul) return type is "
              "'undefined'. "
              "This "
              "is unexpected.\n");
          print_eval_cell_info(ct_func, cell);
          abort();
        }
        return mul_return_cell;
      }
      printf("CTCompiler::eval_function_cell. '*' reached unexpected path.\n");
      abort();
    } else if (first_cell.token == "and") {
      if (cell.list.size() < 3) {
        printf(
            "CTCompiler::eval_function_cell. 'and' expects a list of at "
            "least "
            "size "
            "'3'. "
            "(and a b ...). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto and_return_cell =
          CTCell(CTCellType::None, "and-return-type", ct_func.file_name, 0, 0);
      and_return_cell.variable_type = "bool";
      for (int i = 1; i < cell.list.size(); i++) {
        auto variable_type = eval_function_cell(ct_func, return_type,
                                                local_vars, cell.list.at(i));
        if (variable_type.variable_type != "bool") {
          printf(
              "CTCompiler::eval_function_cell. 'and' expects each param to "
              "have "
              "type 'bool', "
              "found '%s'.\n",
              variable_type.variable_type.c_str());
          print_eval_cell_info(ct_func, cell);
          abort();
        }
      }
      return and_return_cell;
    } else if (first_cell.token == "or") {
      if (cell.list.size() < 3) {
        printf(
            "CTCompiler::eval_function_cell. 'and' expects a list of at "
            "least "
            "size "
            "'3'. "
            "(or a b ...). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto or_return_cell =
          CTCell(CTCellType::None, "and-return-type", ct_func.file_name, 0, 0);
      or_return_cell.variable_type = "bool";
      for (int i = 1; i < cell.list.size(); i++) {
        auto variable_type = eval_function_cell(ct_func, return_type,
                                                local_vars, cell.list.at(i));
        if (variable_type.variable_type != "bool") {
          printf(
              "CTCompiler::eval_function_cell. 'or' expects each param to have "
              "type 'bool', "
              "found '%s'.\n",
              variable_type.variable_type.c_str());
          print_eval_cell_info(ct_func, cell);
          abort();
        }
      }
      return or_return_cell;
    } else if (first_cell.token == "+") {
      if (cell.list.size() < 3) {
        printf(
            "CTCompiler::eval_function_cell. '+' expects a list of at least "
            "size "
            "'3'. "
            "(+ a b ...). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto plus_return_cell =
          CTCell(CTCellType::None, "plus-return-type", ct_func.file_name, 0, 0);
      for (int i = 1; i < cell.list.size(); i++) {
        auto variable_type = eval_function_cell(ct_func, return_type,
                                                local_vars, cell.list.at(i));
        if (!is_number(variable_type)) {
          printf(
              "CTCompiler::eval_function_cell. '+' expects types 'number', "
              "found '%s'.\n",
              variable_type.variable_type.c_str());
          print_eval_cell_info(ct_func, cell);
          abort();
        }
        // all non-doubles get turned into an int (example Uint64, Uint32, and
        // Uint8).
        else if (variable_type.variable_type != "double") {
          if (plus_return_cell.variable_type != "double") {
            plus_return_cell.variable_type = "int";
          }
        } else if (variable_type.variable_type == "double") {
          plus_return_cell.variable_type = "double";
        }
      }
      if (plus_return_cell.variable_type == "undefined") {
        printf(
            "CTCompiler::eval_function_cell. '+''s return type is 'undefined'. "
            "This "
            "is unexpected.\n");
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      return plus_return_cell;
    } else if (first_cell.token == "-") {
      if (cell.list.size() < 2) {
        printf(
            "CTCompiler::eval_function_cell. '-' expects a list of at least "
            "size "
            "'2'. "
            "(- a b ...) or (- a) negation. Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (cell.list.size() == 2) {
        auto variable_type = eval_function_cell(ct_func, return_type,
                                                local_vars, cell.list.at(1));
        if (!is_number(variable_type)) {
          printf(
              "CTCompiler::eval_function_cell. '-' (negation) expects type "
              "'number', "
              "found '%s'.\n",
              variable_type.variable_type.c_str());
          print_eval_cell_info(ct_func, cell);
          abort();
        }
        return variable_type;
      } else {
        auto minus_return_cell = CTCell(CTCellType::None, "minus-return-type",
                                        ct_func.file_name, 0, 0);
        for (int i = 1; i < cell.list.size(); i++) {
          auto variable_type = eval_function_cell(ct_func, return_type,
                                                  local_vars, cell.list.at(i));
          if (!is_number(variable_type)) {
            printf(
                "CTCompiler::eval_function_cell. '-' expects types 'number', "
                "found '%s'.\n",
                variable_type.variable_type.c_str());
            print_eval_cell_info(ct_func, cell);
            abort();
          }
          // all non-doubles get turned into an int (example Uint64, Uint32, and
          // Uint8).
          else if (variable_type.variable_type != "double") {
            if (minus_return_cell.variable_type != "double") {
              minus_return_cell.variable_type = "int";
            }
          } else if (variable_type.variable_type == "double") {
            minus_return_cell.variable_type = "double";
          }
        }
        if (minus_return_cell.variable_type == "undefined") {
          printf(
              "CTCompiler::eval_function_cell. '-''s return type is "
              "'undefined'. "
              "This "
              "is unexpected.\n");
          print_eval_cell_info(ct_func, cell);
          abort();
        }
        return minus_return_cell;
      }
    } else if (first_cell.token == "/") {
      if (cell.list.size() < 3) {
        printf(
            "CTCompiler::eval_function_cell. '/' expects a list of at least "
            "size "
            "'3'. "
            "(/ a b ...). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto div_return_cell = CTCell(CTCellType::None, "minus-return-type",
                                    ct_func.file_name, 0, 0);
      for (int i = 1; i < cell.list.size(); i++) {
        auto variable_type = eval_function_cell(ct_func, return_type,
                                                local_vars, cell.list.at(i));
        if (!is_number(variable_type)) {
          printf(
              "CTCompiler::eval_function_cell. '/' expects types 'number', "
              "found '%s'.\n",
              variable_type.variable_type.c_str());
          print_eval_cell_info(ct_func, cell);
          abort();
        }
        // all non-doubles get turned into an int (example Uint64, Uint32, and
        // Uint8).
        else if (variable_type.variable_type != "double") {
          if (div_return_cell.variable_type != "double") {
            div_return_cell.variable_type = "int";
          }
        } else if (variable_type.variable_type == "double") {
          div_return_cell.variable_type = "double";
        }
      }
      if (div_return_cell.variable_type == "undefined") {
        printf(
            "CTCompiler::eval_function_cell. '/''s return type is 'undefined'. "
            "This "
            "is unexpected.\n");
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      return div_return_cell;
    } else if (first_cell.token == "+=") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. '+=' expects a list of "
            "size "
            "'3'. "
            "(+= a b). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto var =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto val =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));

      if (!is_number(var)) {
        printf(
            "CTCompiler::eval_function_cell. '+=' expects the first param "
            "(the variable) to be a number. Found type '%s'.\n",
            val.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (!is_number(val)) {
        printf(
            "CTCompiler::eval_function_cell. '+=' expects the second param "
            "(the value) to be a number. Found type '%s'.\n",
            val.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      return var;
    } else if (first_cell.token == "-=") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. '-=' expects a list of "
            "size "
            "'3'. "
            "(-= a b). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto var =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto val =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      if (!is_number(var)) {
        printf(
            "CTCompiler::eval_function_cell. '-=' expects the first param "
            "(the variable) to be a number. Found type '%s'.\n",
            val.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (!is_number(val)) {
        printf(
            "CTCompiler::eval_function_cell. '-=' expects the second param "
            "(the value) to be a number. Found type '%s'.\n",
            val.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      return var;
    } else if (first_cell.token == "*=") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. '*=' expects a list of "
            "size "
            "'3'. "
            "(*= a b). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto var =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto val =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      if (!is_number(var)) {
        printf(
            "CTCompiler::eval_function_cell. '*=' expects the first param "
            "(the variable) to be a number. Found type '%s'.\n",
            val.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (!is_number(val)) {
        printf(
            "CTCompiler::eval_function_cell. '*=' expects the second param "
            "(the value) to be a number. Found type '%s'.\n",
            val.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      return var;
    } else if (first_cell.token == "/=") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. '/=' expects a list of "
            "size "
            "'3'. "
            "(/= a b). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto var =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto val =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      if (!is_number(var)) {
        printf(
            "CTCompiler::eval_function_cell. '/=' expects the first param "
            "(the variable) to be a number. Found type '%s'.\n",
            val.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (!is_number(val)) {
        printf(
            "CTCompiler::eval_function_cell. '/=' expects the second param "
            "(the value) to be a number. Found type '%s'.\n",
            val.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      return var;
    } else if (first_cell.token == "mod") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. 'mod' expects a list of "
            "size "
            "'3'. "
            "(mod a b). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto var =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto val =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));

      if (!is_number(var)) {
        printf(
            "CTCompiler::eval_function_cell. 'mod' expects the first param "
            "(the variable) to be a number. Found type '%s'.\n",
            val.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (!is_number(val)) {
        printf(
            "CTCompiler::eval_function_cell. 'mod' expects the second param "
            "(the value) to be a number. Found type '%s'.\n",
            val.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto int_cell =
          CTCell(CTCellType::Bool, "Compiler-Int", ct_func.file_name, 0, 0);
      int_cell.variable_type = "int";
      return int_cell;
    } else if (first_cell.token == ">") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. '>' expects a list of "
            "size "
            "'3'. "
            "(> a b). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto c1 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto c2 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      if (!(is_number(c1.variable_type) || c1.variable_type == "char")) {
        printf(
            "CTCompiler::eval_function_cell. '>' expects first param to be "
            "an "
            "'int', 'double', or 'char'. Found type '%s'\n",
            c1.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (!(is_number(c2.variable_type) || c2.variable_type == "char")) {
        printf(
            "CTCompiler::eval_function_cell. '>' expects second param to be "
            "an "
            "'int', 'double', or 'char'. Found type '%s'\n",
            c2.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto bool_cell =
          CTCell(CTCellType::Bool, "Compiler-Bool", ct_func.file_name, 0, 0);
      bool_cell.variable_type = "bool";
      return bool_cell;
    } else if (first_cell.token == "<") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. '<' expects a list of "
            "size "
            "'3'. "
            "(< a b). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto c1 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto c2 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      if (!(is_number(c1.variable_type) || c1.variable_type == "char")) {
        printf(
            "CTCompiler::eval_function_cell. '<' expects first param to be "
            "an "
            "'int', 'double', or 'char'. Found type '%s'\n",
            c1.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (!(is_number(c2.variable_type) || c2.variable_type == "char")) {
        printf(
            "CTCompiler::eval_function_cell. '<' expects second param to be "
            "an "
            "'int', 'double', or 'char'. Found type '%s'\n",
            c2.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto bool_cell =
          CTCell(CTCellType::Bool, "Compiler-Bool", ct_func.file_name, 0, 0);
      bool_cell.variable_type = "bool";
      return bool_cell;
    } else if (first_cell.token == ">=") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. '>=' expects a list of "
            "size "
            "'3'. "
            "(>= a b). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto c1 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto c2 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      if (!(is_number(c1.variable_type) || c1.variable_type == "char")) {
        printf(
            "CTCompiler::eval_function_cell. '>=' expects first param to be "
            "an "
            "number, Found type '%s'\n",
            c1.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (!(is_number(c2.variable_type) || c2.variable_type == "char")) {
        printf(
            "CTCompiler::eval_function_cell. '>=' expects second param to be "
            "an "
            "number, Found type '%s'\n",
            c2.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto bool_cell =
          CTCell(CTCellType::Bool, "Compiler-Bool", ct_func.file_name, 0, 0);
      bool_cell.variable_type = "bool";
      return bool_cell;
    } else if (first_cell.token == "<=") {
      if (cell.list.size() != 3) {
        printf(
            "CTCompiler::eval_function_cell. '<=' expects a list of "
            "size "
            "'3'. "
            "(<= a b). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto c1 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      auto c2 =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(2));
      if (!(is_number(c1.variable_type) || c1.variable_type == "char")) {
        printf(
            "CTCompiler::eval_function_cell. '<=' expects first param to be "
            "an "
            "'int', 'double', or 'char'. Found type '%s'\n",
            c1.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      if (!(is_number(c2.variable_type) || c2.variable_type == "char")) {
        printf(
            "CTCompiler::eval_function_cell. '<=' expects second param to be "
            "an "
            "'int', 'double', or 'char'. Found type '%s'\n",
            c2.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto bool_cell =
          CTCell(CTCellType::Bool, "Compiler-Bool", ct_func.file_name, 0, 0);
      bool_cell.variable_type = "bool";
      return bool_cell;
    } else if (first_cell.token == "negate") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::eval_function_cell. 'negate' expects a list of "
            "size "
            "'2'. "
            "(negate a). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto negate_cell =
          eval_function_cell(ct_func, return_type, local_vars, cell.list.at(1));
      if (!is_number(negate_cell.variable_type)) {
        printf(
            "CTCompiler::eval_function_cell. 'negate' expects the val's type "
            "to be a number. Found type '%s'.\n",
            negate_cell.variable_type.c_str());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      return negate_cell;
    } else if (first_cell.token == "print") {
      if (cell.list.size() < 2) {
        printf(
            "CTCompiler::eval_function_cell. 'print' expects a list of at "
            "least "
            "size "
            "'2'. "
            "(print a ...). Found a list with size '%ld'\n",
            cell.list.size());
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      for (int i = 1; i < cell.list.size(); i++) {
        auto &param = cell.list.at(i);
        // just to add it to the local var dict at the bottom of this function,
        // remove later if needed
        auto param_cell = eval_function_cell(ct_func, return_type, local_vars,
                                             cell.list.at(i));
        if (param.cell_type == CTCellType::List) {
          printf(
              "CTCompiler::eval_function_cell. 'print' does not support "
              "printing functions, only primitives or variables.\n");
          print_eval_cell_info(ct_func, cell);
          abort();
        }
      }
      auto compiler_builtin_cell =
          CTCell(CTCellType::None, "Compiler-BuiltInFunction-NoReturnType.",
                 ct_func.file_name, 0, 0);
      compiler_builtin_cell.variable_type =
          "Compiler-BuiltInFunction-NoReturnType.";
      return compiler_builtin_cell;
    } else {
      // function call
      auto function_name = first_cell.token;
      auto func_params = vector<CTCell>();
      // class member function
      if (function_name.find(".") != string::npos) {
        auto split = string_split(function_name, '.');
        if (split.size() < 2) {
          printf(
              "CTCompiler::eval_function_cell. Class member function split on "
              "'.' expects a size of at least 2, found size '%ld'. function "
              "name '%s'.\n",
              split.size(), function_name.c_str());
          print_eval_cell_info(ct_func, cell);
          abort();
        }
        auto class_instance_name = string("");
        auto class_func_name = split.at(split.size() - 1);
        // the class instance is all the tokens except the last one. the last
        // token is the function name. example, game.engine.init()
        for (int t = 0; t < split.size() - 1; t++) {
          class_instance_name += split.at(t);
          if (t != split.size() - 2) {
            class_instance_name += ".";
          }
        }
        auto class_name_cell =
            CTCell(CTCellType::Symbol, class_instance_name, cell.file_name,
                   cell.line_number, cell.indent);
        auto class_cell = eval_function_cell(ct_func, return_type, local_vars,
                                             class_name_cell);
        // make a copy so that we can pop back the pointer without modifying the
        // original variable type.
        auto class_var_type = class_cell.variable_type;
        // just need the class name, not the '*' if its a pointer
        if (is_pointer(class_var_type)) {
          class_var_type.pop_back();
        }
        // see if this func is a member func for the type class_var_type. If it
        // is change the function name to the mangled member func function name.
        // If its not, do not modify the function. This is so that any function
        // can be called with dot notation. I.e. push(arr, tile) can be called
        // as arr.push(tile).
        auto is_member_func = false;
        if (class_member_func_dict.find(class_var_type) !=
            class_member_func_dict.end()) {
          // member_funcs are the unmangled function names for this class
          auto &member_funcs = class_member_func_dict.at(class_var_type);
          for (auto &member_func : member_funcs) {
            if (member_func == class_func_name) {
              is_member_func = true;
              break;
            }
          }
        }
        // get the mangled member func name if its a member func
        if (is_member_func) {
          function_name =
              get_class_member_func_name(class_var_type, class_func_name);
        }
        // if its not a member func use the original function name. I.e.
        // arr.push(tile) would be "push".
        else {
          function_name = class_func_name;
        }

        // push back the self param to index 1 as it is always the first param,
        // i.e. the class instance calling it
        cell.list.insert(cell.list.begin() + 1, class_name_cell);
        // func_params.push_back(class_cell);
        // printf("%s %ld\n", function_name.c_str(), cell.list.size());
      }

      // a hack so i can get at syntax without implementing full on macros.
      // arr.at(0).
      if (function_name == "at") {
        // overwrite first cell's token to "at", because it can be self.arr.at
        // here. Then eval the cell with "at" overwritten so it gets caught
        // above in the check for first_cell.token == "at".
        cell.list.at(0).token = "at";
        // add .arr to the array
        cell.list.at(1).token += ".arr";
        return eval_function_cell(ct_func, return_type, local_vars, cell);
      }

      // because class constructors come in the form of a function, check if
      // the function is a class constructor. Example, (= a (Unit)).
      if (is_class_type(function_name)) {
        auto ct_class_val = get_class(function_name);
        cell.list.at(0).variable_type = ct_class_val.class_name;
        return cell.list.at(0);
      }
      /*
      If you add macros in the future, this returns a macro expanded func,
      but its a vector of cells don't know how to replace a single cell
      with a vector of cells.
      // see if the non-class type function is a macro before eval'ing it
      // as a normal function below
      else {
        printf("function name %s\n", function_name.c_str());
        if (function_dict.find(function_name) == function_dict.end()) {
          printf(
              "CTCompiler::eval_function_cell. Function '%s' is "
              "undefined. This is in the macro check part.\nFile: %s\nLine: "
              "%d\n",
              function_name.c_str(), ct_func.file_name.c_str(),
              cell.line_number);
          abort();
        }
        // if func is a macro expand it and then return before doing a normal
        // function eval.
        auto &f = function_dict.at(function_name);
        if (f.return_enforced_type.variable_type == "macro") {
          for (int i = 0; i < cell.list.size(); i++) {
            printf("%d %s\n", i, cell.list.at(i).token.c_str());
          }
          printf("found macro early\n");
          auto expanded_func = expand_macro(f, cell);
          eval_function_cell(ct_func, return_type, local_vars, cell);
          abort();
        }
      }*/
      for (int i = 1; i < cell.list.size(); i++) {
        auto param_original_tok_for_macro = cell.list.at(i).token;
        auto param_cell = eval_function_cell(ct_func, return_type, local_vars,
                                             cell.list.at(i));
        param_cell.macro_param_original_token = param_original_tok_for_macro;
        if (cell.list.at(i).cell_type == CTCellType::List &&
            !is_primitive_type(param_cell.variable_type) &&
            !is_pointer(param_cell.variable_type)) {
          auto param_func_call_name = cell.list.at(i).list.at(0).token;
          // these functions are ok, because they will be passed with an addr
          // as they are coming from l-values.
          if (!(param_func_call_name == "value_at")) {
            printf(
                "CTCompiler::eval_function_cell. Function '%s', param at idx "
                "'%d' "
                "is "
                "a function call '%s' that returns a struct "
                "by value. All "
                "non-primitive params must be l-values so an address can be "
                "taken. Assign this function call to a variable and pass "
                "that "
                "instead.\n",
                function_name.c_str(), (i - 1), param_func_call_name.c_str());
            print_eval_cell_info(ct_func, cell);
            abort();
          }
        }
        // if you are not a primitive and are a struct value (not a struct
        // pointer) pass as a pointer.
        if (!(is_primitive_type(param_cell.variable_type) ||
              is_pointer(param_cell.variable_type))) {
          param_cell.variable_type += "*";
          auto &param_c = cell.list.at(i);
          // wrap param cell in an addr cell and overwrite the param cell in
          // the function call list with the new cell.
          auto addr_wrapper_cell =
              CTCell(CTCellType::List, "", param_cell.file_name,
                     param_cell.line_number, param_cell.indent);
          addr_wrapper_cell.list.push_back(
              CTCell(CTCellType::Symbol, "&", param_cell.file_name,
                     param_cell.line_number, param_cell.indent));
          addr_wrapper_cell.list.push_back(param_c);
          cell.list.at(i) = addr_wrapper_cell;
        }
        func_params.push_back(param_cell);
      }
      int instantiated_function_handle = get_instantied_function_handle(
          ct_func, cell, function_name, func_params);
      if (instantiated_function_handle == -1) {
        auto func_dict_it = function_dict.find(function_name);
        if (func_dict_it == function_dict.end()) {
          printf(
              "CTCompiler::eval_function_cell. Function '%s' is "
              "undefined.\nFile: %s\nLine: %d\n",
              function_name.c_str(), ct_func.file_name.c_str(),
              cell.line_number);
          print_eval_cell_info(ct_func, cell);
          abort();
        } else {
          auto instantiated_func = function_dict[function_name];
          if (instantiated_func.params.size() !=
              instantiated_func.params_enforced_types.size()) {
            printf(
                "CTCompiler::eval_function_cell. instantiated func params size "
                "'%ld' does not equal enforced param size '%ld'. Function "
                "name: %s\n",
                instantiated_func.params.size(),
                instantiated_func.params_enforced_types.size(),
                instantiated_func.function_name.c_str());
            print_eval_cell_info(ct_func, cell);
            abort();
          }
          if (func_params.size() != instantiated_func.params.size()) {
            printf(
                "CTCompiler::eval_function_cell. function '%s' expects '%ld' "
                "params, found '%ld' params.\n",
                instantiated_func.function_name.c_str(),
                instantiated_func.params.size(), func_params.size());
            print_eval_cell_info(ct_func, cell);
            abort();
          }
          for (int i = 0; i < instantiated_func.params.size(); i++) {
            // get from the params that were created above
            auto &param = func_params.at(i);
            // set the param name to the func param name
            param.token = instantiated_func.params.at(i).token;
            auto param_var_type = param.variable_type;
            auto &enforced_param_type =
                instantiated_func.params_enforced_types.at(i);
            auto enforced_var_type = enforced_param_type.variable_type;
            // just checking if the type is the same, so Tile and Tile* will
            // both work as it just sees that its a Tile being passed in, due
            // to python. Change this later if the base language changes.
            if (is_pointer(param_var_type)) {
              replaceAll(param_var_type, "*", "");
            }
            if (is_pointer(enforced_var_type)) {
              replaceAll(enforced_var_type, "*", "");
            }
            if (enforced_var_type != "Any" &&
                enforced_var_type != param_var_type) {
              printf(
                  "CTCompiler::eval_function_cell. Function: '%s'. Param "
                  "number "
                  "'%d' with type '%s' "
                  "does not match the "
                  "enforced type '%s'.\nFile: '%s'\nLine number: '%d'\n",
                  instantiated_func.function_name.c_str(), i,
                  param_var_type.c_str(),
                  enforced_param_type.variable_type.c_str(),
                  cell.file_name.c_str(), cell.line_number);
              print_eval_cell_info(ct_func, cell);
              abort();
            }
          }
          // if the func is a c func or a c library func then just return the
          // return type don't need to eval it as it has no cells, it is just
          // raw c code. The params are checked above so they are known to be
          // correct at this point, so the return type is also known to be
          // correct as well.
          if (instantiated_func.is_c_func ||
              instantiated_func.is_c_library_func) {
            return instantiated_func.return_enforced_type;
          }
          auto func_return_type = eval_function(
              instantiated_func, func_params, cell.file_name, cell.line_number);
          auto func_return_var_type = func_return_type.variable_type;
          // just checking if the type is the same, so Tile and Tile* will
          // both work as it just sees that its a Tile being passed in, due to
          // python. Change this later if the base language changes.
          if (is_pointer(func_return_var_type)) {
            replaceAll(func_return_var_type, "*", "");
          }
          if (instantiated_func.return_enforced_type.variable_type != "Any" &&
              instantiated_func.return_enforced_type.variable_type !=
                  func_return_var_type) {
            printf(
                "CTCompiler::eval_function_cell. Function '%s'. Return type "
                "'%s' "
                "does not match the enforced return type of '%s'.\n",
                instantiated_func.function_name.c_str(),
                func_return_type.variable_type.c_str(),
                instantiated_func.return_enforced_type.variable_type.c_str());
            print_eval_cell_info(ct_func, cell);
            abort();
          }
          instantiated_func.return_type = func_return_type;
          instantiated_func.params = func_params;
          for (auto &p : instantiated_func.params) {
            function_param_types_in_file[instantiated_func.file_name]
                                        [p.variable_type] = true;
          }
          // add the return type too because later the compiler needs to know if
          // it needs to weak import it
          function_param_types_in_file[instantiated_func.file_name]
                                      [instantiated_func.return_type
                                           .variable_type] = true;

          string compiled_func_name = "";
          compiled_func_name += format_type_for_compiled_function(
                                    func_return_type.variable_type) +
                                "_" + function_name;
          if (func_params.size() > 0) {
            compiled_func_name += "_";
          }
          for (int i = 0; i < func_params.size(); i++) {
            compiled_func_name += format_type_for_compiled_function(
                func_params.at(i).variable_type);
            if (i != func_params.size() - 1) {
              compiled_func_name += "_";
            }
          }
          /* DO NOT REFER TO FIRST_CELL AS THE CELL IS IN A VECTOR THAT CAN BE
             MOVED BY INSERTING DONE ABOVE !! */
          // save the original function name here before overwriting the first
          // cell so that member functions for classes can access that name.
          // use cell.list.at(0), as first cell could have been moved. can still
          // reference cell because its stable, cell.list is not.
          cell.list.at(0).original_token = cell.list.at(0).token;
          // overwrite first_cell with the compiled function name so that
          // outputting to c is easier.
          cell.list.at(0).token = compiled_func_name;
          instantiated_func.compiled_function_name = compiled_func_name;
          instantiated_functions.push_back(instantiated_func);

          /*printf("Function %s %s(", func_return_type.variable_type.c_str(),
                 function_name.c_str());*/
          /*for (int i = 0; i < func_params.size(); i++) {
            // printf("%s", func_params.at(i).variable_type.c_str());
            if (i != func_params.size() - 1) {
              // printf(" ");
            }
          }*/
          // printf(") does not exist, creating.\n");

          return func_return_type;
        }
      } else {
        auto instantiated_func =
            instantiated_functions.at(instantiated_function_handle);
        auto func_return_type = instantiated_func.return_type;
        /*printf("Function %s %s(", func_return_type.variable_type.c_str(),
               function_name.c_str());*/
        for (int i = 0; i < func_params.size(); i++) {
          // printf("%s", func_params.at(i).variable_type.c_str());
          if (i != func_params.size() - 1) {
            // printf(" ");
          }
        }
        /*printf(") does exist, returning '%s'.\n",
               func_return_type.variable_type.c_str());*/
        // overwrite first_cell with the compiled function name so that
        // outputting to c is easier.
        cell.list.at(0).token = instantiated_func.compiled_function_name;

        return func_return_type;
      }
    }
  } else {
    // do a lookup in local vars, because the var may have been popped and no
    // longer exist.
    if (cell.cell_type == CTCellType::Symbol) {
      auto class_dict_it = class_dict.find(cell.token);
      // is making a class instance by value
      if (class_dict_it != class_dict.end()) {
        auto class_cell = cell;
        class_cell.variable_type = class_cell.token;
        // add to local var dict so that it can be printed (REMOVE LATER IF THIS
        // CAUSES BUGS)). put it in a separate dict for printable symbols.
        ct_func.local_var_type_dict[cell.token] = class_cell.variable_type;
        return class_cell;
      }
      /* else if (is_enum(cell)) {
        return get_enum_value(cell);
      } */
      else {
        // returns var if no dots, else returns the final var
        // in the dot notation.
        auto dot_notation_cell =
            get_dot_notation_var(ct_func, local_vars, cell, true);
        // add to local var dict so that it can be printed (REMOVE LATER IF THIS
        // CAUSES BUGS)). put it in a separate dict for printable symbols.
        ct_func.local_var_type_dict[cell.token] =
            dot_notation_cell.variable_type;
        return dot_notation_cell;
      }
    }

    return cell;
  }
}

// looks through each instantiated function, returning the handle of the
// function with the function name and the same type for each param. Returns
// -1 if the function with the same variable types was not found.
int CTCompiler::get_instantied_function_handle(CTFunction &eval_cell_func,
                                               CTCell &eval_cell_cell,
                                               string &function_name,
                                               vector<CTCell> &params) {
  for (int i = 0; i < instantiated_functions.size(); i++) {
    auto &func = instantiated_functions.at(i);
    if (func.function_name == function_name) {
      if (func.params.size() != params.size()) {
        printf(
            "CTCompiler::get_instantiated_function_handle. Params sizes do "
            "not "
            "match for function '%s'. Function takes '%ld' params, found "
            "'%ld' "
            "params.\n",
            func.function_name.c_str(), func.params.size(), params.size());
        // this is called from eval_function_cell so it can be called here.
        // func and cell from eval_function_cell are just passed in so this can
        // be called with their context. It is not used elsewhere in this
        // function.
        print_eval_cell_info(eval_cell_func, eval_cell_cell);
        abort();
      }
      // only need to check params, not return type. If the params are the
      // same types then the return type will be the same as well. Also,
      // return types could have different number of params.
      auto params_have_same_types = true;
      for (int j = 0; j < func.params.size(); j++) {
        if (func.params.at(j).variable_type != params.at(j).variable_type) {
          params_have_same_types = false;
          break;
        }
      }
      if (params_have_same_types) {
        return i;
      }
    }
  }
  return -1;
}

CTFunction CTCompiler::expand_macro(CTFunction macro_func, CTCell &macro_cell) {
  // expand the macro for each line in the macro, replacing what was passed in
  for (auto &c : macro_func.cells) {
    expand_macro_for_cell(macro_func, macro_cell, c);
  }
}

void CTCompiler::expand_macro_for_cell(CTFunction &macro_func,
                                       CTCell &macro_cell, CTCell &cell) {
  if (cell.cell_type == CTCellType::List) {
    for (int i = 0; i < cell.list.size(); i++) {
      auto &c = cell.list.at(i);
      expand_macro_for_cell(macro_func, macro_cell, c);
    }
  } else {
    for (int i = 0; i < macro_func.params.size(); i++) {
      auto &param = macro_func.params.at(i);
      auto &c = macro_cell.list.at(i);
      if (param.token == cell.token) {
        cell = param;
      }
    }
  }
}

string CTCompiler::get_class_member_func_name(string &class_name,
                                              string &function_name) {
  return "mfunc_" + class_name + "_" + function_name;
}

string CTCompiler::get_stacktrace_pretty_func_name(string &class_name,
                                                   string &function_name) {
  return class_name + "." + function_name;
}

int CTCompiler::get_instantied_function_compiled_name_handle(
    string &compiled_function_name, vector<CTCell> &params) {
  for (int i = 0; i < instantiated_functions.size(); i++) {
    auto &func = instantiated_functions.at(i);
    if (func.compiled_function_name == compiled_function_name) {
      return i;
    }
  }
  return -1;
}

CTCell CTCompiler::get_local_var(vector<CTCell> &local_vars, CTCell var) {
  if (var.token == "NULL") {
    auto null_cell = var;
    return null_cell;
  }
  auto contains_bracket = var.token.find('[') != string::npos;
  if (contains_bracket) {
    auto split = string_split(var.token, '[');
    var.token = split.at(0);
  }
  for (auto &local_var : local_vars) {
    if (local_var.token == var.token) {
      return local_var;
    }
  }
  printf("CTCompiler::get_local_var. '%s' is undefined.\nFile: %s\nLine: %d\n",
         var.token.c_str(), var.file_name.c_str(), var.line_number);
  abort();
  return CTCell();
}

CTCell CTCompiler::get_local_var(vector<CTCell> &local_vars, string var_token) {
  auto contains_bracket = var_token.find('[') != string::npos;
  if (contains_bracket) {
    auto split = string_split(var_token, '[');
    var_token = split.at(0);
  }
  for (auto &local_var : local_vars) {
    if (local_var.token == var_token) {
      return local_var;
    }
  }
  printf("CTCompiler::get_local_var. '%s' is undefined.\n", var_token.c_str());
  abort();
  return CTCell();
}

bool CTCompiler::is_local_var(vector<CTCell> &local_vars, CTCell var) {
  auto contains_bracket = var.token.find('[') != string::npos;
  if (contains_bracket) {
    auto split = string_split(var.token, '[');
    var.token = split.at(0);
  }
  for (auto &local_var : local_vars) {
    if (local_var.token == var.token) {
      return true;
    }
  }
  return false;
}

CTCell CTCompiler::add_array_class(CTCell &cell, string _class_file_name) {
  /*if (cell.list.size() != 3) {
    printf("CTCompiler::add_array_class. 'make_array' expects a list of "
           "size "
           "'3'. "
           "(make_array type size). Found a list with size '%ld'\n",
           cell.list.size());
    abort();
  }*/
  if (cell.list.at(1).cell_type != CTCellType::Symbol) {
    printf(
        "CTCompiler::add_array_class. 'make_array' expects the second "
        "item in the list to be a 'symbol', found type '%d'\n",
        (int)cell.list.at(1).cell_type);
    abort();
  }
  if (cell.list.at(2).cell_type != CTCellType::Int) {
    printf(
        "CTCompiler::add_array_class. 'make_array' expects the third "
        "item in the list to be an 'int', found type '%d'\n",
        (int)cell.list.at(2).cell_type);
    abort();
  }
  auto array_cell =
      CTCell(CTCellType::Array, "Compiler-Array", _class_file_name, 0, 0);
  auto array_elements_type = cell.list.at(1);
  auto array_capacity = cell.list.at(2);
  auto array_dimensions = cell.list.size() - 2;
  if (cell.list.size() > 3) {
    auto cell_cpy = cell;
    array_capacity = cell_cpy.list.at(cell_cpy.list.size() - 1);
    // pop back enclosing array
    cell_cpy.list.pop_back();
    auto arr_cell = add_array_class(cell_cpy, _class_file_name);
    array_elements_type.token = arr_cell.variable_type;
  }
  // printf("make array class file name %s\n", _class_file_name.c_str());
  auto array_class_name =
      "Array_" + array_elements_type.token + "_" + array_capacity.token;
  array_cell.variable_type = array_class_name;
  // if the array class has already been added we don't need to add it again
  // do an early return.
  auto class_it = class_dict.find(array_class_name);
  if (class_it != class_dict.end()) {
    return array_cell;
  }
  // create and add array class
  auto ct_class = CTClass();
  ct_class.file_name = file_name;
  ct_class.class_name = array_class_name;
  ct_class.array_dimensions = array_dimensions;
  auto array_param = CTCell(CTCellType::Array, "arr", _class_file_name, 0, 0);
  auto size_param = CTCell(CTCellType::Int, "size", _class_file_name, 0, 0);
  auto capacity_param =
      CTCell(CTCellType::Int, "capacity", _class_file_name, 0, 0);
  // hackery, because at takes "arr" set it to the classname of the array
  // class so that it knows its an array. This is very hacky.
  array_param.variable_type = array_class_name;
  array_param.array_elements_type = array_elements_type.token;
  size_param.variable_type = "int";
  capacity_param.variable_type = "int";
  ct_class.array_elements_type = array_elements_type.token;
  ct_class.array_capacity = array_capacity.token;
  ct_class.member_vars.push_back(array_param);
  ct_class.member_vars.push_back(size_param);
  ct_class.member_vars.push_back(capacity_param);
  class_dict[array_class_name] = ct_class;
  class_def_insertion_order.push_back(ct_class);
  return array_cell;
}

CTCell CTCompiler::get_enum_value(CTCell &ct_cell) {
  if (!is_enum(ct_cell)) {
    printf(
        "CTCompiler::get_enum_value. cell is not an enum. Check if it is "
        "before calling this function.\nCell token: %s\n",
        ct_cell.token.c_str());
    abort();
  }
  if (enum_dict.find(ct_cell.token) == enum_dict.end()) {
    printf("CTCompiler::get_enum_value. Enum '%s' is not in the enum dict.\n",
           ct_cell.token.c_str());
    abort();
  }
  return enum_dict[ct_cell.token];
}

CTCell CTCompiler::get_dot_notation_var(CTFunction &ct_func,
                                        vector<CTCell> &local_vars, CTCell var,
                                        bool do_local_var_lookup) {
  if (is_enum(var)) {
    return get_enum_value(var);
  }
  auto contains_dot = var.token.find('.') != string::npos;
  if (contains_dot) {
    auto split = string_split(var.token, '.');
    if (split.size() == 0) {
      printf("'=', split size is 0.\n");
      print_eval_cell_info(ct_func, var);
      abort();
    }
    auto local_var_cell = var;
    local_var_cell.token = split.at(0);
    auto local_var = get_local_var(local_vars, local_var_cell);
    bool is_r_value = local_var.is_r_value;
    if (is_primitive_type(local_var)) {
      printf(
          "CTCompiler::get_dot_notation_var. '='. Expected first var '%s' in "
          "dot "
          "notation '%s' to be a class, instead found a primitive of type "
          "'%s'.\n",
          local_var.token.c_str(), var.token.c_str(),
          local_var.variable_type.c_str());
      print_eval_cell_info(ct_func, var);
      abort();
    }
    // can't do a reference because it gets reset below
    auto ct_class = get_class(local_var.variable_type);
    for (int i = 1; i < split.size(); i++) {
      auto &s = split.at(i);
      auto member_var = get_member_var(ct_func, var, ct_class, s);
      member_var.is_r_value = is_r_value;
      if (i == split.size() - 1) {
        var = member_var;
        var.is_r_value = is_r_value;
      } else if (!is_primitive_type(member_var)) {
        ct_class = get_class(member_var.variable_type);
      } else if (is_primitive_type(member_var) && i != split.size() - 1) {
        printf(
            "CTCompiler::get_dot_notation_var. '='. variable '%s', non-final "
            "primitive '%s' is of type '%s', which is not a class. dot "
            "syntax reached a non-final "
            "member that was a primitive. Primitives must be the final "
            "member.\n",
            var.token.c_str(), s.c_str(), member_var.variable_type.c_str());
        print_eval_cell_info(ct_func, var);
        abort();
      } else {
        printf(
            "CTCompiler::get_dot_notation_var. '='. dot syntax reached "
            "unexpected "
            "branch.\n");
        print_eval_cell_info(ct_func, var);
        abort();
      }
      // printf("dot split %s\n", s.c_str());
    }
  }
  if (!contains_dot && do_local_var_lookup) {
    return get_local_var(local_vars, var);
  } else {
    return var;
  }
}

bool CTCompiler::is_pointer(string &variable_type) {
  return variable_type.find("*") != string::npos;
}

bool CTCompiler::is_primitive_type(CTCell &ct_cell) {
  if (is_enum(ct_cell)) {
    return true;
  }
  if (ct_cell.variable_type == "char*") {
    return true;
  }
  // if its a pointer check if its a primitive pointer thats not a char*,
  // such as int*. int* should still be treated as a primitive.
  if (is_pointer(ct_cell.variable_type)) {
    auto type = ct_cell.variable_type;
    type.pop_back();
    return is_primitive_type(type);
  }
  return ct_cell.variable_type == "int" || ct_cell.variable_type == "Uint8" ||
         ct_cell.variable_type == "Uint32" ||
         ct_cell.variable_type == "Uint64" ||
         ct_cell.variable_type == "long unsigned int" ||
         ct_cell.variable_type == "double" || ct_cell.variable_type == "bool" ||
         ct_cell.variable_type == "char" || ct_cell.variable_type == "char*";
}

bool CTCompiler::is_primitive_type(string &variable_type) {
  if (is_enum(variable_type)) {
    return true;
  }
  if (variable_type == "char*") {
    return true;
  }
  // if its a pointer check if its a primitive pointer thats not a char*,
  // such as int*. int* should still be treated as a primitive.
  if (is_pointer(variable_type)) {
    auto type = variable_type;
    type.pop_back();
    return is_primitive_type(type);
  }
  return variable_type == "int" || variable_type == "Uint8" ||
         variable_type == "Uint32" || variable_type == "Uint64" ||
         variable_type == "long unsigned int" || variable_type == "double" ||
         variable_type == "bool" || variable_type == "char" ||
         variable_type == "char*";
}

bool CTCompiler::is_enum(CTCell &ct_cell) {
  // look in both dicts because sometimes the top level enum (ImageName) will
  // be passed, or an enum value (ImageName_Abilities) will be passed.
  return enum_name_dict.find(ct_cell.token) != enum_name_dict.end() ||
         enum_dict.find(ct_cell.token) != enum_dict.end();
}

bool CTCompiler::is_enum(string &variable_type) {
  // look in both dicts because sometimes the top level enum (ImageName) will
  // be passed, or an enum value (ImageName_Abilities) will be passed.
  return enum_name_dict.find(variable_type) != enum_name_dict.end() ||
         enum_dict.find(variable_type) != enum_dict.end();
}

bool CTCompiler::is_class_type(CTCell &ct_cell) {
  return is_class_type(ct_cell.variable_type);
}

bool CTCompiler::is_class_type(string variable_type) {
  variable_type = remove_ptr_substr_if_needed(variable_type);
  for (auto &entry : class_dict) {
    if (entry.first == variable_type) {
      return true;
    }
  }
  return false;
}

bool CTCompiler::is_token_a_class_type(CTCell &ct_cell) {
  for (auto &entry : class_dict) {
    if (entry.first == ct_cell.token) {
      return true;
    }
  }
  return false;
}

string CTCompiler::format_type_for_compiled_function(string variable_type) {
  replaceAll(variable_type, "*", "Ptr");
  return variable_type;
}

string CTCompiler::remove_ptr_substr_if_needed(string tok) {
  // remove any pointers from the class name, so Unit* becomes Unit.
  // don't do this for char* as it is a primitive (though it should never
  // call this function anyway).
  if (tok != "char*" && tok.find("*") != string::npos) {
    tok.erase(tok.find("*"), 1);
  }
  return tok;
}

bool CTCompiler::already_compiled_file(string &_file_name) {
  for (auto &f_name : compiled_files) {
    if (f_name == _file_name) {
      return true;
    }
  }
  return false;
}

void CTCompiler::get_imported_files() {
  for (auto &cell : file_cells) {
    if (cell.cell_type != CTCellType::List) {
      printf(
          "CTCompiler::get_imported_files. Expected each line to be a cell "
          "of type "
          "list. Found type '%d'\nFile: '%s'\nLine number: '%d'.\n",
          (int)cell.cell_type, cell.file_name.c_str(), cell.line_number);
      abort();
    }
    if (cell.list.size() > 0) {
      auto &first_cell = cell.list.at(0);
      if (first_cell.token == "import") {
        if (cell.list.size() != 2) {
          printf(
              "CTCompiler::get_imported_files. 'import' expects a list of "
              "size "
              "'2', found a list with size '%ld'.\n",
              cell.list.size());
          abort();
        }
        auto _file_name = cell.list.at(1);
        // printf("imported file name %s\n", _file_name.token.c_str());
        imported_files.push_back(_file_name.token);
        auto imported_dict_it = file_import_dict.find(file_name);
        if (imported_dict_it == file_import_dict.end()) {
          printf(
              "CTCompiler::get_imported_files. file_import_dict does not "
              "contain file '%s'.\n",
              file_name.c_str());
        }
        file_import_dict.at(file_name).push_back(_file_name.token);
      } else if (first_cell.token == "weak_import") {
        if (cell.list.size() != 2) {
          printf(
              "CTCompiler::get_imported_files. 'weak_import' expects a list "
              "of "
              "size "
              "'2', found a list with size '%ld'.\n",
              cell.list.size());
          abort();
        }
        auto _file_name = cell.list.at(1);
        // printf("weak imported file name %s\n", _file_name.token.c_str());
        imported_files.push_back(_file_name.token);
        auto imported_dict_it = file_weak_import_dict.find(file_name);
        if (imported_dict_it == file_weak_import_dict.end()) {
          printf(
              "CTCompiler::get_imported_files. file_weak_import_dict does "
              "not "
              "contain file '%s'.\n",
              file_name.c_str());
        }
        file_weak_import_dict.at(file_name).push_back(_file_name.token);
      }
    }
  }
}

string CTCompiler::get_array_elements_type_from_string_name(
    string _array_class_name) {
  if (_array_class_name.size() == 0) {
    printf(
        "CTCompiler::get_array_elements_type_from_string_name. name has a "
        "size of 0.\n");
    abort();
  }
  auto split = string_split(_array_class_name, '_');
  if (split.size() == 0) {
    printf(
        "CTCompiler::get_array_elements_type_from_string_name. split of '_' "
        "has a "
        "size of 0.\n");
    abort();
  }
  auto rebuilt_type_str = string("");
  // skip "Array" (idx 0) and the size (idx size - 1)
  for (int i = 1; i < split.size() - 1; i++) {
    rebuilt_type_str += split.at(i);
    // handles cases like SDL_Rect
    if (i != split.size() - 2) {
      rebuilt_type_str += "_";
    }
  }
  return rebuilt_type_str;
}

CTFunction &CTCompiler::get_instantiated_func(string compiled_function_name) {
  for (auto &ct_func : instantiated_functions) {
    if (ct_func.compiled_function_name == compiled_function_name) {
      return ct_func;
    }
  }
  printf(
      "CTCompiler::get_instantiated_func. Compiled function '%s' is "
      "undefined.\n",
      compiled_function_name.c_str());
  abort();
  return function_dict.at("main");
}

CTClass &CTCompiler::get_class(string class_name) {
  class_name = remove_ptr_substr_if_needed(class_name);
  for (auto &entry : class_dict) {
    if (entry.first == class_name) {
      return class_dict.at(entry.first);
    }
  }
  printf("CTCompiler::get_class. Class '%s' is undefined.\n",
         class_name.c_str());
  printf(
      "Missing an enum value can cause this error. If the class_name string is "
      "empty then it definitely is a missing enum value.\n");
  abort();
  return class_dict.at("main");
}

void CTCompiler::get_classes() {
  auto ct_class = CTClass();
  auto parsing_class = false;
  for (auto &cell : file_cells) {
    // non-empty lines must have a single list (one list for each line)
    if (cell.cell_type != CTCellType::List) {
      printf(
          "CTCompiler::get_classes. Expected each line to be a cell of type "
          "list. Found type '%d'.\n",
          (int)cell.cell_type);
      abort();
    }
    // empty line, each line gets a '(' and ')' added os empty line are just
    // "(  )".
    if (cell.list.size() == 0) {
      if (parsing_class) {
        parsing_class = false;
        class_dict[ct_class.class_name] = ct_class;
        class_def_insertion_order.push_back(ct_class);
        ct_class = CTClass();
      }
      continue;
    }
    auto &first_cell = cell.list.at(0);
    if (parsing_class) {
      // not sure how array syntax works, maybe (Unit 20) so that its a list?
      // or just allow different list sizes for [Unit 20]
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::get_classes. defclass member variable list expects "
            "a size of '2'. found '%ld'\n",
            cell.list.size());
        abort();
      }
      if (cell.list.at(0).cell_type == CTCellType::Symbol) {
        auto member_var = cell.list.at(1);
        // if using a semicolon at the end just remove it (copy pasted c
        // struct over)
        if (member_var.token.at(member_var.token.size() - 1) == ';') {
          member_var.token.pop_back();
        }
        if (member_var.token.at(0) == '*') {
          printf(
              "CTCompiler::get_classes. Member var for class has '*' as the "
              "token. The ptr * needs to be in the first type's value, not "
              "the "
              "variable name.\nExample:\nSDL_Window *window "
              "should be "
              "SDL_Window* window.\n\nvariable: \"%s\"\n",
              member_var.token.c_str());
          abort();
        }
        if (cell.list.at(0).token == "=") {
          printf(
              "CTCompiler::get_classes. Class member variable type is "
              "missing.\nclass: "
              "'%s'\nvar name: '%s'\nfile name: '%s'\nline_number: '%d'",
              ct_class.class_name.c_str(), member_var.token.c_str(),
              file_name.c_str(), cell.line_number);
          abort();
        }
        member_var.variable_type = cell.list.at(0).token;
        ct_class.member_vars.push_back(member_var);
      } else if (cell.list.at(0).cell_type == CTCellType::List) {
        auto class_list_cell = cell.list.at(0);
        if (class_list_cell.list.at(0).token != "make_array") {
          printf(
              "CTCompiler::get_classes. First list must be a make_array "
              "list, "
              "so the expected firs token is 'make_array', found '%s'.\n",
              class_list_cell.list.at(0).token.c_str());
          abort();
        }
        auto array_cell = add_array_class(class_list_cell, ct_class.file_name);
        auto member_var = cell.list.at(1);
        // if using a semicolon at the end just remove it (copy pasted c
        // struct over)
        if (member_var.token.at(member_var.token.size() - 1) == ';') {
          member_var.token.pop_back();
        }
        if (member_var.token.at(0) == '*') {
          printf(
              "CTCompiler::get_classes. Member var for class has '*' as the "
              "token. The ptr * needs to be in the first type's value, not "
              "the "
              "variable name.\nExample:\nSDL_Window *window "
              "should be "
              "SDL_Window* window.\n\nvariable: \"%s\"\n",
              member_var.token.c_str());
          abort();
        }
        member_var.variable_type = array_cell.variable_type;
        ct_class.member_vars.push_back(member_var);
      }
    } else if (first_cell.token == "defclass") {
      if (parsing_class) {
        printf(
            "CTCompiler::get_classes. defclass cannot have deflass "
            "lists in the function body. This can be caused by not having "
            "an empty line after a defun ends.\n");
        abort();
      }
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::get_classes. declass expects a list of size '3', "
            "found "
            "a list of size '%ld'.\n",
            cell.list.size());
        abort();
      }
      if (cell.list[1].cell_type != CTCellType::Symbol) {
        printf(
            "CTCompiler::get_classes. defclass's second element must be a "
            "symbol. Found a cell with type '%d'.\n",
            (int)cell.list[1].cell_type);
        abort();
      }
      auto class_dict_it = class_dict.find(cell.list.at(1).token);
      if (class_dict_it != class_dict.end()) {
        printf(
            "CTCompiler::get_classes. class '%s' is already defined. class "
            "redefinition error.\n",
            cell.list.at(1).token.c_str());
        abort();
      } else {
        parsing_class = true;
        ct_class.file_name = file_name;
        ct_class.class_name = cell.list.at(1).token;
      }
    }
  }
}

void CTCompiler::get_enums() {
  CTCell enum_cell = CTCell();
  auto parsing_enum = false;
  for (auto &cell : file_cells) {
    // non-empty lines must have a single list (one list for each line)
    if (cell.cell_type != CTCellType::List) {
      printf(
          "CTCompiler::get_enums. Expected each line to be a cell of type "
          "list. Found type '%d'.\n",
          (int)cell.cell_type);
      abort();
    }
    // empty line, each line gets a '(' and ')' added os empty line are just
    // "(  )".
    if (cell.list.size() == 0) {
      if (parsing_enum) {
        parsing_enum = false;
      }
      continue;
    }
    auto &first_cell = cell.list.at(0);
    if (parsing_enum) {
      // not sure how array syntax works, maybe (Unit 20) so that its a list?
      // or just allow different list sizes for [Unit 20]
      if (cell.list.size() != 1) {
        printf(
            "CTCompiler::get_enums. defenum member variable list expects "
            "a size of '1'. found '%ld'\n",
            cell.list.size());
        abort();
      }
      if (cell.list.at(0).cell_type == CTCellType::Symbol) {
        auto enum_token = cell.list.at(0).token;
        // if using a comma at the end just remove it (copy pasted c struct
        // over)
        if (enum_token.at(enum_token.size() - 1) == ',') {
          enum_token.pop_back();
        }
        // enums are of the form ImageName.Abilities, format later when
        // outputting to c.
        auto final_enum_token = enum_cell.token + "." + enum_token;
        // add it to the enum name dict for easy outputting to c
        auto enum_value_cell = CTCell();
        enum_value_cell.token = final_enum_token;
        enum_value_cell.variable_type = enum_cell.token;
        enum_value_cell.file_name = file_name;
        // add the enum value for easy lookup when comparing,
        // value is the enum it belongs to.
        enum_dict[final_enum_token] = enum_value_cell;
        enum_name_dict[enum_cell.token].push_back(enum_value_cell);
      }
    } else if (first_cell.token == "defenum") {
      if (parsing_enum) {
        printf(
            "CTCompiler::get_enums. defenum cannot have deflass "
            "lists in the function body. This can be caused by not having "
            "an empty line after a defun ends.\n");
        abort();
      }
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::get_enums. defenum expects a list of size '3', "
            "found "
            "a list of size '%ld'.\n",
            cell.list.size());
        abort();
      }
      if (cell.list[1].cell_type != CTCellType::Symbol) {
        printf(
            "CTCompiler::get_enums. defenum's second element must be a "
            "symbol. Found a cell with type '%d'.\n",
            (int)cell.list[1].cell_type);
        abort();
      }
      enum_cell.token = cell.list.at(1).token;
      enum_cell.variable_type = cell.list.at(1).token;
      enum_cell.file_name = file_name;
      auto enum_name_it = enum_name_dict.find(enum_cell.token);
      if (enum_name_it != enum_name_dict.end()) {
        printf(
            "CTCompiler::get_enums. enum '%s' is already defined. enum "
            "redefinition error.\n",
            enum_cell.token.c_str());
        abort();
      } else {
        parsing_enum = true;
        enum_name_dict[enum_cell.token] = vector<CTCell>();
      }
    }
  }
}

void CTCompiler::get_functions() {
  auto ct_func = CTFunction();
  auto parsing_function = false;
  auto is_class_member_func = false;
  auto inside_class_name = string("");
  for (int i = 0; i < file_cells.size(); i++) {
    auto &cell = file_cells.at(i);
    // non-empty lines must have a single list (one list for each line)
    if (cell.cell_type != CTCellType::List) {
      printf(
          "CTCompiler::get_functions. Expected each line to be a cell of "
          "type "
          "list. Found type '%d'.\n",
          (int)cell.cell_type);
      abort();
    }
    if (cell.list.size() > 0 && cell.list.at(0).token == "defclass") {
      if (cell.list.size() != 2) {
        printf(
            "CTCompiler::get_functions. inside class name expects defclass to "
            "have a size of 2, found '%ld'.\n",
            cell.list.size());
        abort();
      }
      inside_class_name = cell.list.at(1).token;
    }
    // empty line, each line gets a '(' and ')' added os empty line are just
    // "(  )".
    // for some reason in python class member funcs only have 1 space between
    // them, not two, so im handling that with that is_class_member_func clause.
    if (i == file_cells.size() - 1 ||
        (is_class_member_func && cell.list.size() == 0 &&
         i < file_cells.size() - 1 &&
         file_cells.at(i + 1).indent == indent_size &&
         file_cells.at(i + 1).list.size() > 0) ||
        (cell.list.size() == 0 && i < file_cells.size() - 1 &&
         file_cells.at(i + 1).indent == 0 &&
         file_cells.at(i + 1).list.size() > 0)) {
      if (parsing_function) {
        parsing_function = false;
        function_dict[ct_func.function_name] = ct_func;
        func_def_insertion_order.push_back(ct_func);
        ct_func = CTFunction();
      }
      continue;
    }
    if (parsing_function && cell.list.size() > 0) {
      if (is_class_member_func) {
        auto c = cell;
        c.indent -= indent_size;
        ct_func.cells.push_back(c);
      } else {
        ct_func.cells.push_back(cell);
      }
    } else if (cell.list.size() > 0 && cell.list.at(0).token == "defun") {
      if (parsing_function) {
        printf(
            "CTCompiler::get_functions. defun cannot have defun "
            "lists in the function body. This can be caused by not having "
            "an empty line after a defun ends.\n");
        abort();
      }
      if (cell.list.size() != 4) {
        printf(
            "CTCompiler::get_functions. defun expects a list of size '4', "
            "found "
            "a list of size '%ld'.\n",
            cell.list.size());
        abort();
      }
      if (cell.list[1].cell_type != CTCellType::Symbol) {
        printf(
            "CTCompiler::get_functions. defun's second element must be a "
            "symbol. Found a cell with type '%d'.\n",
            (int)cell.list[1].cell_type);
        abort();
      }
      if (cell.list[2].cell_type != CTCellType::List) {
        printf(
            "CTCompiler::get_functions. defun's third element must be a "
            "list. Found a cell with type '%d'.\n",
            (int)cell.list[2].cell_type);
        abort();
      }
      if (!(cell.indent == 0 || cell.indent == 4)) {
        printf(
            "CTCompiler::get_functions. Expected function indent is one that "
            "starts at 0 (normal function) or 4 (member function), found "
            "function indent of '%d'. File name: '%s'\n ",
            cell.indent, file_name.c_str());
        abort();
      }
      // if the indent is greater than 0 it is nested in a class definition and
      // is a class member func.
      is_class_member_func = cell.indent != 0;
      auto function_dict_it = function_dict.find(cell.list.at(1).token);
      // class member function redefinition erros will be checked below,
      // this just checks normal function redefinition errors.
      if (!is_class_member_func && function_dict_it != function_dict.end()) {
        // functions may be defined for intellisense after c func or
        // c library func blocks, but not actually used. Continue if the
        // function is such a function.
        auto &f = function_dict.at(cell.list.at(1).token);
        if (f.is_c_func || f.is_c_library_func) {
          continue;
        } else {
          printf(
              "CTCompiler::get_functions. function '%s' is already defined. "
              "function "
              "redefinition error.\nFile: '%s'\nline: '%d'\n",
              cell.list.at(1).token.c_str(), cell.list.at(1).file_name.c_str(),
              cell.list.at(1).line_number);
          abort();
        }
      } else {
        parsing_function = true;
        ct_func.file_name = file_name;
        ct_func.function_name = cell.list.at(1).token;
        ct_func.return_enforced_type = cell.list.at(3);
        ct_func.return_enforced_type.variable_type =
            ct_func.return_enforced_type.token;
        ct_func.is_member_func = is_class_member_func;
        if (ct_func.is_member_func) {
          // change function name so that it doesn't collide with normal
          // functions
          ct_func.function_name = get_class_member_func_name(
              inside_class_name, cell.list.at(1).token);
          ct_func.stacktrace_pretty_func_name = get_stacktrace_pretty_func_name(
              inside_class_name, cell.list.at(1).token);
          ct_func.member_func_of_class_name = inside_class_name;
          // add to class member dict
          if (class_member_func_dict.find(inside_class_name) ==
              class_member_func_dict.end()) {
            class_member_func_dict[inside_class_name] = vector<string>();
          }
          auto &class_member_funcs =
              class_member_func_dict.at(inside_class_name);
          for (auto &f : class_member_funcs) {
            if (f == ct_func.function_name) {
              printf(
                  "CTCompiler::get_functions. Class member function '%s' for "
                  "class '%s' is "
                  "already "
                  "defined. "
                  "function "
                  "redefinition error.\n",
                  ct_func.function_name.c_str(), inside_class_name.c_str());
              abort();
            }
          }
          // using the unmangled name here becuase I need it when trying to
          // figure out if the unmangled function name is a member function or
          // not. i.e. "init" instead of "mfunc_Game_init".
          class_member_func_dict[inside_class_name].push_back(
              cell.list.at(1).token);
        } else {
          ct_func.stacktrace_pretty_func_name = ct_func.function_name;
        }
        /*if (ct_func.is_member_func) {
          auto inside_class_name_ptr = inside_class_name + "*";
          auto class_cell =
              CTCell(CTCellType::Symbol, inside_class_name, cell.file_name,
                     cell.line_number, cell.indent);
          class_cell.variable_type = inside_class_name_ptr;
          ct_func.params.push_back(class_cell);
          ct_func.params_enforced_types.push_back(class_cell);
        }*/
        for (auto &param : cell.list.at(2).list) {
          if (param.cell_type != CTCellType::List) {
            printf(
                "CTCompiler::get_functions. params must be of type list (var "
                "type). Found type '%d'.\n",
                (int)param.cell_type);
            abort();
          }
          if (param.list.size() != 2) {
            printf(
                "CTCompiler::get_functions. Expected each param to be a list "
                "of size '2', found size '%ld'\n",
                param.list.size());
            abort();
          }
          ct_func.params.push_back(param.list.at(0));
          auto enforced_type = param.list.at(1);
          enforced_type.variable_type = enforced_type.token;
          ct_func.params_enforced_types.push_back(enforced_type);
        }
        if (is_class_member_func) {
          auto c = cell;
          c.indent -= indent_size;
          ct_func.cells.push_back(c);
        } else {
          ct_func.cells.push_back(cell);
        }
      }
    }
  }
}

void CTCompiler::print_function_dict() {
  for (auto &entry : function_dict) {
    print_function(entry.second);
  }
}

void CTCompiler::print_function(CTFunction &ct_func) {
  printf("\nfile: %s - %s(", ct_func.file_name.c_str(),
         ct_func.function_name.c_str());
  for (int i = 0; i < ct_func.params.size(); i++) {
    printf("%s", ct_func.params[i].token.c_str());
    if (i != ct_func.params.size() - 1) {
      printf(" ");
    }
  }
  printf(") - %ld params\n", ct_func.params.size());
  for (auto &cell : ct_func.cells) {
    printf("%d - %d - ", cell.line_number, cell.indent);
    print_cell(cell);
    printf("\n");
  }
}

void CTCompiler::print_class_dict() {
  for (auto &entry : class_dict) {
    print_class(entry.second);
  }
}

void CTCompiler::print_class(CTClass &ct_class) {
  printf("\nfile: %s - %s\n", ct_class.file_name.c_str(),
         ct_class.class_name.c_str());
  for (auto &member_var : ct_class.member_vars) {
    printf("%s %s\n", member_var.variable_type.c_str(),
           member_var.token.c_str());
  }
}

void CTCompiler::print_cell(CTCell &cell) {
  if (cell.cell_type == CTCellType::List) {
    printf("( ");
    for (auto &c : cell.list) {
      print_cell(c);
    }
    printf(") ");
  } else {
    printf("%s ", cell.token.c_str());
  }
}

bool CTCompiler::is_array(CTCell &cell) {
  return cell.variable_type.find("Array") != string::npos;
}

bool CTCompiler::is_array(string &variable_type) {
  return variable_type.find("Array") != string::npos;
}

string CTCompiler::get_array_capacity(CTCell &cell) {
  if (!is_array(cell)) {
    printf("CTCompiler::get_array_capacity. cell is not an array.");
    abort();
  }
  auto array_class = get_class(cell.variable_type);
  auto split = string_split(cell.variable_type, '_');
  if (split.size() < 3) {
    printf(
        "CTCompiler::get_array_capacity. array class name split size is < "
        "3.");
    abort();
  }
  auto cap_str = split.at(2);
  replaceAll(cap_str, "*", "");
  return cap_str;
}

string CTCompiler::get_array_capacity(string &variable_type) {
  auto split = string_split(variable_type, '_');
  if (split.size() < 3) {
    printf(
        "CTCompiler::get_array_capacity. array class name split size is < "
        "3.");
    abort();
  }
  auto cap_str = split.at(split.size() - 1);
  replaceAll(cap_str, "*", "");
  return cap_str;
}

// make sure to pass in a cpy because line's tokens are erased
CTCell CTCompiler::read_from_tokens(CTLine &line) {
  if (line.tokens.size() == 0) {
    return CTCell(CTCellType::None, "", file_name, line.line_number,
                  line.indent);
  }
  auto token = line.tokens[0];
  line.tokens.erase(line.tokens.begin() + 0);
  if (token == "(") {
    auto cell =
        CTCell(CTCellType::List, "(", file_name, line.line_number, line.indent);
    while (line.tokens[0] != ")") {
      cell.list.push_back(read_from_tokens(line));
    }
    line.tokens.erase(line.tokens.begin() + 0);
    return cell;
  } else if (token == ")") {
    printf("CTCompiler::read_from_tokens. Unexpected ')'");
    abort();
  } else {
    bool contains_dot = false;
    bool is_numeric = true;
    for (int i = 0; i < token.size(); i++) {
      auto c = token[i];
      // ignore dot for digit check because of double
      // token.size() > 1
      if (!isdigit(c) && c != '.') {
        is_numeric = false;
      }
      if (c == '.') {
        contains_dot = true;
      }
    }
    if (is_numeric && !contains_dot) {
      auto ct_cell = CTCell(CTCellType::Int, token, file_name, line.line_number,
                            line.indent);
      ct_cell.variable_type = "int";
      return ct_cell;
    } else if (is_numeric && contains_dot) {
      auto ct_cell = CTCell(CTCellType::Double, token, file_name,
                            line.line_number, line.indent);
      ct_cell.variable_type = "double";
      return ct_cell;
    } else if (token[0] == '\'') {
      if (token[token.size() - 1] != '\'') {
        printf(
            "CTCompiler::read_from_tokens. char does not have "
            "closing quote.\n");
        abort();
      }
      auto ct_cell = CTCell(CTCellType::Char, token, file_name,
                            line.line_number, line.indent);
      ct_cell.variable_type = "char";
      return ct_cell;
    } else if (token[0] == '"') {
      // printf("last char %s\n", token.c_str());
      if (token[token.size() - 1] != '"') {
        printf(
            "CTCompiler::read_from_tokens. String does not have "
            "closing quote.\n");
        abort();
      }
      auto ct_cell = CTCell(CTCellType::CharPointer, token, file_name,
                            line.line_number, line.indent);
      ct_cell.variable_type = "char*";
      return ct_cell;
    } else if (token == "true" || token == "false") {
      auto ct_cell = CTCell(CTCellType::Bool, token, file_name,
                            line.line_number, line.indent);
      ct_cell.variable_type = "bool";
      return ct_cell;
    } else {
      return CTCell(CTCellType::Symbol, token, file_name, line.line_number,
                    line.indent);
    }
  }
}

void CTCompiler::replaceAll(std::string &str, const std::string &from,
                            const std::string &to) {
  if (from.empty()) return;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();  // In case 'to' contains 'from', like replacing
                               // 'x' with 'yx'
  }
}

vector<string> CTCompiler::string_split(const string &s, char delim) {
  stringstream ss(s);
  string item;
  vector<string> elems;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
    // elems.push_back(move(item)); // if C++11 (based on comment from
    // @mchiasson)
  }
  return elems;
}

int CTCompiler::num_leading_spaces(string &s) {
  int num = 0;
  for (auto c : s) {
    if (isspace((int)c)) {
      num += 1;
    } else {
      return num;
    }
  }
  // if all spaces return 0 (empty line)
  return 0;
}

int CTCompiler::num_trailing_spaces(string &s) {
  int num = 0;
  for (int i = s.size() - 1; i > -1; i++) {
    auto c = s[i];
    if (isspace((int)c)) {
      num += 1;
    } else {
      return num;
    }
  }
  // if all spaces return 0 (empty line)
  return 0;
}

void CTCompiler::remove_leading_spaces(string &s) {
  while (!s.empty() && std::isspace(*s.begin())) s.erase(s.begin());
}

void CTCompiler::remove_trailing_spaces(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](int ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

void CTCompiler::remove_trailing_spaces_only(string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return ch != ' '; })
              .base(),
          s.end());
}

void CTCompiler::update_make_file() {
  ifstream inFile;
  string make_file_path = "../CMakeLists.txt";
  inFile.open(make_file_path.c_str());
  if (!inFile.good()) {
    printf("CTCompiler - make file not found.\n");
    abort();
  }
  auto parsing_c_lines = false;
  int line_number = 0;
  string file_contents = "";
  vector<string> lines;
  vector<string> c_file_lines;
  unordered_map<string, bool> c_files_dict;
  string line = "";
  int c_file_line_start = -1;
  int c_files_line_end = -1;
  while (getline(inFile, line, '\n')) {
    // printf("make_file line %s\n", line.c_str());
    string trim_line = line;
    remove_leading_spaces(trim_line);
    remove_trailing_spaces(trim_line);
    lines.push_back(line + "\n");
    if (trim_line == "# generated c files") {
      parsing_c_lines = true;
      c_file_line_start = line_number;
    } else if (parsing_c_lines && trim_line == ")") {
      parsing_c_lines = false;
      c_files_line_end = line_number;
    } else if (parsing_c_lines) {
      c_files_dict[trim_line] = true;
      c_file_lines.push_back(trim_line);
    }
    line_number += 1;
  }

  if (c_file_line_start == -1 || c_files_line_end == -1) {
    printf("CTCompiler::ouptut_make_file. c file line start or end is -1.\n");
    abort();
  }
  // skip the comment
  c_file_line_start += 1;
  string base_c_file_directory = "src/ct/game/";
  auto executable_file_name = "game_main";
  // see if we actually need to update the makefile (if new c files have been
  // added)
  auto new_files_added = false;
  for (auto &f : compiled_files) {
    if (f == executable_file_name) {
      continue;
    }
    if (c_files_dict.find(base_c_file_directory + f + ".c") ==
        c_files_dict.end()) {
      new_files_added = true;
      break;
    }
  }
  if (!new_files_added) {
    printf("No new c files have been added. Make file is up to date.\n");
    return;
  }
  printf("New c files have been added. Updating make file.\n");
  // remove old c files
  lines.erase(lines.begin() + c_file_line_start,
              lines.begin() + c_files_line_end);
  // add new c files
  for (auto &f : compiled_files) {
    // skip executable file
    if (f == executable_file_name) {
      continue;
    }
    lines.insert(lines.begin() + c_file_line_start,
                 "   " + base_c_file_directory + f + ".c\n");
  }
  for (auto &line : lines) {
    file_contents += line;
  }
  for (auto &c_line : c_file_lines) {
    printf("c line %s\n", c_line.c_str());
  }
  // printf("%d %d\n", c_file_line_start, c_files_line_end);
  ofstream make_file(make_file_path.c_str());
  make_file << file_contents;
}

string CTCompiler::to_uppercase(string s) {
  string upper_s = s;
  for (auto &c : upper_s) {
    c = toupper(c);
  }
  return upper_s;
}

string CTCompiler::get_array_elements_type(string &array_class_name) {
  auto class_it = class_dict.find(array_class_name);
  if (class_it == class_dict.end()) {
    printf(
        "CTCompiler::get_array_elements_type - array class name not in "
        "class_dict, array_class_name: '%s'\n",
        array_class_name.c_str());
    abort();
  }
  auto &ct_class = class_dict.at(array_class_name);
  /* printf("get_array_elements_type: %s\n",
   * ct_class.array_elements_type.c_str()); */
  if (!is_array(array_class_name)) {
    printf(
        "CTCompiler::get_array_elements_type - array_class_name is expected "
        "to "
        "have array in the name, found '%s'.\n",
        array_class_name.c_str());
    abort();
  }
  /*auto split = string_split(array_class_name, '_');
  if (split.size() != 3) {
    printf(
        "CTCompiler::get_array_elements_type - array_class_name split is "
        "expected to have size '3', found size '%ld'. array_class_name:
  '%s'\n", split.size(), array_class_name.c_str()); abort();
  }*/
  // array class name should be named Array_Type_Capacity
  return ct_class.array_elements_type;
}

void CTCompiler::change_array_files_to_class_def_file() {
  // primtiive arrays
  class_array_dict["primitive"] = vector<CTClass>();
  // using class_def_insertion_order instead of class dict so that it can be
  // sorted by array dimensions. Need to sort arrays because higher
  // dimensional arrays reference lower dimensional arrays and must be
  // declared after lower dimensional arrays. make a copy here so that the
  // original insertion order is preserved
  auto class_def_insertion_order_cpy = class_def_insertion_order;
  sort(class_def_insertion_order_cpy.begin(),
       class_def_insertion_order_cpy.end(), [](CTClass &a, CTClass &b) -> bool {
         return a.array_dimensions < b.array_dimensions;
       });
  for (auto &ct_class : class_def_insertion_order_cpy) {
    if (!is_array(ct_class.class_name)) {
      class_array_dict[ct_class.class_name] = vector<CTClass>();
    }
  }
  for (int i = 0; i < class_def_insertion_order_cpy.size(); i++) {
    auto &ct_class = class_def_insertion_order_cpy.at(i);
    if (is_array(ct_class.class_name)) {
      /*auto array_elements_type =
          get_array_elements_type(entry.second.class_name);*/
      auto array_elements_type =
          get_array_elements_type_from_string_name(ct_class.class_name);
      /*printf("change arrays %s - %s %d\n", ct_class.class_name.c_str(),
             array_elements_type.c_str(), ct_class.array_dimensions);*/
      // all SDL based structs will get defined as primitive arrays as well for
      // now.
      if (is_primitive_type(array_elements_type) ||
          array_elements_type == "SDL_Point" ||
          array_elements_type == "SDL_Rect" ||
          array_elements_type == "SDL_Color") {
        // put all primitive arrays in the ct_array file
        ct_class.file_name = "ct_array";
        class_array_dict["primitive"].push_back(ct_class);
      } else {
        // if array of Unit, this gets the class Unit
        auto &array_elements_class = get_class(array_elements_type);
        /*printf("non primitive file %s\n",
               array_elements_class.file_name.c_str());*/
        ct_class.file_name = array_elements_class.file_name;
        class_array_dict[array_elements_type].push_back(ct_class);
        // update the new file name in the other class containers as well.
        for (auto &c : class_def_insertion_order) {
          if (c.class_name == ct_class.class_name) {
            c.file_name = ct_class.file_name;
          }
        }
        class_dict[ct_class.class_name].file_name = ct_class.file_name;
      }
    }
  }
}

void CTCompiler::output_c_files() {
  change_array_files_to_class_def_file();
  auto main_func = get_instantiated_func("main");
  for (auto &compiled_file : compiled_files) {
    auto is_main_func = compiled_file == main_func.file_name;
    h_file_output.clear();
    c_file_output.clear();
    // include guard
    h_file_output += "#ifndef GAME_" + to_uppercase(compiled_file) + "\n";
    h_file_output += "#define GAME_" + to_uppercase(compiled_file) + "\n\n";

    // imported files (not sure if stb ttf should be imported everywhere,
    // maybe change later if necessary).
    h_file_output +=
        "#include <SDL2/SDL.h>\n#include <SDL2/SDL_image.h>\n#include "
        "<SDL2/SDL_mixer.h>\n#include "
        "<SDL2/SDL_ttf.h>\n#include <stdbool.h>\n#include \"stbttf_sdl.h\"\n";
    c_file_output +=
        "#include <SDL.h>\n#include <stdio.h>\n#include <stdlib.h>\n#include "
        "<stdbool.h>\n#include <string.h>\n#include <math.h>\n#include "
        "\"ct_stacktrace.h\"\n";
    // engine needs rand
    if (compiled_file == "engine") {
      h_file_output += "#include \"mtwister.h\"\n";
      c_file_output += "#include <time.h>\n";
    }
    if (!is_main_func) {
      c_file_output += "#include \"" + compiled_file + ".h\"\n";
    }
    auto imported_files = file_import_dict.at(compiled_file);
    for (auto &imported_file : imported_files) {
      h_file_output += "#include \"" + imported_file + ".h\"\n";
      c_file_output += "#include \"" + imported_file + ".h\"\n";
    }
    for (auto &weak_imported_file : file_weak_import_dict.at(compiled_file)) {
      c_file_output += "#include \"" + weak_imported_file + ".h\"\n";
    }
    h_file_output += "\n";
    c_file_output += "\n";

    // output forward declared structs
    int num_forward_declares = 0;
    if (is_debug) {
      // forward declare stack trace if in debug
      h_file_output += "struct CT_StackTrace;\n";
      num_forward_declares += 1;
    }
    // forward declare all structs defined in each weak import file
    auto &param_types_in_file = function_param_types_in_file.at(compiled_file);
    /*printf("file %s dict size %ld\n", compiled_file.c_str(),
           param_types_in_file.size());
    for (auto &entry : param_types_in_file) {
      printf("file %s param type %s\n", compiled_file.c_str(),
             entry.first.c_str());
    }*/
    for (auto &weak_import : file_weak_import_dict.at(compiled_file)) {
      for (auto &ct_class : class_def_insertion_order) {
        auto class_name_with_ptr = ct_class.class_name + "*";
        /*printf("%s class_name w ptr %s %d\n", compiled_file.c_str(),
               class_name_with_ptr.c_str(),
               param_types_in_file.find(class_name_with_ptr) !=
                   param_types_in_file.end());*/
        // if the class is from a weak import and its actually used in a
        // function forward declare it.]
        if (ct_class.file_name == weak_import &&
            param_types_in_file.find(class_name_with_ptr) !=
                param_types_in_file.end()) {
          h_file_output += "struct " + ct_class.class_name + ";\n";
          num_forward_declares += 1;
        }
      }
    }
    if (num_forward_declares > 0) {
      h_file_output += "\n";
    }

    // output enums
    for (auto &val : enum_name_dict) {
      // skip any sdl enums used for intellisense
      if (val.first.find("SDL") != string::npos) {
        continue;
      }
      // should never happen
      if (val.second.size() == 0) {
        continue;
      }
      // continue if the enum val if its defined in this file.
      if (val.second.at(0).file_name != compiled_file) {
        continue;
      }
      h_file_output += "typedef enum " + val.first + " {\n";
      for (auto &e_val : val.second) {
        // format enum by replacing the '.' to a '_'. ImageName.Abilities
        // becomes ImageName_Abilities.
        auto enum_str_cpy = e_val.token;
        replaceAll(enum_str_cpy, ".", "_");
        h_file_output += "  " + enum_str_cpy + ",\n";
      }
      h_file_output += "} " + val.first + ";\n\n";
    }

    // output classes
    /*
    typedef struct TestStruct {
      int a;
    } TestStruct;
    */
    for (auto &ct_class_insertion_order : class_def_insertion_order) {
      // skip any sdl structs used for intellisense
      if (ct_class_insertion_order.class_name.find("SDL") != string::npos) {
        continue;
      }
      // this is slow but its just a sanity check, remove later if stable.
      auto class_it = class_dict.find(ct_class_insertion_order.class_name);
      if (class_it == class_dict.end()) {
        printf(
            "CTCompiler::output_c_files. Insertion order class is not in the "
            "class dict. Class name: %s\n",
            ct_class_insertion_order.class_name.c_str());
        abort();
      }
      auto &ct_class = class_dict[ct_class_insertion_order.class_name];
      if (ct_class.file_name != compiled_file) {
        continue;
      }
      if (is_array(ct_class.class_name)) {
        continue;
      }
      h_file_output += "typedef struct " + ct_class.class_name + " {\n";
      for (auto &member_var : ct_class.member_vars) {
        h_file_output +=
            "  " + member_var.variable_type + " " + member_var.token + ";\n";
      }
      h_file_output += "} " + ct_class.class_name + ";\n\n";

      // output arrays for this class after the class is defined. The arrays
      // are sorted by dimensionality, as a 2d array must come after a 1d
      // array as it references the 1d array.
      auto class_arrays = class_array_dict[ct_class.class_name];
      for (auto &class_array : class_arrays) {
        h_file_output += "typedef struct " + class_array.class_name + " {\n";
        for (auto &member_var : class_array.member_vars) {
          if (member_var.token == "arr") {
            h_file_output += "  " + class_array.array_elements_type + " arr[" +
                             class_array.array_capacity + "];\n";
          } else {
            h_file_output += "  " + member_var.variable_type + " " +
                             member_var.token + ";\n";
          }
        }
        h_file_output += "} " + class_array.class_name + ";\n\n";
      }
    }

    // output primitive arrays to ct_array
    if (compiled_file == "ct_array") {
      auto class_arrays = class_array_dict["primitive"];
      for (auto &class_array : class_arrays) {
        h_file_output += "typedef struct " + class_array.class_name + " {\n";
        for (auto &member_var : class_array.member_vars) {
          if (member_var.token == "arr") {
            h_file_output += "  " + class_array.array_elements_type + " arr[" +
                             class_array.array_capacity + "];\n";
          } else {
            h_file_output += "  " + member_var.variable_type + " " +
                             member_var.token + ";\n";
          }
        }
        h_file_output += "} " + class_array.class_name + ";\n\n";
      }
    }

    // output functions
    // go through every instantiated func for this compiled file and compile
    // it into h and c files.
    for (auto &ct_func : instantiated_functions) {
      if (ct_func.file_name == compiled_file) {
        // skip c library funcs as they are defined in a library
        // (SDL_RenderCopy for example).
        if (ct_func.is_c_library_func) {
          continue;
        }
        // if its a c func block just paste in the c func str
        if (ct_func.is_c_func) {
          h_file_output += ct_func.h_func_str + ";\n";
          c_file_output += ct_func.c_func_str + "\n\n";
          continue;
        }
        auto template_function = function_dict.at(ct_func.function_name);
        auto func_signature = ct_func.return_type.variable_type + " " +
                              ct_func.compiled_function_name + "(";
        auto h_func_signature = string("");
        // if the return type is a struct and its a pointer and it is defined
        // in a differnet file then add a struct before its type.
        if (!is_primitive_type(ct_func.return_type.variable_type) &&
            is_pointer(ct_func.return_type.variable_type)) {
          // if the struct is defined in this file then no need for
          // struct MyStruct*, can just do MyStruct*.
          auto class_name = ct_func.return_type.variable_type;
          class_name.pop_back();

          // add struct before return type
          if (class_dict[class_name].file_name != compiled_file) {
            h_func_signature += "struct ";
          }
        }
        // add return type to h_func_signature
        h_func_signature += func_signature;

        // the first param to every non c func and non c library func is
        // the stacktrace if in debug. Except for main as it has no params.
        if (is_debug && ct_func.function_name != "main") {
          h_func_signature +=
              "struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, "
              "int "
              "line_number_of_call";
          func_signature +=
              "CT_StackTrace* ct_stacktrace, int func_idx_of_call, int "
              "line_number_of_call";
          if (ct_func.params.size() > 0) {
            h_func_signature += ", ";
            func_signature += ", ";
          }
        }
        for (int i = 0; i < ct_func.params.size(); i++) {
          // need the fuction template's param name, not the name of the param
          // passed in making a copy so as not to modify the template functin.
          auto template_param = template_function.params.at(i);
          auto &param = ct_func.params.at(i);
          func_signature += param.variable_type + " " + template_param.token;
          if (!is_primitive_type(param.variable_type) &&
              is_pointer(param.variable_type)) {
            // if the struct is defined in this file then no need for
            // struct MyStruct*, can just do MyStruct*.
            auto class_name = param.variable_type;
            class_name.pop_back();

            // if the pointer is not a primitive passed as a pointer
            // then struct delcare it in the h func signature.
            if (!is_primitive_type(class_name)) {
              if (class_dict[class_name].file_name != compiled_file) {
                h_func_signature += "struct ";
              }
            }
          }
          h_func_signature += param.variable_type + " " + template_param.token;
          if (i != ct_func.params.size() - 1) {
            func_signature += ", ";
            h_func_signature += ", ";
          }
        }
        func_signature += ")";
        h_func_signature += ")";
        if (ct_func.function_name != "main") {
          h_file_output += h_func_signature + ";\n";
        }
        c_file_output += func_signature + " {\n";
        // create stacktrace if in main and in debug
        if (ct_func.function_name == "main" && is_debug) {
          add_n_leading_spaces(c_file_output, 4);
          c_file_output +=
              "CT_StackTrace* ct_stacktrace = (CT_StackTrace*) "
              "malloc(sizeof(CT_StackTrace));\n";
          add_n_leading_spaces(c_file_output, 4);
          c_file_output += "ct_stacktrace_init(ct_stacktrace);\n";
          // add all functions to the stacktrace so that it can reference them
          // later when it prints out the stacktrace.
          for (auto &f : instantiated_functions) {
            if (f.is_c_func || f.is_c_library_func) {
              continue;
            }
            // don't add the same function name twice to the stacktrace function
            // array.
            if (ct_stacktrace_function_index_dict.find(
                    f.stacktrace_pretty_func_name) !=
                ct_stacktrace_function_index_dict.end()) {
              continue;
            }
            ct_stacktrace_function_index_dict[f.stacktrace_pretty_func_name] =
                ct_stacktrace_function_index_dict.size();
            add_n_leading_spaces(c_file_output, 4);
            c_file_output +=
                "ct_stacktrace_add_function(ct_stacktrace, "
                "\"" +
                f.file_name + "\", " + "\"" + f.stacktrace_pretty_func_name +
                "\");\n";
          }
        }
        // output all local vars (c89 style)
        auto num_local_vars = 0;
        for (auto &entry : ct_func.local_var_type_dict) {
          // member vars are in the local var type dict for printing, so that
          // the types of what is printing is known. This stops them from
          // being declared.
          if (entry.first.find(".") != string::npos) {
            continue;
          }
          // if the variable is a func param don't declare it.
          auto is_func_param = false;
          for (auto &param : ct_func.params) {
            if (param.token == entry.first) {
              is_func_param = true;
              break;
            }
          }
          if (!is_func_param) {
            if (entry.first == "NULL") {
              continue;
            }
            num_local_vars += 1;
            // declare and initialize variable
            c_file_output += "    " + entry.second + " " + entry.first + " = ";
            if (is_pointer(entry.second)) {
              c_file_output += "NULL;\n";
            } else if (is_number(entry.second)) {
              if (entry.second == "double") {
                c_file_output += "0.0;\n";
              } else {
                c_file_output += "0;\n";
              }
            } else if (entry.second == "bool") {
              c_file_output += "false;\n";
            } else if (is_class_type(entry.second)) {
              c_file_output += "{0};\n";
            } else if (is_enum(entry.second)) {
              // initialize enum values to the 0th entry in the enum
              // by casting 0 to the enum type.
              c_file_output += "(" + entry.second + ") 0;\n";
            } else {
              printf(
                  "CTCompiler::output_c_files. C89 Style initialization type "
                  "not handled.\nVariable name: '%s'\nType: '%s'.\n",
                  entry.first.c_str(), entry.second.c_str());
              abort();
            }
          }
        }
        if (num_local_vars > 0) {
          c_file_output += "\n";
        }
        // push to stack trace after local vars if in debug
        if (is_debug) {
          add_n_leading_spaces(c_file_output, 4);
          string calling_func_idx = "0";
          string call_line_number = "0";
          if (ct_func.function_name != "main") {
            calling_func_idx = "func_idx_of_call";
            call_line_number = "line_number_of_call";
          }
          /* c_file_output += "char* ct_stacktrace_file_name = \"" +
                            ct_func.file_name + "\";\n";
           c_file_output += "char* ct_stacktrace_function_name = \"" +
                            ct_func.function_name + "\";\n";*/
          if (ct_stacktrace_function_index_dict.find(
                  ct_func.stacktrace_pretty_func_name) ==
              ct_stacktrace_function_index_dict.end()) {
            printf(
                "CTCompiler::output_c_files. function '%s' "
                "is not in the stacktrace dict.\n",
                ct_func.function_name.c_str());
            abort();
          }
          if (ct_func.function_name != "main") {
            c_file_output += "ct_stacktrace_push(ct_stacktrace, " +
                             calling_func_idx + ", " + call_line_number +
                             ");\n";
          }
        }
        auto prev_indent = 0;
        auto local_vars = vector<CTCell>();
        for (int i = 1; i < ct_func.cells.size(); i++) {
          auto &cell = ct_func.cells.at(i);
          if (cell.indent < prev_indent) {
            auto indent_diff = (prev_indent - cell.indent) / 4;
            for (int ind = 0; ind < indent_diff; ind++) {
              add_n_leading_spaces(c_file_output, (indent_diff - ind - 1) * 4);
              c_file_output += "}\n";
            }
          }
          auto indent = cell.indent;
          add_n_leading_spaces(c_file_output, indent);
          auto is_semicolon_needed = true;
          if (is_debug) {
            output_bounds_checking(ct_func, local_vars, cell);
            // output_null_checking_for_non_params(ct_func, local_vars, cell);
          }
          output_c_from_cell(ct_func, local_vars, cell, is_semicolon_needed);
          if (is_semicolon_needed && !(cell.list.at(0).token == "if" ||
                                       cell.list.at(0).token == "elif" ||
                                       cell.list.at(0).token == "else" ||
                                       cell.list.at(0).token == "for" ||
                                       cell.list.at(0).token == "forrev" ||
                                       cell.list.at(0).token == "while" ||
                                       cell.list.at(0).token == "foreach" ||
                                       cell.list.at(0).token == "map")) {
            c_file_output += ";\n";
          }
          // this removes the leading spaces added above. is_semicolon_needed
          // is only set to false for struct initialization, which occurs
          // above so is redudant in "=" calls, so nothing happens. Change
          // later if its used in another way.
          if (!is_semicolon_needed) {
            remove_trailing_spaces_only(c_file_output);
          }
          // indent diff check
          if (i < ct_func.cells.size() - 1) {
            if (!(cell.list.at(0).token == "foreach" ||
                  cell.list.at(0).token == "map")) {
              auto next_line_indent = ct_func.cells.at(i + 1).indent;
              if (next_line_indent > indent) {
                // c_file_output += "\n";
                // add_n_leading_spaces(c_file_output, indent);
                c_file_output += " {\n";
              }
            }
          }
          // function end
          else if (i == ct_func.cells.size() - 1) {
            if (ct_func.function_name == "main") {
              if (is_debug) {
                add_n_leading_spaces(c_file_output, indent);
                c_file_output += "free(ct_stacktrace);\n";
              }
              add_n_leading_spaces(c_file_output, indent);
              c_file_output += "return 0;\n";
            }
            auto indent_diff = cell.indent / 4;
            for (int ind = 0; ind < indent_diff; ind++) {
              // if in debug and the final line is not a return line add it on
              // the last line before the function ends.
              if (is_debug && ct_func.function_name != "main" &&
                  i == ct_func.cells.size() - 1 && cell.list.size() > 0 &&
                  cell.list.at(0).token != "return" && ind == indent_diff - 1) {
                add_n_leading_spaces(c_file_output, 4);
                c_file_output += "ct_stacktrace_pop(ct_stacktrace);\n";
              }
              add_n_leading_spaces(c_file_output, (indent_diff - ind - 1) * 4);
              c_file_output += "}\n";
            }
            c_file_output += "\n";
          }
          prev_indent = cell.indent;
        }
      }
    }

    // include guard end
    h_file_output += "\n#endif // GAME_" + to_uppercase(compiled_file) + "\n";

    // write files
    auto h_file_path = h_files_base_directory + compiled_file + ".h";
    auto c_file_path = c_files_base_directory + compiled_file + ".c";
    auto executable_file_name = string("game_main");

    // only output diffs if necessary to Makefile doesn't keep rebuilding. It
    // seems to always rebuild if the file changes on rewrite.
    // output new h file
    // if necessary executable file has no h file
    if (compiled_file != executable_file_name) {
      std::ifstream h_t(h_file_path);
      std::string current_h_file_content((std::istreambuf_iterator<char>(h_t)),
                                         std::istreambuf_iterator<char>());
      if (h_file_output != current_h_file_content) {
        printf("h file: '%s' has changed, ouputting new h file.\n",
               h_file_path.c_str());
        ofstream h_file(h_file_path.c_str());
        h_file << h_file_output;
      }
    }

    // ouptut new c file if necessary
    std::ifstream c_t(c_file_path);
    std::string current_c_file_content((std::istreambuf_iterator<char>(c_t)),
                                       std::istreambuf_iterator<char>());

    if (c_file_output != current_c_file_content) {
      printf("c file: '%s' has changed, ouputting new c file.\n",
             c_file_path.c_str());
      ofstream c_file(c_file_path.c_str());
      c_file << c_file_output;
    }
  }
}

bool CTCompiler::local_var_exists_in_c_output(vector<string> &local_vars,
                                              string &var) {
  for (auto &v : local_vars) {
    if (v == var) {
      return true;
    }
  }
  return false;
}

void CTCompiler::add_n_leading_spaces(string &s, int leading_spaces) {
  for (int i = 0; i < leading_spaces; i++) {
    s += " ";
  }
}

// do this before calling output_c_from_cell, as it will check everything in
// the line for an "value_at" and do bounds checking.
void CTCompiler::output_bounds_checking(CTFunction &ct_func,
                                        vector<CTCell> &local_vars,
                                        CTCell &cell) {
  // these functions modify array size and thus
  // can't be bounds checked automatically.
  if (ct_func.function_name == "push" ||
      ct_func.function_name == "push_value" ||
      ct_func.function_name == "clear" || ct_func.function_name == "next" ||
      ct_func.function_name == "next_handle" ||
      ct_func.function_name == "remove_at") {
    return;
  }
  if (cell.cell_type == CTCellType::List) {
    auto first_cell = cell.list.at(0);
    // only bounds checking array access. Foreach and map are not bounds
    // checked because their iterators are always accessing in bounds indexes.
    if (first_cell.token == "value_at" || first_cell.token == "at") {
      auto array_var = cell.list.at(1);
      auto arr_idx = cell.list.at(2);
      auto arr_token = array_var.token;
      replaceAll(arr_token, ".arr", ".size");
      array_var.token = arr_token;
      auto is_arr_a_ptr = false;
      if (ct_func.local_var_type_dict.find(array_var.token) !=
          ct_func.local_var_type_dict.end()) {
        auto arr_v = ct_func.local_var_type_dict.at(array_var.token);
        is_arr_a_ptr = is_pointer(arr_v);
      }
      if (array_var.cell_type == CTCellType::List) {
        printf(
            "CTCompiler::output_bounds_checking. Bounds checking requires "
            "the "
            "array to be a symbol, not a function call.\n");
        abort();
      }
      if (arr_idx.cell_type == CTCellType::List) {
        printf(
            "CTCompiler::output_bounds_checking. Bounds checking requires "
            "the "
            "array index to be a symbol, not a function call.\n");
        abort();
      }
      auto semicolon_needed = false;
      c_file_output += "if (";
      output_c_from_cell(ct_func, local_vars, arr_idx, semicolon_needed);
      c_file_output += " < 0 || ";
      output_c_from_cell(ct_func, local_vars, arr_idx, semicolon_needed);
      c_file_output += " > ";
      output_c_from_cell(ct_func, local_vars, array_var, semicolon_needed);
      c_file_output += " - 1) {\n";
      add_n_leading_spaces(c_file_output, cell.indent + 4);
      c_file_output += "printf(\"Out of bounds error: idx: %d size: %d.\\n\", ";
      output_c_from_cell(ct_func, local_vars, arr_idx, semicolon_needed);
      c_file_output += ", ";
      output_c_from_cell(ct_func, local_vars, array_var, semicolon_needed);
      c_file_output += ");\n";
      add_n_leading_spaces(c_file_output, cell.indent + 4);
      c_file_output += "ct_stacktrace_push(ct_stacktrace, " +
                       to_string(ct_stacktrace_function_index_dict.at(
                           ct_func.stacktrace_pretty_func_name)) +
                       ", " + to_string(cell.line_number) + ");\n";
      add_n_leading_spaces(c_file_output, cell.indent + 4);
      c_file_output += "ct_stacktrace_print(ct_stacktrace);\n";
      add_n_leading_spaces(c_file_output, cell.indent + 4);
      c_file_output += "exit(1);\n";
      add_n_leading_spaces(c_file_output, cell.indent);
      c_file_output += "}\n ";
      add_n_leading_spaces(c_file_output, cell.indent - 1);
    } else {
      for (int i = 1; i < cell.list.size(); i++) {
        auto &param_cell = cell.list.at(i);
        output_bounds_checking(ct_func, local_vars, param_cell);
      }
    }
  } else {
  }
}

// do this before calling output_c_from_cell, as it will check everything in
// the line looking for member access in structs that are pointers to see if
// they are NULL. Params are basically references and almost always don't have
// NULL values. Can check them later if they become a problem though.
void CTCompiler::output_null_checking_for_non_params(CTFunction &ct_func,
                                                     vector<CTCell> &local_vars,
                                                     CTCell &cell) {
  if (cell.cell_type == CTCellType::List) {
    for (int i = 1; i < cell.list.size(); i++) {
      if (cell.list.at(i).cell_type != CTCellType::Symbol) {
        continue;
      }
      auto param_cell = cell.list.at(i);
      output_null_checking_for_non_params(ct_func, local_vars, param_cell);
    }
  } else {
    if (cell.cell_type != CTCellType::Symbol) {
      return;
    }
    if (is_enum(cell.token)) {
      return;
    }
    auto contains_dot = cell.token.find('.') != string::npos;
    if (contains_dot) {
      auto split = string_split(cell.token, '.');
      if (split.size() == 0) {
        return;
      }
      if (split.size() == 0) {
        printf("'=', split size is 0.\n");
        print_eval_cell_info(ct_func, cell);
        abort();
      }
      auto local_var_cell = cell;
      local_var_cell.token = split.at(0);
      if (ct_func.local_var_type_dict.find(local_var_cell.token) ==
          ct_func.local_var_type_dict.end()) {
        printf(
            "CTCompiler::output_null_checking_for_non_params. Local var is not "
            "in local var dict. %s\n",
            local_var_cell.token.c_str());
        abort();
      }
      auto local_var_variable_type =
          ct_func.local_var_type_dict.at(local_var_cell.token);
      auto rebuilt_string = split.at(0);
      if (is_pointer(local_var_variable_type)) {
        rebuilt_string += "->";
      } else {
        rebuilt_string += ".";
      }
      if (is_primitive_type(local_var_variable_type)) {
        return;
      }
      auto ct_class = get_class(local_var_variable_type);
      for (int i = 1; i < split.size(); i++) {
        auto &s = split.at(i);
        auto member_var = get_member_var(ct_func, cell, ct_class, s);
        if (i == split.size() - 1) {
          cell = member_var;
        } else if (!is_primitive_type(member_var)) {
          ct_class = get_class(member_var.variable_type);
          rebuilt_string += member_var.token;
          auto is_ptr = is_pointer(member_var.variable_type);
          if (is_ptr) {
            printf("is ptr %d %s %s\n", is_ptr, rebuilt_string.c_str(),
                   ct_func.file_name.c_str());
            c_file_output += "if (" + rebuilt_string + " == NULL) {\n";
            add_n_leading_spaces(c_file_output, cell.indent + 4);
            c_file_output += "printf(\"Variable is null error.\\n\");\n";
            add_n_leading_spaces(c_file_output, cell.indent + 4);
            c_file_output += "ct_stacktrace_push(ct_stacktrace, " +
                             to_string(ct_stacktrace_function_index_dict.at(
                                 ct_func.stacktrace_pretty_func_name)) +
                             ", " + to_string(cell.line_number) + ");\n";
            add_n_leading_spaces(c_file_output, cell.indent + 4);
            c_file_output += "ct_stacktrace_print(ct_stacktrace);\n";
            add_n_leading_spaces(c_file_output, cell.indent + 4);
            c_file_output += "exit(1);\n";
            add_n_leading_spaces(c_file_output, cell.indent);
            c_file_output += "}\n ";
            add_n_leading_spaces(c_file_output, cell.indent - 1);
          }
          rebuilt_string += is_ptr ? "->" : ".";
        } else if (is_primitive_type(member_var) && i != split.size() - 1) {
          printf(
              "CTCompiler::output_null_checking_for_non_params. variable '%s', "
              "non-final "
              "primitive '%s' is of type '%s', which is not a class. dot "
              "syntax reached a non-final "
              "member that was a primitive. Primitives must be the final "
              "member.\n",
              cell.token.c_str(), s.c_str(), member_var.variable_type.c_str());
          print_eval_cell_info(ct_func, cell);
          abort();
        } else {
          printf(
              "CTCompiler::output_null_checking_for_non_params. dot syntax "
              "reached "
              "unexpected "
              "branch.\n");
          print_eval_cell_info(ct_func, cell);
          abort();
        }
      }
    }
  }
}

void CTCompiler::output_c_from_cell(CTFunction &ct_func,
                                    vector<CTCell> &local_vars, CTCell &cell,
                                    bool &is_semicolon_needed) {
  if (cell.cell_type == CTCellType::List) {
    auto &first_cell = cell.list.at(0);
    if (first_cell.token == "defun") {
      return;
    } else if (first_cell.token == "for") {
      auto loop_var = cell.list.at(1);
      auto loop_range_list = cell.list.at(2);
      auto is_rev_loop = cell.list.at(2).list.at(0).token == "rev_range";
      auto comparison_string = is_rev_loop ? " >= " : " < ";
      auto comparison_operator = is_rev_loop ? " -= " : " += ";
      if (loop_range_list.list.size() == 4) {
        auto loop_start = loop_range_list.list.at(1);
        auto loop_end = loop_range_list.list.at(2);
        auto loop_step = loop_range_list.list.at(3);
        c_file_output += "for (" + loop_var.token + " = ";
        output_c_from_cell(ct_func, local_vars, loop_start,
                           is_semicolon_needed);
        c_file_output += "; " + loop_var.token + comparison_string;
        output_c_from_cell(ct_func, local_vars, loop_end, is_semicolon_needed);
        c_file_output += "; " + loop_var.token + comparison_operator;
        output_c_from_cell(ct_func, local_vars, loop_step, is_semicolon_needed);
        c_file_output += ")";
      } else if (loop_range_list.list.size() == 3) {
        auto loop_start = loop_range_list.list.at(1);
        auto loop_end = loop_range_list.list.at(2);
        auto loop_step = "1";
        c_file_output += "for (" + loop_var.token + " = ";
        output_c_from_cell(ct_func, local_vars, loop_start,
                           is_semicolon_needed);
        c_file_output += "; " + loop_var.token + comparison_string;
        output_c_from_cell(ct_func, local_vars, loop_end, is_semicolon_needed);
        c_file_output += "; " + loop_var.token + comparison_operator;
        c_file_output += loop_step;
        c_file_output += ")";
      } else if (loop_range_list.list.size() == 2) {
        if (is_rev_loop) {
          auto loop_start = loop_range_list.list.at(1);
          auto loop_end = "0";
          auto loop_step = "1";
          c_file_output += "for (" + loop_var.token + " = ";
          output_c_from_cell(ct_func, local_vars, loop_start,
                             is_semicolon_needed);
          c_file_output += "; " + loop_var.token + comparison_string + loop_end;
          c_file_output += "; " + loop_var.token + comparison_operator;
          c_file_output += loop_step;
          c_file_output += ")";
        } else {
          auto loop_start = "0";
          auto loop_end = loop_range_list.list.at(1);
          auto loop_step = "1";
          c_file_output += "for (" + loop_var.token + " = ";
          c_file_output += loop_start;
          c_file_output += "; " + loop_var.token + comparison_string;
          output_c_from_cell(ct_func, local_vars, loop_end,
                             is_semicolon_needed);
          c_file_output += "; " + loop_var.token + comparison_operator;
          c_file_output += loop_step;
          c_file_output += ")";
        }
      }
      return;
    } else if (first_cell.token == "while") {
      c_file_output += "while (";
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += ")";
      return;
    } else if (first_cell.token == "cast") {
      auto var_type = cell.list.at(2).token;
      replaceAll(var_type, "\"", "");
      c_file_output += "(" + var_type + ")(";
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += ")";
      return;
    } else if (first_cell.token == "==") {
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += " == ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == "!=") {
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += " != ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == "foreach") {
      auto element_var = cell.list.at(1).token;
      auto array_var = cell.list.at(2);
      auto element_var_type = ct_func.local_var_type_dict.at(element_var);
      // if the array is passed in as a param, its .size and .arr need to be
      // ->size and ->arr, this checks for that. Theres should never be a
      // pointer to an arr stored in a struct so that doesn't need to be
      // handled.
      auto is_arr_a_ptr = false;
      if (ct_func.local_var_type_dict.find(array_var.token) !=
          ct_func.local_var_type_dict.end()) {
        auto arr_v = ct_func.local_var_type_dict.at(array_var.token);
        is_arr_a_ptr = is_pointer(arr_v);
      }
      c_file_output += "for (i = 0; i < ";
      output_c_from_cell(ct_func, local_vars, array_var, is_semicolon_needed);
      c_file_output += is_arr_a_ptr ? "->" : ".";
      c_file_output += "size";
      c_file_output += "; i++) {\n ";
      add_n_leading_spaces(c_file_output, cell.indent + 3);
      c_file_output += element_var + " = &";
      output_c_from_cell(ct_func, local_vars, array_var, is_semicolon_needed);
      c_file_output += is_arr_a_ptr ? "->" : ".";
      c_file_output += "arr[i];\n";
      return;
    } else if (first_cell.token == "map") {
      auto loop_var = cell.list.at(1).token;
      auto element_var = cell.list.at(2).token;
      auto array_var = cell.list.at(3);
      auto element_var_type = ct_func.local_var_type_dict.at(element_var);
      // if the array is passed in as a param, its .size and .arr need to be
      // ->size and ->arr, this checks for that. Theres should never be a
      // pointer to an arr stored in a struct so that doesn't need to be
      // handled.
      auto is_arr_a_ptr = false;
      if (ct_func.local_var_type_dict.find(array_var.token) !=
          ct_func.local_var_type_dict.end()) {
        auto arr_v = ct_func.local_var_type_dict.at(array_var.token);
        is_arr_a_ptr = is_pointer(arr_v);
      }
      c_file_output += "for (" + loop_var + " = 0; " + loop_var + " < ";
      output_c_from_cell(ct_func, local_vars, array_var, is_semicolon_needed);
      c_file_output += is_arr_a_ptr ? "->" : ".";
      c_file_output += "size";
      c_file_output += "; " + loop_var + "++) {\n ";
      add_n_leading_spaces(c_file_output, cell.indent + 3);
      c_file_output += element_var + " = &";
      output_c_from_cell(ct_func, local_vars, array_var, is_semicolon_needed);
      c_file_output += is_arr_a_ptr ? "->" : ".";
      c_file_output += "arr[" + loop_var + "];\n";
      return;
    } else if (first_cell.token == "array_get_buffer") {
      auto variable_type1 =
          ct_func.local_var_type_dict.at(cell.list.at(1).token);
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      if (is_pointer(variable_type1)) {
        c_file_output += "->arr";
      } else {
        c_file_output += ".arr";
      }
      return;
    } else if (first_cell.token == "last_enum_int") {
      auto enum_literal_cell = cell.list.at(1);
      auto num_enum_values = enum_name_dict[enum_literal_cell.token].size();
      c_file_output += to_string(num_enum_values);
      return;
    } else if (first_cell.token == "sizeof") {
      auto type_cell = cell.list.at(1).list.at(0);
      c_file_output += "sizeof(" + type_cell.token + ")";
      return;
    } else if (first_cell.token == "malloc") {
      auto type_cell = cell.list.at(1).list.at(0);
      auto size_cell = cell.list.at(2);
      c_file_output += "(" + type_cell.token + "*)" + "malloc(sizeof(" +
                       type_cell.token + ") * " + size_cell.token + ")";
      return;
    } else if (first_cell.token == "free") {
      c_file_output += "free(" + cell.list.at(1).token + ")";
      return;
    } else if (first_cell.token == "memset") {
      c_file_output += "memset(";
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += ", ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      c_file_output += ", sizeof(";
      auto variable_tok = cell.list.at(1).token;
      // is an addr, the compiler forces function calls in memset's first param
      // to only be addr(value).
      if (cell.list.at(1).cell_type == CTCellType::List) {
        variable_tok = cell.list.at(1).list.at(1).token;
      }
      // printf("memset tok %s\n", variable_tok.c_str());
      auto variable_type_of_ptr = ct_func.local_var_type_dict.at(variable_tok);
      auto type_without_ptr = remove_ptr_substr_if_needed(variable_type_of_ptr);
      c_file_output += type_without_ptr;
      c_file_output += ") * ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(3),
                         is_semicolon_needed);
      c_file_output += ")";
      return;
    } else if (first_cell.token == "sprintf") {
      auto buf_variable_type =
          ct_func.local_var_type_dict.at(cell.list.at(1).token);
      auto buf_is_arr_pointer = is_pointer(buf_variable_type);
      c_file_output += "snprintf(";
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += buf_is_arr_pointer ? "->arr" : ".arr";
      c_file_output += ", ";
      c_file_output += "(size_t) " + get_array_capacity(buf_variable_type);
      c_file_output += ", ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      c_file_output += ", ";
      for (int i = 3; i < cell.list.size(); i++) {
        output_c_from_cell(ct_func, local_vars, cell.list.at(i),
                           is_semicolon_needed);
        if (i != cell.list.size() - 1) {
          c_file_output += ", ";
        }
      }
      c_file_output += ");\n";
      add_n_leading_spaces(c_file_output, cell.indent);
      // set the size of the arr for convenience to the new formatted string.
      // if this is not done here it will be forgotten most definitely.
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += buf_is_arr_pointer ? "->size" : ".size";
      c_file_output += " = ";
      c_file_output += "strlen(";
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += buf_is_arr_pointer ? "->arr" : ".arr";
      c_file_output += ")";
      return;
    } else if (first_cell.token == "continue") {
      c_file_output += "continue";
      return;
    } else if (first_cell.token == "break") {
      c_file_output += "break";
      return;
    } else if (first_cell.token == "not") {
      c_file_output += "!(";
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += ")";
      return;
    } else if (first_cell.token == "forrev") {
      auto loop_var = cell.list.at(1);
      auto loop_start = cell.list.at(2);
      auto loop_end = cell.list.at(3);
      c_file_output += "for (int " + loop_var.token + " = ";
      output_c_from_cell(ct_func, local_vars, loop_start, is_semicolon_needed);
      c_file_output += "; " + loop_var.token + " > ";
      output_c_from_cell(ct_func, local_vars, loop_end, is_semicolon_needed);
      c_file_output += "; " + loop_var.token + "--)";
      return;
    } else if (first_cell.token == "return") {
      // if is debug add a stacktrace pop before returning.
      if (is_debug) {
        add_n_leading_spaces(c_file_output, cell.indent);
        c_file_output += "ct_stacktrace_pop(ct_stacktrace);\n";
      }
      if (cell.list.size() == 1) {
        c_file_output += "return";
      } else {
        c_file_output += "return ";
        output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                           is_semicolon_needed);
      }
      return;
    } else if (first_cell.token == "make_array") {
      return;
    } else if (first_cell.token == "array_capacity") {
      auto variable_type = ct_func.local_var_type_dict[cell.list.at(1).token];
      auto capacity = get_array_capacity(variable_type);
      c_file_output += capacity;
      return;
    } else if (first_cell.token == "negate") {
      c_file_output += "-";
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == "value_at") {
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += "[";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      c_file_output += "]";
      return;
    } else if (first_cell.token == "at") {
      c_file_output += "&";
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += "[";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      c_file_output += "]";
      return;
    } else if (first_cell.token == "if") {
      c_file_output += "if (";
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += ")";
      return;
    } else if (first_cell.token == "elif") {
      c_file_output += "else if (";
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += ")";
      return;
    } else if (first_cell.token == "else") {
      c_file_output += "else";
      return;
    } else if (first_cell.token == "exit") {
      // print stacktrace if in debug
      if (is_debug) {
        c_file_output += "ct_stacktrace_push(ct_stacktrace, " +
                         to_string(ct_stacktrace_function_index_dict.at(
                             ct_func.stacktrace_pretty_func_name)) +
                         ", " + to_string(cell.line_number) + ");\n";
        add_n_leading_spaces(c_file_output, cell.indent);
        c_file_output += "ct_stacktrace_print(ct_stacktrace);\n";
      }
      add_n_leading_spaces(c_file_output, cell.indent);
      c_file_output += "exit(";
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += ")";
      return;
    } else if (first_cell.token == ">") {
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += " > ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == "<") {
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += " < ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == ">=") {
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += " >= ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == "<=") {
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += " <= ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == "&" || first_cell.token == "addr") {
      c_file_output += "&";
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == "and") {
      c_file_output += "(";
      for (int i = 1; i < cell.list.size(); i++) {
        output_c_from_cell(ct_func, local_vars, cell.list.at(i),
                           is_semicolon_needed);
        if (i != cell.list.size() - 1) {
          c_file_output += " && ";
        }
      }
      c_file_output += ")";
      return;
    } else if (first_cell.token == "or") {
      c_file_output += "(";
      for (int i = 1; i < cell.list.size(); i++) {
        output_c_from_cell(ct_func, local_vars, cell.list.at(i),
                           is_semicolon_needed);
        if (i != cell.list.size() - 1) {
          c_file_output += " || ";
        }
      }
      c_file_output += ")";
      return;
    } else if (first_cell.token == "+") {
      c_file_output += "(";
      for (int i = 1; i < cell.list.size(); i++) {
        output_c_from_cell(ct_func, local_vars, cell.list.at(i),
                           is_semicolon_needed);
        if (i != cell.list.size() - 1) {
          c_file_output += " + ";
        }
      }
      c_file_output += ")";
      return;
    } else if (first_cell.token == "-") {
      if (cell.list.size() == 2) {
        c_file_output += "-";
        output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                           is_semicolon_needed);
      } else {
        c_file_output += "(";
        for (int i = 1; i < cell.list.size(); i++) {
          output_c_from_cell(ct_func, local_vars, cell.list.at(i),
                             is_semicolon_needed);
          if (i != cell.list.size() - 1) {
            c_file_output += " - ";
          }
        }
        c_file_output += ")";
      }
      return;
    } else if (first_cell.token == "*" || first_cell.token == "deref") {
      // deref
      if (cell.list.size() == 2) {
        c_file_output += "*";
        output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                           is_semicolon_needed);
      }
      // mul
      else {
        c_file_output += "(";
        for (int i = 1; i < cell.list.size(); i++) {
          output_c_from_cell(ct_func, local_vars, cell.list.at(i),
                             is_semicolon_needed);
          if (i != cell.list.size() - 1) {
            c_file_output += " * ";
          }
        }
        c_file_output += ")";
      }
      return;
    } else if (first_cell.token == "/") {
      c_file_output += "(";
      for (int i = 1; i < cell.list.size(); i++) {
        output_c_from_cell(ct_func, local_vars, cell.list.at(i),
                           is_semicolon_needed);
        if (i != cell.list.size() - 1) {
          c_file_output += " / ";
        }
      }
      c_file_output += ")";
      return;
    } else if (first_cell.token == "mod") {
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += " % ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == "+=") {
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += " += ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == "-=") {
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += " -= ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == "*=") {
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += " *= ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == "/=") {
      output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                         is_semicolon_needed);
      c_file_output += " /= ";
      output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                         is_semicolon_needed);
      return;
    } else if (first_cell.token == "print") {
      c_file_output += "printf(\"";
      // currently cannot print function calls (CTCellType::List). Will
      // exit in the type checking portion before it gets here.
      for (int i = 1; i < cell.list.size(); i++) {
        auto &param = cell.list.at(i);
        if (param.cell_type == CTCellType::Symbol) {
          auto variable_type = ct_func.local_var_type_dict.at(param.token);
          /*printf("print var %s %s\n", param.token.c_str(),
                 variable_type.c_str());*/
          if (variable_type == "int") {
            c_file_output += "%d";
          } else if (variable_type == "long unsigned int") {
            // pretty much only used for sizeof calls
            c_file_output += "%lu";
          } else if (variable_type == "Uint8" || variable_type == "Uint32" ||
                     variable_type == "Uint64") {
            c_file_output += "%u";
          } else if (variable_type == "bool") {
            c_file_output += "%d";
          } else if (variable_type == "double") {
            c_file_output += "%f";
          } else if (variable_type == "char*") {
            c_file_output += "%s";
          } else if (variable_type == "char") {
            c_file_output += "%c";
          } else {
            c_file_output += "%s";
          }
        } else if (param.cell_type == CTCellType::Int) {
          c_file_output += "%d";
        } else if (param.cell_type == CTCellType::Double) {
          c_file_output += "%f";
        } else if (param.cell_type == CTCellType::CharPointer) {
          c_file_output += "%s";
        } else if (param.cell_type == CTCellType::Char) {
          c_file_output += "%c";
        }
        if (i != cell.list.size() - 1) {
          c_file_output += " ";
        }
      }
      c_file_output += "\\n\", ";
      for (int i = 1; i < cell.list.size(); i++) {
        auto &param = cell.list.at(i);
        if (param.cell_type == CTCellType::Symbol) {
          auto variable_type = ct_func.local_var_type_dict[param.token];
          if (is_class_type(variable_type) || is_enum(variable_type)) {
            c_file_output += "\"" + variable_type + "\"";
          } else {
            output_c_from_cell(ct_func, local_vars, cell.list.at(i),
                               is_semicolon_needed);
          }
        } else {
          output_c_from_cell(ct_func, local_vars, cell.list.at(i),
                             is_semicolon_needed);
        }
        if (i != cell.list.size() - 1) {
          c_file_output += ", ";
        }
      }
      c_file_output += ")";
      return;
    } else if (first_cell.token == "=" || first_cell.token == "set") {
      auto var = cell.list.at(1);
      auto value = cell.list.at(2);
      if (var.cell_type == CTCellType::List) {
        output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                           is_semicolon_needed);
        c_file_output += " = ";
        output_c_from_cell(ct_func, local_vars, cell.list.at(2),
                           is_semicolon_needed);
      } else {
        auto contains_dot = var.token.find('.') != string::npos;
        auto var_already_defined = is_local_var(local_vars, var);
        if (!var_already_defined) {
          local_vars.push_back(var);
        }
        auto var_type_it = ct_func.local_var_type_dict.find(var.token);
        if (var_type_it == ct_func.local_var_type_dict.end()) {
          printf(
              "CTCompiler::output_from_cell. Variable '%s' is not in the "
              "local var dictionary. File %s:%d\n",
              var.token.c_str(), cell.file_name.c_str(), cell.line_number);
          abort();
        }
        auto variable_type = ct_func.local_var_type_dict[var.token];

        // local variable arrays in functions do not need any code for them as
        // they are declared and initialized at the top of function scope. int
        // add(int a, int b) {
        //     Array_int_40 vals = {0};
        //     later on...
        //     vals = ?? // this is unnecessary as it is already declared.
        // so nothing should be outputted in this case.
        if (is_array(variable_type)) {
          // printf("is array %s %s\n", var.token.c_str(),
          // variable_type.c_str());
          // early return, no semicolon is needed as nothing was outputted on
          // this line.
          is_semicolon_needed = false;
          return;
        }

        // if contains dot the var is already defined, don't need to have a
        // type in front of the var declaring it.
        if (contains_dot || var_already_defined) {
          output_c_from_cell(ct_func, local_vars, cell.list.at(1),
                             is_semicolon_needed);
        } else if (!(value.cell_type == CTCellType::List &&
                     is_class_type(value.list.at(0).token))) {
          // variable type is not needed because I am currently doing c89
          // style variable declaration, change back if needed.
          // c_file_output += variable_type + " " + var.token;
          c_file_output += var.token;
        }
        auto is_class = is_class_type(variable_type);
        auto value_is_class_literal = false;
        auto is_array_literal = false;
        if (value.cell_type == CTCellType::List &&
            is_class_type(value.list.at(0).token)) {
          value_is_class_literal = true;
        }
        if (value.cell_type == CTCellType::List && value.list.size() > 0) {
          auto value_first_cell = value.list.at(0);
          is_array_literal = value_first_cell.token == "make_array";
        }
        if (!value_is_class_literal && !is_array_literal) {
          c_file_output += " = ";
          output_c_from_cell(ct_func, local_vars, value, is_semicolon_needed);
        }
        // zero initialize struct, this is nice because it sets the array size
        // to 0. don't have to set it explicitly. Even in nested structs the
        // arrays will be initailized to size 0.
        else {
          is_semicolon_needed = false;
          // c_file_output += " = {0}";
        }

        // always zero out malloc memory
        if (value.list.size() > 0 && value.list.at(0).token == "malloc") {
          c_file_output += ";\n";
          add_n_leading_spaces(c_file_output, cell.indent);
          c_file_output += "memset(" + var.token + ", 0, sizeof(" +
                           value.list.at(1).list.at(0).token + ") * " +
                           value.list.at(2).token + ")";
        }
      }
      return;
    } else {
      // function
      auto function_name = first_cell.token;
      // first_cell is overwritten to be the compiled_function name when
      // the function is instantiated.
      auto &func = get_instantiated_func(function_name);
      c_file_output += func.compiled_function_name + "(";
      // ct_func can't be a c func or c library func at this point but im
      // putting it here anyway as a sanity check.
      if (is_debug && !func.is_c_func && !func.is_c_library_func &&
          !ct_func.is_c_func && !ct_func.is_c_library_func) {
        // add ct_stacktrace param as the first param if in debug
        c_file_output += "ct_stacktrace, " +
                         to_string(ct_stacktrace_function_index_dict.at(
                             ct_func.stacktrace_pretty_func_name)) +
                         ", " + to_string(cell.line_number);
        if (cell.list.size() > 1) {
          c_file_output += ", ";
        }
      }
      // class member function, need to add the 'self' param
      /*if (func.is_member_func) {
        // use original token as the first cell's token has been overwritten
        // to the compiled function name.
        auto split = string_split(first_cell.original_token, '.');
        // need a comma before the self param for the stacktrace if the
        // member func had no params other than self, as above the comma is only
        // added if cell.list.size() > 1, and it won't think there is a param in
        // a self only member func call.
        if (is_debug && cell.list.size() == 1) {
          // c_file_output += ", ";
        }
        // outputting it this way is fairly naive. It assumes that the member
        // function is only invoked from variables, so only something like
        // engine.update(). This will not work for indexed calls like
        // arr[i].update() or for function calls like get_engine().update(). I
        // am not handling those cases yet.
        auto class_instance_name = string("");
        // the class instance is all the tokens except the last one. the last
        // token is the function name. example, game.engine.init()
        for (int t = 0; t < split.size() - 1; t++) {
          class_instance_name += split.at(t);
          if (t != split.size() - 2) {
            class_instance_name += ".";
          }
        }
        // output the class instance cell so that any pointers get '->'.
        auto class_instance_cell =
            CTCell(CTCellType::Symbol, class_instance_name, cell.file_name,
                   cell.line_number, cell.indent);
        output_c_from_cell(ct_func, local_vars, class_instance_cell,
                           is_semicolon_needed);
        if (cell.list.size() > 1) {
          c_file_output += ", ";
        }
      }*/
      for (int i = 1; i < cell.list.size(); i++) {
        auto &param = cell.list.at(i);
        // i - 1 because i starts at at 1 to skip the first cell (function
        // name) so i in the list is actually the func param at i - 1
        auto func_param = func.params.at(i - 1);
        auto variable_type = ct_func.local_var_type_dict[param.token];
        auto func_param_is_ptr =
            func_param.variable_type.find('*') != string::npos;
        auto variable_is_ptr = variable_type.find('*') != string::npos;
        /*printf("%s %s\n", func_param.variable_type.c_str(),
               variable_type.c_str());*/
        // pass by pointer if the func param takes a pointer and the variable
        // is not a pointer.
        if (func_param_is_ptr && !variable_is_ptr) {
          // c_file_output += "&";
        }
        output_c_from_cell(ct_func, local_vars, param, is_semicolon_needed);
        if (i != cell.list.size() - 1) {
          c_file_output += ", ";
        }
      }
      c_file_output += ")";
    }
  } else {
    // need to do arrows for pointers unit->hp
    if (cell.cell_type == CTCellType::Symbol) {
      if (is_enum(cell)) {
        // format enum for c
        auto enum_str_cpy = cell.token;
        replaceAll(enum_str_cpy, ".", "_");
        c_file_output += enum_str_cpy;
      } else {
        auto contains_dot = cell.token.find('.') != string::npos;
        auto dot_str_with_ptrs = string("");
        if (contains_dot) {
          auto dot_split = string_split(cell.token, '.');
          auto class_var = dot_split.at(0);
          auto variable_type = ct_func.local_var_type_dict[class_var];
          auto variable_is_ptr = variable_type.find('*') != string::npos;
          // This should not be handled here. It should be handled in eval
          // function cell. But I can't find where the malformed enum would be
          // there. It seems to reliably error here so I'm handling it here for
          // now. Change later if necessary.
          if (variable_type.size() == 0) {
            printf(
                "CTCompiler::eval_function_cell. Variable type is size 0. "
                "Usually this means an enum value is not yet defined.\nEnum "
                "type: '%s'\nEnum value: '%s' <-- Not yet defined.\nFile name: "
                "'%s'\nLine number: "
                "'%d'\n",
                class_var.c_str(), cell.token.c_str(), cell.file_name.c_str(),
                cell.line_number);
            abort();
          }
          auto ct_class = get_class(variable_type);
          // printf("dot class %s %s\n", class_var.c_str(),
          // variable_type.c_str());
          c_file_output += class_var;
          if (variable_is_ptr) {
            c_file_output += "->";
          } else {
            c_file_output += ".";
          }
          for (int i = 1; i < dot_split.size(); i++) {
            auto &s = dot_split.at(i);
            // before this was a reference but if the member var is an SDL_Rect*
            // it errors. Not sure why. Fix later if this slows things down.
            auto member_var = get_member_var(ct_func, cell, ct_class, s);
            if (is_class_type(member_var.variable_type)) {
              ct_class = get_class(member_var.variable_type);
              auto variable_is_ptr =
                  member_var.variable_type.find('*') != string::npos;
              c_file_output += s;
              if (i != dot_split.size() - 1) {
                if (variable_is_ptr) {
                  c_file_output += "->";
                } else {
                  c_file_output += ".";
                }
              }
            } else {
              c_file_output += s;
              if (i != dot_split.size() - 1) {
                c_file_output += ".";
              }
            }
          }
        } else {
          // if no dot in token output the whole token
          c_file_output += cell.token;
        }
      }
    } else {
      c_file_output += cell.token;
    }
  }
}