#include "py_compiler.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <streambuf>
#include <string>

PYCell::PYCell() {
  is_func = false;
  tok = string("");
  list = vector<PYCell>();
}

PYCell::PYCell(bool _is_func, string _tok, vector<PYCell> _list) {
  is_func = _is_func;
  tok = _tok;
  list = _list;
}

PYFuncArgs::PYFuncArgs() {
  func_name = string("");
  num_args = 0;
  num_parenths = 0;
}

PYFuncArgs::PYFuncArgs(string _func_name) {
  func_name = _func_name;
  num_args = 0;
  num_parenths = 0;
}

PYLine::PYLine() {
  line = string("");
  s_expr = string("");
  line_number = -1;
  indent = -1;
}

PYLine::PYLine(string _line, string _s_expr, vector<string> _tokens,
               string &_file_name, int _line_number, int _indent) {
  line = _line;
  s_expr = _s_expr;
  tokens = _tokens;
  file_name = _file_name;
  line_number = _line_number;
  indent = _indent;
}

PYCompiler::PYCompiler() {
  files_base_directory = string("");
  ct_files_base_directory = string("");
  file_name = string("");
  file_contents = string("");
  line_number = 1;
  current_enum_string = string("");
  file_lines = vector<PYLine>();
  output_stack = vector<PYCell>();
  operator_stack = vector<PYCell>();
  temp_func_args = vector<PYFuncArgs>();
  func_args = vector<PYFuncArgs>();
  enum_values_dict = unordered_map<string, bool>();
  compiled_files = unordered_map<string, bool>();
}

PYCompiler::PYCompiler(string _files_base_directory,
                       string _ct_files_base_directory) {
  files_base_directory = _files_base_directory;
  ct_files_base_directory = _ct_files_base_directory;
  file_name = string("");
  file_contents = string("");
  line_number = 1;
  current_enum_string = string("");
  file_lines = vector<PYLine>();
  output_stack = vector<PYCell>();
  operator_stack = vector<PYCell>();
  temp_func_args = vector<PYFuncArgs>();
  func_args = vector<PYFuncArgs>();
  enum_values_dict = unordered_map<string, bool>();
  compiled_files = unordered_map<string, bool>();
}

void PYCompiler::compile_file(
    string _file_name, unordered_map<string, string> &ct_file_content_dict) {
  // the file has already been compiled, no need to compile it again
  if (compiled_files.find(_file_name) != compiled_files.end()) {
    return;
  }
  /*printf("py - compiling %s.py into a %s.ct.\n", _file_name.c_str(),
         _file_name.c_str());*/
  // add file to compiled files
  compiled_files[_file_name] = true;
  file_name = _file_name;

  ifstream inFile;
  inFile.open(files_base_directory + _file_name + ".py");
  if (!inFile.good()) {
    printf("PYCompiler - file not found. file_name: %s\n",
           (files_base_directory + _file_name + ".py").c_str());
    exit(1);
  }

  // printf("Compiling py file: %s\n", _file_name.c_str());

  // clear previous file data
  file_lines.clear();

  std::string line;
  line_number = 1;
  auto ct_file_output = string("");
  bool parsing_class = false;
  bool parsing_array_class = false;
  bool pasring_enum = false;
  auto parsing_c_func = false;
  auto parsing_c_library_funcs = false;
  auto parsing_weak_imports = false;
  string c_func_str = "<c_func>\n";
  string c_library_funcs_str = "<c_library_funcs>\n";
  int l_parenths = 0;
  int r_parenths = 0;
  auto temp_line = string("");
  while (getline(inFile, line, '\n')) {
    // printf("line %s\n", line.c_str());
    // if the line breaks mid function
    for (auto c : line) {
      if (c == '(') {
        l_parenths += 1;
      } else if (c == ')') {
        r_parenths += 1;
      }
    }
    // temp line always adds line
    temp_line += line;
    // keep going the function isn't over
    if (l_parenths != r_parenths) {
      continue;
    }
    // function is over or the line didnt break mid function
    else {
      // reset parenths values for next line
      l_parenths = 0;
      r_parenths = 0;
      // copy over the temp line into line and clear the temp line
      if (temp_line.size() > 0) {
        line = temp_line;
        temp_line.clear();
      }
    }
    // printf("line %s\n", line.c_str());
    replaceAll(line, "True", "true");
    replaceAll(line, "False", "false");
    replaceAll(line, "None", "NULL");
    if (line == "# weak imports") {
      parsing_weak_imports = true;
      continue;
    } else if (line == "'''<c_func>" && parsing_c_func) {
      printf(
          "PYCompiler::compile_file. Cannot nest <c_func> tags. filename: %s\n",
          file_name.c_str());
      exit(1);
    } else if (line == "</c_func>'''" && !parsing_c_func) {
      printf(
          "PYCompiler::compile_file. Found closing </c_func> tag, but had no "
          "matching <c_func> tag. filename: %s\n",
          file_name.c_str());
      exit(1);
    } else if (line == "'''<c_func>") {
      parsing_c_func = true;
      line_number += 1;
      continue;
    } else if (line == "</c_func>'''") {
      parsing_c_func = false;
      line_number += 1;
      c_func_str += "\n</c_func>";
      file_lines.push_back(PYLine(line, c_func_str, string_split(line, ' '),
                                  file_name, line_number, -1));
      ct_file_output += c_func_str + "\n";
      c_func_str = "<c_func>\n";
      continue;
    } else if (parsing_c_func) {
      c_func_str += line;
      line_number += 1;
      continue;
    } else if (line == "'''<c_library_funcs>" && parsing_c_library_funcs) {
      printf(
          "PYCompiler::compile_file. Cannot nest <c_library_funcs> tags. "
          "filename: %s\n",
          file_name.c_str());
      exit(1);
    } else if (line == "</c_library_funcs>'''" && !parsing_c_library_funcs) {
      printf(
          "PYCompiler::compile_file. Found closing </c_library_funcs> tag, but "
          "had no "
          "matching <c_func> tag. filename: %s\n",
          file_name.c_str());
      exit(1);
    } else if (line == "'''<c_library_funcs>") {
      parsing_c_library_funcs = true;
      line_number += 1;
      continue;
    } else if (line == "</c_library_funcs>'''") {
      parsing_c_library_funcs = false;
      line_number += 1;
      c_library_funcs_str += "\n</c_library_funcs>";
      file_lines.push_back(PYLine(line, c_library_funcs_str,
                                  string_split(line, ' '), file_name,
                                  line_number, -1));
      ct_file_output += c_library_funcs_str + "\n";
      c_library_funcs_str = "<c_library_funcs>\n";
      continue;
    } else if (parsing_c_library_funcs) {
      c_library_funcs_str += line;
      line_number += 1;
      continue;
    }

    auto indent = num_leading_spaces(line);
    // don't compile anything while parsing an array class, it is display only
    // for python intellisense.
    if (parsing_array_class && indent == 0 && line.size() != 0) {
      parsing_array_class = false;
    } else if (parsing_array_class) {
      continue;
    }
    // parsing class lines to be skipped
    if (parsing_class) {
      if (line.find("__init__") != string::npos) {
        continue;
      } else if (line.find("'''") != string::npos) {
        continue;
      }
    }
    if ((parsing_class || pasring_enum) && indent == 0) {
      parsing_class = false;
      pasring_enum = false;
    } else if (parsing_class || pasring_enum) {
      // correctly indent member vars
      indent = 4;
    }
    remove_leading_spaces(line);
    // just in case there were any trailing spaces
    remove_trailing_spaces(line);
    replaceAll(line, "(", " ( ");
    replaceAll(line, ")", " )");
    replaceAll(line, ",", " , ");
    // def needs all colons replaced, don't want to split again to see
    // if the first tok is a def, so I'm doing this instead. kind of hacky.
    if (line.size() >= 4 && line.at(0) == 'd' && line.at(1) == 'e' &&
        line.at(2) == 'f' && line.at(3) == ' ') {
      replaceAll(line, ":", "");
    }
    // remove final colon at line end if it exists
    else if (line.size() > 0 && line.at(line.size() - 1) == ':') {
      line.pop_back();
    }
    // replaces empty lists with a single space, because the replaces above will
    // add two spaces ("(  )" => "( )"). empty param lists need a single space,
    // not two spaces - defun my_func ()
    replaceAll(line, "(  )", "( )");

    /*if (line.find("class") == string::npos &&
        line.find("Array") != string::npos) {
      line = replace_array_classes_with_make_array(line);
    }*/

    // printf("py file line %d %s\n", line_number, line.c_str());
    auto tokens = tokenize_line(line);
    for (auto &t : tokens) {
      // printf("tokenize tok %s\n", t.c_str());
    }
    auto replaced_str = string("");
    replace_arrays_with_make_array(tokens);
    replace_all_negatives(tokens);
    // replace_all_nots(tokens);
    for (auto &t : tokens) {
      replaced_str += t;
      // printf("after replaced tok %s\n", t.c_str());
    }
    // printf("replaced str %s\n", replaced_str.c_str());
    // shunting_yard_s_expr(tokens);
    auto s_expr_str = string("");
    if (line.size() > 0 && tokens.size() > 0) {
      if (line.find("#") != string::npos) {
        auto l = line;
        l.at(0) = ';';
        s_expr_str = l;
      } else if (pasring_enum) {
        s_expr_str = compile_enum_member_var(line, tokens);
      } else if (parsing_class) {
        // printf("parisng class\n");
        s_expr_str = compile_class_member_var(line, tokens);
      } else if (line.find("class") != string::npos &&
                 line.find("Enum") != string::npos) {
        pasring_enum = true;
        s_expr_str = compile_enum(line, tokens);
      } else if (line.find("class") != string::npos &&
                 line.find("Enum") == string::npos) {
        // printf("class line\n");
        // array classes are only for python intellisense, they aren't actually
        // compiled.
        if (line.find("Array") != string::npos) {
          parsing_array_class = true;
        } else {
          parsing_class = true;
          s_expr_str = compile_class(line, tokens);
        }
      } else if (tokens[0] == "def") {
        // printf("def\n");
        s_expr_str = compile_function_def(line);
      } else if (tokens[0] == "if" || tokens[0] == "elif" ||
                 tokens[0] == "else") {
        // printf("cond\n");
        s_expr_str = compile_conditional(line, tokens);
      } else if (tokens[0] == "for") {
        // printf("for\n");
        s_expr_str = compile_for(line, tokens);
      } else if (tokens[0] == "while") {
        // printf("for\n");
        s_expr_str = compile_while(line, tokens);
      } else if (line.find("import") != string::npos) {
        // printf("import\n");
        s_expr_str = compile_import(line, tokens, parsing_weak_imports,
                                    ct_file_content_dict);
      } else if (tokens[0] == "return") {
        // printf("return\n");
        s_expr_str = compile_return(line, tokens);
      } else if (tokens[0] == "continue") {
        s_expr_str = "(continue)";
      } else if (tokens[0] == "break") {
        s_expr_str = "(break)";
      } else {
        // printf("else\n");
        s_expr_str = shunting_yard_s_expr(tokens, line);
      }
      exit_if_parenths_dont_match(s_expr_str);

      // printf("s_expr %s\n", s_expr_str.c_str());
      for (int i = 0; i < indent; i++) {
        s_expr_str.insert(0, " ");
      }
    }
    file_lines.push_back(PYLine(line, s_expr_str, string_split(line, ' '),
                                file_name, line_number, indent));
    ct_file_output += s_expr_str + "\n";
    line_number += 1;
  }
  // push one empty line at the end so that scopes can close
  /*file_lines.push_back(
      CTLine("( )", string_split("( )", ' '), file_name, line_number, 0));*/

  /*
  stringstream strStream;
  strStream << inFile.rdbuf();
  file_contents = strStream.str();
  */

  /*for (auto &l : file_lines) {
    printf("tokens %d - %d - %s\n", l.line_number, l.indent, l.s_expr.c_str());
  }*/

  // write ct file
  /*auto ct_file_path = ct_files_base_directory + file_name + ".ct";
  ofstream ct_file(ct_file_path.c_str());
  ct_file << ct_file_output;*/
  // add file_name and ct_file_output to the ct_file_content_dict instead of
  // writing the ct_file_output to a file.
  ct_file_content_dict[file_name] = ct_file_output;
}

void PYCompiler::replace_arrays_with_make_array(vector<string> &tokens) {
  auto has_array = false;
  for (int i = tokens.size() - 1; i > -1; i--) {
    auto &tok = tokens.at(i);
    // printf("%d %s\n", i, tok.c_str());
    if (tok.find("Array[") != string::npos) {
      has_array = true;
      // printf("array tok %s\n", tok.c_str());
      auto initial_type_split = string_split(tok, '[');
      auto type_split = string_split(initial_type_split.at(1), ']');
      auto &type_str = type_split.at(0);
      if (i + 2 > tokens.size() - 1) {
        printf("replace_arrays_with_make_array. i + 2 > tokens.size() - 1.\n");
        exit(1);
      }
      auto capacity_str = tokens.at(i + 2);
      // erase the tokens that are going to be thrown away.
      tokens.erase(tokens.begin() + (i + 1), tokens.begin() + (i + 4));
      tok = "make_array";
      // push back each token after erasing so that it matches the tokenizer
      // split output.
      tokens.insert(tokens.begin() + (i + 1), ")");
      tokens.insert(tokens.begin() + (i + 1), capacity_str);
      tokens.insert(tokens.begin() + (i + 1), ",");
      tokens.insert(tokens.begin() + (i + 1), type_str);
      tokens.insert(tokens.begin() + (i + 1), "(");
    } else if (tok.find("Array2D[") != string::npos) {
      has_array = true;
      // printf("array tok %s\n", tok.c_str());
      auto initial_type_split = string_split(tok, '[');
      auto type_split = string_split(initial_type_split.at(1), ']');
      auto &type_str = type_split.at(0);
      if (i + 2 > tokens.size() - 1) {
        printf("replace_arrays_with_make_array. i + 2 > tokens.size() - 1.\n");
        exit(1);
      }
      auto inner_capacity_str = tokens.at(i + 2);
      auto capacity_str = tokens.at(i + 4);
      // erase the tokens that are going to be thrown away.
      tokens.erase(tokens.begin() + (i + 1), tokens.begin() + (i + 6));
      tok = "make_array";
      // push back each token after erasing so that it matches the tokenizer
      // split output.
      tokens.insert(tokens.begin() + (i + 1), ")");
      tokens.insert(tokens.begin() + (i + 1), capacity_str);
      tokens.insert(tokens.begin() + (i + 1), ",");
      tokens.insert(tokens.begin() + (i + 1), inner_capacity_str);
      tokens.insert(tokens.begin() + (i + 1), ",");
      tokens.insert(tokens.begin() + (i + 1), type_str);
      tokens.insert(tokens.begin() + (i + 1), "(");
    } else if (tok.find("Array3D[") != string::npos) {
      has_array = true;
      printf("array tok %s\n", tok.c_str());
      auto initial_type_split = string_split(tok, '[');
      auto type_split = string_split(initial_type_split.at(1), ']');
      auto &type_str = type_split.at(0);
      if (i + 2 > tokens.size() - 1) {
        printf("replace_arrays_with_make_array. i + 2 > tokens.size() - 1.\n");
        exit(1);
      }
      auto capacity_str_1 = tokens.at(i + 2);
      auto capacity_str_2 = tokens.at(i + 4);
      auto capacity_str_3 = tokens.at(i + 6);
      // erase the tokens that are going to be thrown away.
      tokens.erase(tokens.begin() + (i + 1), tokens.begin() + (i + 8));
      tok = "make_array";
      // push back each token after erasing so that it matches the tokenizer
      // split output.
      tokens.insert(tokens.begin() + (i + 1), ")");
      tokens.insert(tokens.begin() + (i + 1), capacity_str_3);
      tokens.insert(tokens.begin() + (i + 1), ",");
      tokens.insert(tokens.begin() + (i + 1), capacity_str_2);
      tokens.insert(tokens.begin() + (i + 1), ",");
      tokens.insert(tokens.begin() + (i + 1), capacity_str_1);
      tokens.insert(tokens.begin() + (i + 1), ",");
      tokens.insert(tokens.begin() + (i + 1), type_str);
      tokens.insert(tokens.begin() + (i + 1), "(");
    }
  }

  if (has_array) {
    for (int i = 0; i < tokens.size(); i++) {
      auto &tok = tokens.at(i);
      // printf("%d %s\n", i, tok.c_str());
    }
    //  exit(1);
  }
}

void PYCompiler::set_func_args_for_line(vector<string> &tokens) {
  temp_func_args.clear();
  func_args.clear();

  for (int i = 0; i < tokens.size(); i++) {
    auto &tok = tokens.at(i);
    auto is_func = false;
    if (i <= tokens.size() - 2) {
      if (tokens.at(i + 1) == "(") {
        is_func = true;
      }
    }
    if (is_func) {
      auto args = PYFuncArgs(tok);
      // handles the case where the first param is another function call, need
      // to inc params in that case as the new function will be inserted in the
      // front.
      if (temp_func_args.size() > 0 && temp_func_args.at(0).num_args == 0) {
        temp_func_args.at(0).num_args += 1;
      }
      temp_func_args.insert(temp_func_args.begin(), args);
    }
    if (temp_func_args.size() > 0)
      // initial param, some tok after the first parenth. skip ")" so that
      // func() has 0 params and not 1 param.
      if (temp_func_args.size() > 0 && temp_func_args.at(0).num_parenths > 0 &&
          temp_func_args.at(0).num_args == 0 && tok != ")") {
        temp_func_args.at(0).num_args += 1;
      }
    // additional params
    if (tok == ",") {
      if (temp_func_args.size() > 0) {
        auto &t_args = temp_func_args.at(0);
        temp_func_args.at(0).num_args += 1;
      }
    } else if (tok == "(") {
      if (temp_func_args.size() > 0) {
        temp_func_args.at(0).num_parenths += 1;
      }
    } else if (tok == ")") {
      if (temp_func_args.size() > 0) {
        auto &t_args = temp_func_args.at(0);
        t_args.num_parenths -= 1;
        if (t_args.num_parenths == 0) {
          func_args.push_back(t_args);
          temp_func_args.erase(temp_func_args.begin());
        }
      }
    }
  }

  /*
  for (auto &arg : func_args) {
    printf("arg %s %d %d\n", arg.func_name.c_str(), arg.num_args,
           arg.num_parenths);
  }
  */
}

string PYCompiler::shunting_yard_s_expr(vector<string> &tokens, string &line) {
  if (tokens.size() == 0) {
    printf("shunting yard tokens.size is 0. line '%s'\n", line.c_str());
    exit(1);
    return string("");
  } else if (tokens.size() == 1) {
    return tokens.at(0);
  }
  output_stack.clear();
  operator_stack.clear();

  set_func_args_for_line(tokens);

  for (int i = 0; i < tokens.size(); i++) {
    auto &tok = tokens.at(i);
    remove_leading_spaces(tok);
    remove_trailing_spaces(tok);
    auto next_is_l_parenths = false;
    if (i <= tokens.size() - 2) {
      if (tokens.at(i + 1) == "(") {
        next_is_l_parenths = true;
      }
    }
    // printf("shunting yard %d %s\n", i, tok.c_str());
    if ((tok != "," && tok != "(" && tok != ")" && !isOperator(tok)) &&
        (is_number(tok) || !next_is_l_parenths)) {
      // printf("is numeric\n");
      output_stack.push_back(PYCell(false, tok, vector<PYCell>()));
    } else if (next_is_l_parenths) {
      // printf("is func\n");
      operator_stack.insert(operator_stack.begin(),
                            PYCell(false, tok, vector<PYCell>()));
    } else if (tok == ",") {
      while (operator_stack.size() > 0 && operator_stack.at(0).tok != "(") {
        auto t = operator_stack.at(0);
        operator_stack.erase(operator_stack.begin());
        output_stack.push_back(t);
      }
    } else if (isOperator(tok)) {
      // printf("is operator\n");
      /*for (int i = 0; i < operator_stack.size(); i++) {
        printf("bef operator stack %d %s\n", i,
               operator_stack.at(i).tok.c_str());
      }*/
      auto tok_priority = getPriority(tok);
      while (operator_stack.size() > 0 &&
             getPriority(operator_stack.at(0).tok) >= tok_priority &&
             operator_stack.at(0).tok != "(") {
        auto t = operator_stack.at(0);
        operator_stack.erase(operator_stack.begin());
        output_stack.push_back(t);
      }
      operator_stack.insert(operator_stack.begin(),
                            PYCell(false, tok, vector<PYCell>()));
      /*for (int i = 0; i < operator_stack.size(); i++) {
        printf("af operator stack %d %s\n", i,
               operator_stack.at(i).tok.c_str());
      }*/
      /*sort(begin(operator_stack), end(operator_stack),
           [this](string a, string b) {
             return getPriority(a) < getPriority(b);
           });*/
    } else if (tok == "(") {
      // printf("is l parenths\n");
      operator_stack.insert(operator_stack.begin(),
                            PYCell(false, tok, vector<PYCell>()));
    } else if (tok == ")") {
      // printf("is r parenths\n");
      // printf("right parenths found\n");
      /*for (int i = 0; i < operator_stack.size(); i++) {
        printf("bef operator stack %d %s\n", i,
               operator_stack.at(i).tok.c_str());
      }*/
      while (operator_stack.size() > 0 && operator_stack.at(0).tok != "(") {
        auto t = operator_stack.at(0);
        // printf("while %s\n", t.tok.c_str());
        operator_stack.erase(operator_stack.begin());
        output_stack.push_back(t);
      }
      if (operator_stack.at(0).tok == "(") {
        operator_stack.erase(operator_stack.begin());
      }
    }
  }
  while (operator_stack.size() > 0) {
    auto t = operator_stack.at(0);
    operator_stack.erase(operator_stack.begin());
    output_stack.push_back(t);
  }
  /*
    for (int i = 0; i < output_stack.size(); i++) {
      printf("output stack %d %s\n", i, output_stack.at(i).tok.c_str());
    }
    for (int i = 0; i < operator_stack.size(); i++) {
      printf("operator stack %d %s\n", i, operator_stack.at(i).tok.c_str());
    }
    */
  auto prefix = vector<PYCell>();
  for (int i = 0; i < output_stack.size(); i++) {
    auto &tok = output_stack.at(i);
    auto num_params = -1;
    if (isOperator(tok.tok)) {
      num_params = 2;
    } else {
      for (auto &num_args : func_args) {
        if (num_args.func_name == tok.tok) {
          num_params = num_args.num_args;
        }
      }
    }
    // printf("args %s %d\n", tok.tok.c_str(), num_params);
    // printf("tok %s params %d\n", tok.tok.c_str(), num_params);
    if (num_params == -1) {
      prefix.insert(prefix.begin(), tok);
    } else {
      tok.is_func = true;
      for (int j = 0; j < num_params; j++) {
        if (prefix.size() == 0) {
          printf("file: %s\nline number: %d\nline: %s\n", file_name.c_str(),
                 line_number, line.c_str());
          printf("shunting yard prefix size is 0.\n");
          exit(1);
        }
        auto param = prefix.at(0);
        prefix.erase(prefix.begin());
        // tok.list.push_back(param);
        tok.list.insert(tok.list.begin(), param);
      }
      prefix.insert(prefix.begin(), tok);
    }
    /*
    if (!is_number(tok.tok)) {
      if (tok.tok == "+" || tok.tok == "-" || tok.tok == "*" ||
          tok.tok == "/" || tok.tok == "max") {
        auto p1 = prefix.at(0);
        prefix.erase(prefix.begin());
        auto p2 = prefix.at(0);
        prefix.erase(prefix.begin());
        tok.list.push_back(p2);
        tok.list.push_back(p1);
        prefix.insert(prefix.begin(), tok);
        auto s_expr_str = string("");
        cell_to_s_expression(prefix.at(0), s_expr_str);
        printf("prefix s expr %s\n", s_expr_str.c_str());
      } else {
        auto p1 = prefix.at(0);
        prefix.erase(prefix.begin());
        tok.list.push_back(p1);
        prefix.insert(prefix.begin(), tok);
      }
    } else {
      prefix.insert(prefix.begin(), tok);
    }
    */
  }
  /*for (auto &c : prefix) {
    printf("pycell %s\n", c.tok.c_str());
  }*/
  if (prefix.size() != 1) {
    printf("file: %s\nline number: %d\nline: %s\n", file_name.c_str(),
           line_number, line.c_str());
    printf(
        "shunting yard prefix size is != 1. This indicates an error, wrong "
        "number of params probably. size '%ld'\n",
        prefix.size());
    exit(1);
  }
  /*
  for (int i = 0; i < prefix.size(); i++) {
    printf("prefix %d %s\n", i, prefix.at(i).tok.c_str());
    auto s_expr_str = string("");
    cell_to_s_expression(prefix.at(i), s_expr_str);
    printf("s expr str %d %s\n", i, s_expr_str.c_str());
  }
  */
  /*
  this should not be needed, I belive it indicates an error, prefix.size() > 1
  while (prefix.size() != 1) {
    auto t = prefix.at(1);
    prefix.erase(prefix.begin() + 1);
    prefix.at(0).list.insert(prefix.at(0).list.begin(), t);
  }
  */
  // print_cell(prefix.at(0));
  auto s_expr_str = string("");
  cell_to_s_expression(prefix.at(0), s_expr_str);
  // printf("s expr str %s\n", s_expr_str.c_str());
  return s_expr_str;
}

bool PYCompiler::is_primitive_type(string &variable_type) {
  return variable_type == "int" || variable_type == "double" ||
         variable_type == "char" || variable_type == "char*";
}

bool PYCompiler::is_number(string token) {
  std::string::const_iterator it = token.begin();
  while (it != token.end() && std::isdigit(*it)) ++it;
  return !token.empty() && it == token.end();
}

string PYCompiler::math_to_s_expression(string s) {
  auto prefix = infixToPrefixStr(s);
  return prefixToSExpression(prefix);
}

string PYCompiler::math_to_s_expression(vector<pair<bool, string>> vals) {
  auto prefix = infixToPrefixStr(vals);
  return prefixToSExpression(prefix);
}

vector<string> PYCompiler::tokenize_line(const string &line) {
  auto toks = vector<string>();
  if (line.size() == 0) {
    return toks;
  }
  auto split = string_split(line, ' ');
  auto current_word = string("");
  auto char_ptr_str = string("");
  auto parsing_char_ptr = false;
  for (auto c : line) {
    if (isspace(c) && !parsing_char_ptr) {
      if (current_word.size() > 0) {
        toks.push_back(current_word);
      }
      current_word.clear();
    } else if (c == '"') {
      current_word.push_back(c);
      if (parsing_char_ptr) {
        toks.push_back(current_word);
        current_word.clear();
      }
      parsing_char_ptr = !parsing_char_ptr;
    } else {
      current_word.push_back(c);
    }
  }
  if (current_word.size() > 0) {
    toks.push_back(current_word);
  }
  /*for (auto &t : toks) {
    printf("tokenize %s\n", t.c_str());
  }*/
  return toks;
}

string PYCompiler::compile_function_def(string line) {
  auto output = string("");
  auto split = string_split(line, ' ');
  output += "defun " + split.at(1) + " (";
  for (int i = 2; i < split.size(); i++) {
    auto s = split.at(i);
    // printf("param %s\n", s.c_str());
    // the split above isnt using the tokenize line method
    if (s.size() == 0) {
      continue;
    }
    // params are done
    if (s == ")") {
      break;
    }
    if (s == "(" || s == ",") {
      continue;
    }
    remove_leading_spaces(s);
    remove_trailing_spaces(s);
    auto inc_i = false;
    if (split.at(i + 1) == ")" || split.at(i + 1) == "," ||
        split.at(i + 1).size() == 0) {
      output += "(" + s + " " + "Any" + ")";
    } else {
      auto type_str = split.at(i + 1);
      if (type_str == "str") {
        type_str = "char*";
      } else if (type_str == "float") {
        type_str = "double";
      } else if (type_str.find("Array") != string::npos) {
        auto dimensions = 1;
        if (type_str.find("2D") != string::npos) {
          dimensions = 2;
        } else if (type_str.find("3D") != string::npos) {
          dimensions = 3;
        }
        auto toks = string_split(type_str, '[');
        auto type_split_toks = string_split(toks[1], ']');
        auto array_elements_type = type_split_toks[0];
        type_str = "Array_" + array_elements_type + "_" +
                   to_string(dimensions) + "_dim";
      }
      output += "(" + s + " " + type_str + ")";
      // skip type token
      inc_i = true;
    }
    if (!(split.at(i + 1) == ")" || (inc_i && split.at(i + 2) == ")"))) {
      output += " ";
    }
    if (inc_i) {
      i += 1;
    }
  }
  output += ")";
  // get return type if there is one
  if (split.at(split.size() - 1) == ")") {
    output += " Any";
  } else {
    auto type_str = split.at(split.size() - 1);
    if (type_str == "str") {
      type_str = "char*";
    } else if (type_str == "float") {
      type_str = "double";
    } else if (type_str.find("Array") != string::npos) {
      auto dimensions = 1;
      if (type_str.find("2D") != string::npos) {
        dimensions = 2;
      } else if (type_str.find("3D") != string::npos) {
        dimensions = 3;
      }
      auto toks = string_split(type_str, '[');
      auto type_split_toks = string_split(toks[1], ']');
      auto array_elements_type = type_split_toks[0];
      type_str = dimensions + "_" + array_elements_type + "_Array";
    }
    output += " " + type_str;
  }
  output += ")";
  output.insert(0, "(");
  // printf("output %s\n", output.c_str());
  return output;
}

string PYCompiler::compile_enum(string line, vector<string> tokens) {
  auto split = string_split(line, ' ');
  current_enum_string = tokens.at(1);
  return "(defenum " + tokens.at(1) + ")";
}

string PYCompiler::compile_enum_member_var(string line, vector<string> tokens) {
  // auto enum_str = current_enum_string + "_" + tokens[0];
  // enum_values_dict[enum_str] = true;
  return "(" + tokens[0] + ")";
}

string PYCompiler::compile_class(string line, vector<string> tokens) {
  auto split = string_split(line, ' ');
  return "(defclass " + tokens.at(1) + ")";
}

string PYCompiler::compile_class_member_var(string line,
                                            vector<string> tokens) {
  // ptr hack for now
  replaceAll(line, "Ptr", "*");
  auto split = string_split(line, ' ');
  auto variable_str = split.at(0);
  if (variable_str.at(variable_str.size() - 1) == ':') {
    variable_str.pop_back();
  }
  auto variable_str_after_self = string("");
  // start at 5 (idx 6) to skip the substring "self.".
  for (int i = 5; i < variable_str.size(); i++) {
    variable_str_after_self.push_back(variable_str.at(i));
  }
  string type_str = string("");
  if (split.at(1).find("Array") != string::npos) {
    auto array_type_str = split.at(1);
    auto array_type_str_split = string_split(array_type_str, '[');
    array_type_str_split = string_split(array_type_str_split.at(1), ']');
    array_type_str = array_type_str_split.at(0);
    type_str = "(make_array " + array_type_str + " " + split.at(5) + ")";
  } else {
    type_str = split.at(1);
  }
  if (type_str == "float") {
    type_str = "double";
  }
  return "(" + type_str + " " + variable_str_after_self + ")";
}

string PYCompiler::compile_conditional(string line, vector<string> tokens) {
  auto output = string("");
  auto cond_str = tokens.at(0);
  tokens.erase(tokens.begin());
  output += "(" + cond_str;
  if (cond_str != "else") {
    output += " ";
  }
  if (cond_str != "else") {
    output += shunting_yard_s_expr(tokens, line);
  }
  output += ")";
  return output;
}

string PYCompiler::compile_while(string line, vector<string> tokens) {
  // erase "while" from tokens
  tokens.erase(tokens.begin());
  auto output = string("");
  output += "(while ";
  output += shunting_yard_s_expr(tokens, line);
  output += ")";
  return output;
}

string PYCompiler::compile_for(string line, vector<string> tokens) {
  auto output = string("");
  // enumerate loop for i, item in enumerate(items)
  if (line.find("enumerate") != string::npos) {
    // the array must be a literal, not a function call because im not doing
    // shunting yard yet.
    output =
        "(map " + tokens.at(1) + " " + tokens.at(3) + " " + tokens.at(7) + ")";
  }
  // for i loop (for i in range(322) or for i in rev_range(322))
  else if (line.find("range") != string::npos) {
    output += "(" + tokens.at(0) + " " + tokens.at(1) + " ";
    tokens.erase(tokens.begin(), tokens.begin() + 3);
    for (auto t : tokens) {
      // printf("compile for %s\n", t.c_str());
    }
    output += shunting_yard_s_expr(tokens, line);
    output += ")";
  }
  // for in loop (for item in items)
  else {
    // the array must be a literal, not a function call because im not doing
    // shunting yard yet.
    output = "(foreach " + tokens.at(1) + " " + tokens.at(3) + ")";
  }
  return output;
}

string PYCompiler::compile_import(
    string line, vector<string> tokens, bool is_weak_import,
    unordered_map<string, string> &ct_file_content_dict) {
  auto output = string("");
  auto py_path = tokens.at(1);
  auto py_path_split = string_split(py_path, '.');
  auto py_file_name = py_path_split.at(py_path_split.size() - 1);
  if (py_file_name == "typing" || py_file_name == "base_types" ||
      py_file_name == "enum") {
    return "";
  }
  // from sprite import *
  if (is_weak_import) {
    output += "(weak_import " + py_file_name + ")";
  } else {
    output += "(import " + py_file_name + ")";
  }

  // compile the file if it hasn't been compiled yet
  if (compiled_files.find(py_file_name) == compiled_files.end()) {
    // make a new pycompiler to compile the file (inefficient but convenient)
    auto file_compiler =
        PYCompiler(files_base_directory, ct_files_base_directory);
    // add compiled files to the new compiler so that it doenst compile
    // files that have already been compiled.
    file_compiler.compiled_files = compiled_files;
    file_compiler.compile_file(py_file_name, ct_file_content_dict);
    // for each file in the new pycompile files, add them to the
    // compiled files in this compiler so that it knows about what
    // was compiled and doesnt compile the files again.
    for (auto &entry : file_compiler.compiled_files) {
      compiled_files[entry.first] = true;
    }
  }
  return output;
}

string PYCompiler::compile_return(string line, vector<string> tokens) {
  if (tokens.size() == 1) {
    return string("(return)");
  }
  auto output = string("");
  output += "(" + tokens.at(0) + " ";
  tokens.erase(tokens.begin());
  output += shunting_yard_s_expr(tokens, line);
  output += ")";
  return output;
}

string PYCompiler::compile_equals(string line, vector<string> tokens) {
  auto l = string("");
  auto r = string("");
  auto equals_split = string_split(line, '=');
  /*for (int i = 0; i < equals_split.size(); i++) {
    printf("equals %s\n", equals_split.at(i).c_str());
  }*/
  return line;
}

int PYCompiler::get_num_negatives(vector<string> &tokens) {
  int n = 0;
  for (int i = 0; i < tokens.size(); i++) {
    auto &s = tokens.at(i);
    if (s.size() == 0) {
      continue;
    } else if (s == "-=") {
      continue;
    } else if (s.at(0) == '"' && s.at(s.size() - 1) == '"') {
      continue;
    }
    // handles the case -(2 + 2)
    if (s == "-" && i + 1 <= tokens.size() - 1 && tokens.at(i + 1) == "(") {
      n += 1;
    } else if (s.at(0) == '-' && s.size() >= 2) {
      n += 1;
    }
  }
  return n;
}

// only replaces the first negative for simplicity (perf shouldnt matter too
// much for this)
void PYCompiler::replace_first_negative_with_func(vector<string> &tokens) {
  auto found_negative = false;
  auto is_math_parens_expression = false;
  int parenths = 0;
  int start_idx = -1;
  int end_idx = -1;
  for (int i = 0; i < tokens.size(); i++) {
    auto &s = tokens.at(i);
    // printf("%d %s %d\n", i, s.c_str(), parenths);
    // printf("%d %s %d %d\n", i, s.c_str(), found_negative, parenths);
    if (s.size() == 0) {
      continue;
    } else if (s == "-=") {
      continue;
    } else if (s.at(0) == '"' && s.at(s.size() - 1) == '"') {
      continue;
    } else if (found_negative) {
      if (s.find("(") != string::npos) {
        parenths += 1;
      } else if (s.find(")") != string::npos) {
        parenths -= 1;
      }
      if (parenths == 0) {
        end_idx = i;
        break;
      }
    } else if (!found_negative && s == "-" && i + 1 <= tokens.size() - 1 &&
               tokens.at(i + 1) == "(") {
      is_math_parens_expression = true;
      found_negative = true;
      start_idx = i;
      s.erase(s.begin());
      parenths = 0;
    } else if (!found_negative && s.at(0) == '-' && s.size() >= 2) {
      if (s.at(1) == '(') {
        s = "negate(";
        return;
      }
      found_negative = true;
      start_idx = i;
      s.erase(s.begin());
      // parenths - example -(2 + 2)
      if (s.find("(") != string::npos) {
        parenths = 1;
      }
      // function call - eample -func(2) parenths will be the next token so set
      // parenths to 0.
      else if (i + 1 <= tokens.size() - 1 && tokens.at(i + 1) == "(") {
        parenths = 0;
      } else {
        // not a func (example -5)
        end_idx = i;
        break;
      }
    }
  }
  // printf("start end %d %d\n", start_idx, end_idx);
  if (start_idx != -1 && end_idx != -1) {
    if (is_math_parens_expression) {
      tokens[start_idx] = "negate" + tokens[start_idx];
    } else {
      // negative number of negative var
      if (start_idx == end_idx) {
        tokens.insert(tokens.begin() + (start_idx + 1), ")");
        tokens.insert(tokens.begin() + start_idx, "(");
        tokens.insert(tokens.begin() + start_idx, "negate");
      } else {
        tokens.insert(tokens.begin() + end_idx, ")");
        tokens.insert(tokens.begin() + start_idx, "(");
        tokens.insert(tokens.begin() + start_idx, "negate");
      }
    }
  }
}

void PYCompiler::replace_all_negatives(vector<string> &tokens) {
  int num_iters = 0;
  while (get_num_negatives(tokens) != 0) {
    if (num_iters > 1000) {
      printf("PYCompiler::replace_all_negatives. num_iters > 1000.\n");
      exit(1);
      return;
    }
    replace_first_negative_with_func(tokens);
  }
}

// only replaces the first negative for simplicity (perf shouldnt matter too
// much for this)
void PYCompiler::replace_first_not_with_func(vector<string> &tokens) {
  auto found_negative = false;
  auto is_math_parens_expression = false;
  int parenths = 0;
  int start_idx = -1;
  int end_idx = -1;
  for (int i = 0; i < tokens.size(); i++) {
    auto &s = tokens.at(i);
    // printf("%d %s %d\n", i, s.c_str(), parenths);
    // printf("%d %s %d %d\n", i, s.c_str(), found_negative, parenths);
    if (s.size() == 0) {
      continue;
    } else if (found_negative) {
      if (s.find("(") != string::npos) {
        parenths += 1;
      } else if (s.find(")") != string::npos) {
        parenths -= 1;
      }
      if (parenths == 0) {
        end_idx = i;
        break;
      }
    } else if (!found_negative && s == "-" && i + 1 <= tokens.size() - 1 &&
               tokens.at(i + 1) == "(") {
      is_math_parens_expression = true;
      found_negative = true;
      start_idx = i;
      s.erase(s.begin());
      parenths = 0;
    } else if (!found_negative && s.at(0) == '-' && s.size() >= 2) {
      if (s.at(1) == '(') {
        s = "negate(";
        return;
      }
      found_negative = true;
      start_idx = i;
      s.erase(s.begin());
      // parenths - example -(2 + 2)
      if (s.find("(") != string::npos) {
        parenths = 1;
      }
      // function call - eample -func(2) parenths will be the next token so set
      // parenths to 0.
      else if (i + 1 <= tokens.size() - 1 && tokens.at(i + 1) == "(") {
        parenths = 0;
      } else {
        // not a func (example -5)
        end_idx = i;
        break;
      }
    }
  }
  // printf("start end %d %d\n", start_idx, end_idx);
  if (start_idx != -1 && end_idx != -1) {
    if (is_math_parens_expression) {
      tokens[start_idx] = "not" + tokens[start_idx];
    } else {
      // negative number of negative var
      if (start_idx == end_idx) {
        tokens.insert(tokens.begin() + (start_idx + 1), ")");
        tokens.insert(tokens.begin() + start_idx, "(");
        tokens.insert(tokens.begin() + start_idx, "not");
      } else {
        tokens.insert(tokens.begin() + end_idx, ")");
        tokens.insert(tokens.begin() + start_idx, "(");
        tokens.insert(tokens.begin() + start_idx, "not");
      }
    }
  }
}

void PYCompiler::replace_all_nots(vector<string> &tokens) {
  int num_iters = 0;
  while (get_num_nots(tokens) != 0) {
    if (num_iters > 1000) {
      printf("PYCompiler::replace_all_nots. num_iters > 1000.\n");
      exit(1);
      return;
    }
    replace_first_negative_with_func(tokens);
  }
}

int PYCompiler::get_num_nots(vector<string> &tokens) {
  int n = 0;
  for (auto t : tokens) {
    if (t == "not") {
      n += 1;
    }
  }
  return n;
}

void PYCompiler::get_cells(vector<string> &tokens, PYCell &cell,
                           bool do_recur_call) {
  if (tokens.size() == 0) {
    return;
  }
  auto token = tokens[0];
  // printf("call %s\n", token.c_str());
  remove_leading_spaces(token);
  remove_trailing_spaces(token);
  tokens.erase(tokens.begin());
  if (is_function(token)) {
    auto func_name = string("");
    for (int i = 0; i < token.size() - 1; i++) {
      func_name.push_back(token.at(i));
    }
    auto c = PYCell(true, token, vector<PYCell>());
    c.list.push_back(PYCell(false, func_name, vector<PYCell>()));
    int num_parenths = 1;
    int num_iters = 0;
    while (num_parenths > 0) {
      if (is_function(tokens[0]) || tokens[0].find('(') != string::npos) {
        num_parenths += 1;
      }
      if (tokens[0].find(')') != string::npos) {
        num_parenths -= 1;
      }
      // printf("t %s - %d\n", tokens[0].c_str(), num_parenths);
      get_cells(tokens, c, false);
      // printf("end %s - %d\n", token.c_str(), num_parenths);
    }
    cell.list.push_back(c);
    // tokens.erase(tokens.begin());
  } else {
    cell.list.push_back(PYCell(false, token, vector<PYCell>()));
    if (do_recur_call) {
      get_cells(tokens, cell, true);
    }
  }
}

void PYCompiler::print_cell(PYCell &cell) {
  if (cell.list.size() > 0) {
    printf("func call (%s) (\n", cell.tok.c_str());
    for (auto &c : cell.list) {
      print_cell(c);
    }
    printf("func call end )\n");
  } else {
    printf("%s\n", cell.tok.c_str());
  }
}

void PYCompiler::post_process_params(PYCell &cell, PYCell &output_cell) {
  if (cell.list.size() > 0) {
    output_cell.list.push_back(PYCell(true, cell.tok, vector<PYCell>()));
    auto &func_cell = output_cell.list.at(output_cell.list.size() - 1);
    if (cell.list.size() > 0) {
      func_cell.list.push_back(
          PYCell(false, cell.list.at(0).tok, vector<PYCell>()));
    }
    auto param_str = string("");
    for (int i = 1; i < cell.list.size(); i++) {
      auto &c = cell.list.at(i);
      if (c.list.size() > 0) {
        // printf("is list %d %ld\n", i, c.list.size());
        post_process_params(c, func_cell);
      } else {
        // printf("post process %d %s\n", i, c.tok.c_str());
        if (c.tok.find(',') != string::npos || i == cell.list.size() - 2) {
          if (c.tok.find(',') != string::npos) {
            c.tok.pop_back();
          }
          param_str += c.tok;
          // sometimes param_str will have closing parenths, remove them. kind
          // of hacky.
          replaceAll(param_str, " )", "");
          replaceAll(param_str, ")", "");
          if (param_str.size() > 0) {
            func_cell.list.push_back(
                PYCell(false, param_str, vector<PYCell>()));
          }
          param_str.clear();
        } else {
          param_str += c.tok + " ";
        }
      }
    }
  }
}

void PYCompiler::cell_to_s_expression(PYCell &cell, string &output) {
  if (cell.is_func) {
    output += "(" + cell.tok;
    for (int i = 0; i < cell.list.size(); i++) {
      if (i == 0) {
        output += " ";
      }
      auto &c = cell.list.at(i);
      cell_to_s_expression(c, output);
      if (i != cell.list.size() - 1) {
        output += " ";
      }
    }
    output += ")";
  } else {
    output += cell.tok;
  }
}

void PYCompiler::cell_to_s_expression(PYCell &cell, string &output,
                                      bool s_expr_math, bool is_initial_cell) {
  if (cell.list.size() > 0) {
    // skip for initial pycell
    if (!is_initial_cell) {
      output += "(";
    }
    for (int i = 0; i < cell.list.size(); i++) {
      auto &c = cell.list.at(i);
      // printf("c %d %ld %s\n", i, cell.list.size(), c.tok.c_str());
      cell_to_s_expression(c, output, s_expr_math, false);
      if (i != cell.list.size() - 1) {
        output += " ";
      }
    }
    if (!is_initial_cell) {
      output += ")";
    }
  } else {
    if (cell.tok != "(" && cell.tok != ")") {
      // printf("tok %s %d\n", cell.tok.c_str(), contains_math(cell.tok));
      if (s_expr_math) {
        if (contains_math(cell.tok)) {
          // printf("math tok %s\n", cell.tok.c_str());
          output += math_to_s_expression(cell.tok);
        } else {
          // fixes a spacing bug. maybe change this later.
          replaceAll(cell.tok, " )", ")");
          output += cell.tok;
        }
      } else {
        output += cell.tok;
      }
    }
  }
}

bool PYCompiler::is_function(string &s) {
  for (int i = 0; i < s.size(); i++) {
    if (s.at(i) == '(') {
      if (i >= 1) {
        auto c = s.at(i - 1);
        if (!(c == '+' || c == '-' || c == '*' || c == '/')) {
          return true;
        }
      }
    }
  }
  return false;
}

void PYCompiler::replaceAll(std::string &str, const std::string &from,
                            const std::string &to) {
  if (from.empty()) return;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();  // In case 'to' contains 'from', like replacing
                               // 'x' with 'yx'
  }
}

vector<string> PYCompiler::string_split(const string &s, char delim) {
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

int PYCompiler::num_leading_spaces(string &s) {
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

void PYCompiler::exit_if_parenths_dont_match(string &s) {
  int l = 0;
  int r = 0;
  for (auto c : s) {
    if (c == '(') {
      l += 1;
    } else if (c == ')') {
      r += 1;
    }
  }
  if (l != r) {
    printf(
        "PYCompiler::exit_if_parenths_dont_match. Parenths don't match. Left "
        "parenths: %d, right parenths: %d\nstr: %s\nfile: '%s'\nline: '%d'\n",
        l, r, s.c_str(), file_name.c_str(), line_number);
    exit(1);
  }
}

void PYCompiler::remove_leading_spaces(string &s) {
  while (!s.empty() && std::isspace(*s.begin())) s.erase(s.begin());
}

void PYCompiler::remove_trailing_spaces(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](int ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

bool PYCompiler::isOperator(char c) { return (!isalpha(c) && !isdigit(c)); }

int PYCompiler::getPriority(char c) {
  if (c == '-' || c == '+')
    return 1;
  else if (c == '*' || c == '/')
    return 2;
  else if (c == '^')
    return 3;
  return 0;
}

bool PYCompiler::isOperator(string s) {
  if (s.size() == 0) {
    return false;
  }
  remove_leading_spaces(s);
  remove_trailing_spaces(s);
  if (s == "=" || s == "-" || s == "+" || s == "*" || s == "/" || s == "%" ||
      s == "^" || s == "+=" || s == "-=" || s == "*=" || s == "/=" ||
      s == ">" || s == ">=" || s == "<" || s == "<=" || s == "==" ||
      s == "!=" || s == "and" || s == "or") {
    return true;
  }
  /*
  auto c = s.at(0);
  return (s.size() == 1 && !isalpha(c) && !isdigit(c));
  */
  return false;
}

int PYCompiler::getPriority(string &s) {
  if (s == "=" || s == "+=" || s == "-=" || s == "*=" || s == "/=")
    return 1;
  else if (s == "and" || s == "or")
    return 2;
  else if (s == "==" || s == "!=")
    return 3;
  else if (s == "%")
    return 4;
  else if (s == ">" || s == ">=" || s == "<" || s == "<=")
    return 5;
  else if (s == "-" || s == "+")
    return 6;
  else if (s == "*" || s == "/")
    return 7;
  else if (s == "^")
    return 8;
  return 20;
}

bool PYCompiler::string_is_alpha(string &s) {
  if (s.size() >= 2 && s.at(0) == '"' && s.at(s.size() - 1) == '"') {
    return true;
  }
  if (s == "and" || s == "or" || s == ">=" || s == "<=" || s == "==" ||
      s == "!=") {
    return false;
  }
  // handle -50 for example
  if (s.size() > 1 && s.at(0) == '-') {
    return true;
  }
  for (auto c : s) {
    if (c == '.' || c == '[' || c == ']' || c == '_') {
      continue;
    }
    if (!(isalpha(c) || isdigit(c))) {
      return false;
    }
  }
  return true;
}

vector<string> PYCompiler::infixToPostfixStr(vector<pair<bool, string>> infix) {
  infix.insert(infix.begin(), make_pair(false, "("));
  infix.push_back(make_pair(false, ")"));
  stack<string> str_stack;
  vector<string> output;

  for (int i = 0; i < infix.size(); i++) {
    auto &val = infix.at(i);
    // printf("%d %s\n", i, val.second.c_str());
    // If the scanned character is an
    // operand, add it to output.
    if (val.first || string_is_alpha(val.second)) {
      output.push_back(val.second);
    }

    // If the scanned character is an
    // ‘(‘, push it to the stack.
    else if (val.second == "(") {
      str_stack.push(val.second);
    }

    // If the scanned character is an
    // ‘)’, pop and output from the stack
    // until an ‘(‘ is encountered.
    else if (val.second == ")") {
      while (str_stack.top() != "(") {
        output.push_back(str_stack.top());
        str_stack.pop();
      }

      // Remove '(' from the stack
      str_stack.pop();
    }

    // Operator found
    else {
      if (str_stack.size() == 0) {
        printf("PYCompiler::infixToPostfixStr - str_stack is empty.\n");
        exit(1);
      }
      if (isOperator(str_stack.top())) {
        while (getPriority(val.second) <= getPriority(str_stack.top())) {
          output.push_back(str_stack.top());
          str_stack.pop();
        }

        // Push current Operator on stack
        str_stack.push(val.second);
      }
    }
  }
  return output;
}

vector<string> PYCompiler::infixToPostfixStr(string infix) {
  auto split = string_split(infix, ' ');
  split.insert(split.begin(), "(");
  split.push_back(")");
  auto l = split.size();
  stack<string> str_stack;
  vector<string> output;

  for (int i = 0; i < l; i++) {
    auto &s = split.at(i);
    // If the scanned character is an
    // operand, add it to output.
    if (string_is_alpha(s)) {
      output.push_back(s);
    }

    // If the scanned character is an
    // ‘(‘, push it to the stack.
    else if (s == "(") {
      str_stack.push(s);
    }

    // If the scanned character is an
    // ‘)’, pop and output from the stack
    // until an ‘(‘ is encountered.
    else if (s == ")") {
      while (str_stack.top() != "(") {
        output.push_back(str_stack.top());
        str_stack.pop();
      }

      // Remove '(' from the stack
      str_stack.pop();
    }

    // Operator found
    else {
      if (isOperator(str_stack.top())) {
        while (getPriority(s) <= getPriority(str_stack.top())) {
          output.push_back(str_stack.top());
          str_stack.pop();
        }

        // Push current Operator on stack
        str_stack.push(s);
      }
    }
  }
  return output;
}

string PYCompiler::infixToPostfix(string infix) {
  infix = '(' + infix + ')';
  int l = infix.size();
  stack<char> char_stack;
  string output;

  for (int i = 0; i < l; i++) {
    if (isspace(infix[i])) {
      continue;
    }
    // If the scanned character is an
    // operand, add it to output.
    if (isalpha(infix[i]) || isdigit(infix[i])) {
      output += infix[i];
    }

    // If the scanned character is an
    // ‘(‘, push it to the stack.
    else if (infix[i] == '(') {
      char_stack.push('(');
    }

    // If the scanned character is an
    // ‘)’, pop and output from the stack
    // until an ‘(‘ is encountered.
    else if (infix[i] == ')') {
      while (char_stack.top() != '(') {
        output += char_stack.top();
        char_stack.pop();
      }

      // Remove '(' from the stack
      char_stack.pop();
    }

    // Operator found
    else {
      if (isOperator(char_stack.top())) {
        while (getPriority(infix[i]) <= getPriority(char_stack.top())) {
          output += char_stack.top();
          char_stack.pop();
        }

        // Push current Operator on stack
        char_stack.push(infix[i]);
      }
    }
  }
  // printf("postfix %s\n", output.c_str());
  return output;
}

vector<string> PYCompiler::infixToPrefixStr(vector<pair<bool, string>> infix) {
  /* Reverse String
   * Replace ( with ) and vice versa
   * Get Postfix
   * Reverse Postfix  *  */
  // reverse the split and then build it back up in a buffer later,
  // if you reverse the string numbers will be reversed - 51 becomes 15,
  // thats why the split is reversed so the numbers are still preserved
  // correctly.
  reverse(infix.begin(), infix.end());

  /*int l = infix.size();

  // Reverse infix
  reverse(infix.begin(), infix.end());*/

  // Replace ( with ) and vice versa
  for (auto &val : infix) {
    if (val.first) {
      continue;
    }
    for (auto &c : val.second) {
      if (c == '(') {
        c = ')';
      } else if (c == ')') {
        c = '(';
      }
    }
  }

  auto prefix = infixToPostfixStr(infix);

  // Reverse postfix
  reverse(prefix.begin(), prefix.end());
  /*for (int i = prefix.size() - 1; i > -1; i--) {
    if (i != prefix.size() - 1 && prefix.at(i) != '(' && prefix.at(i) != ')')
  { prefix.insert(i + 1, " ");
    }
  }*/
  return prefix;
}

vector<string> PYCompiler::infixToPrefixStr(string infix) {
  /* Reverse String
   * Replace ( with ) and vice versa
   * Get Postfix
   * Reverse Postfix  *  */
  // reverse the split and then build it back up in a buffer later,
  // if you reverse the string numbers will be reversed - 51 becomes 15,
  // thats why the split is reversed so the numbers are still preserved
  // correctly.
  auto split = string_split(infix, ' ');
  reverse(split.begin(), split.end());

  /*int l = infix.size();

  // Reverse infix
  reverse(infix.begin(), infix.end());*/

  // Replace ( with ) and vice versa
  for (auto &s : split) {
    for (auto &c : s) {
      if (c == '(') {
        c = ')';
      } else if (c == ')') {
        c = '(';
      }
    }
  }

  auto str_buffer = string("");
  for (int i = 0; i < split.size(); i++) {
    auto &s = split.at(i);
    str_buffer += s;
    if (i != split.size() - 1) {
      str_buffer += " ";
    }
  }

  auto prefix = infixToPostfixStr(str_buffer);

  // Reverse postfix
  reverse(prefix.begin(), prefix.end());
  /*for (int i = prefix.size() - 1; i > -1; i--) {
    if (i != prefix.size() - 1 && prefix.at(i) != '(' && prefix.at(i) != ')')
  { prefix.insert(i + 1, " ");
    }
  }*/
  return prefix;
}

string PYCompiler::infixToPrefix(string infix) {
  /* Reverse String
   * Replace ( with ) and vice versa
   * Get Postfix
   * Reverse Postfix  *  */
  int l = infix.size();

  // Reverse infix
  reverse(infix.begin(), infix.end());

  // Replace ( with ) and vice versa
  for (int i = 0; i < l; i++) {
    if (infix[i] == '(') {
      infix[i] = ')';
      i++;
    } else if (infix[i] == ')') {
      infix[i] = '(';
      i++;
    }
  }

  string prefix = infixToPostfix(infix);

  // Reverse postfix
  reverse(prefix.begin(), prefix.end());
  /*for (int i = prefix.size() - 1; i > -1; i--) {
    if (i != prefix.size() - 1 && prefix.at(i) != '(' && prefix.at(i) != ')')
  { prefix.insert(i + 1, " ");
    }
  }*/
  return prefix;
}

string PYCompiler::prefixToSExpression(vector<string> &prefix) {
  // printf("prefix size %ld\n", prefix.size());
  auto s_expr = string("");
  auto expressions = stack<string>();
  for (int i = prefix.size() - 1; i > -1; i--) {
    auto s = prefix.at(i);
    // printf("%d %s\n", i, s.c_str());
    if (s == "+" || s == "-" || s == "*" || s == "/" || s == "%" || s == "+=" ||
        s == "-=" || s == "*=" || s == "/=" || s == "and" || s == "or" ||
        s == ">" || s == ">=" || s == "<" || s == "<=" || s == "==" ||
        s == "!=" || s == "=") {
      if (expressions.size() < 2) {
        printf(
            "PYCompiler::prefixToSExpression. expressions size is < 2, "
            "expected a size >= 2.\n");
        exit(1);
      }
      auto p1 = expressions.top();
      expressions.pop();
      auto p2 = expressions.top();
      expressions.pop();
      auto expr = string("(");
      expr += s;
      expr += " " + p1 + " " + p2 + ")";
      expressions.push(expr);
    } else {
      expressions.push(s);
    }
  }

  if (expressions.size() != 1) {
    printf(
        "PYCompiler::prefixToSExpression. expressions size is > 1, expected "
        "size of 1.\n");
    exit(1);
  }
  auto expr = expressions.top();
  return expr;
}

bool PYCompiler::contains_math(string &s) {
  if (s.size() == 0) {
    return false;
  }
  if (s.size() >= 2 && s.at(0) == '"' && s.at(s.size() - 1) == '"') {
    return false;
  }
  if (s.find("and") != string::npos || s.find("or") != string::npos ||
      s.find(">=") != string::npos || s.find("<=") != string::npos ||
      s.find("==") != string::npos || s.find("!=") != string::npos) {
    return true;
  }
  for (int i = 0; i < s.size(); i++) {
    auto c = s.at(i);
    if (i == 0 && c == '-' && s.size() > 1) {
      return false;
    }
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '>' || c == '<' ||
        c == '=') {
      return true;
    }
  }
  return false;
}