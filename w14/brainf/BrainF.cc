#include "BrainF.hh"

int BrainF::parse(std::istream &sourceFile) {
  char chr;
  while ((chr = sourceFile.get()) != EOF) {
    if (chr != '>' && chr != '<' && chr != '+' && chr != '-' && chr != '.' &&
        chr != ',' && chr != '[' && chr != ']')
      continue; // ignore any unknown character
    program.push_back(chr);
    if (chr == '>' || chr == '<' || chr == '+' || chr == '-' || chr == '.' ||
        chr == ',')
      continue;
    if (chr == '[')
      loopStart.push(program.size() - 1);
    else if (chr == ']' && loopStart.size() > 0) {
      auto startPos = loopStart.top();
      loopStart.pop();
      loopEnd[startPos] = program.size(); // opening [ knows where its ] is
    } else {
      return -1; // error, ] without [
    }
  }
  return loopStart.size();
}
int BrainF::run(const size_t memSize, std::istream &fin, std::ostream &fout) {
  char *mem = new char[memSize];
  char *ptr = mem;

  for (auto i = 0; i < program.size(); ++i) {
    if (program[i] == '>')
      ++ptr;
    else if (program[i] == '<')
      --ptr;
    else if (program[i] == '+')
      ++*ptr;
    else if (program[i] == '-')
      --*ptr;
    else if (program[i] == '.')
      fout << *ptr;
    else if (program[i] == ',')
      *ptr = fin.get();
    else if (program[i] == '[' && *ptr != 0)
      loopStart.push(i);
    else if (program[i] == '[')
      i = loopEnd[i]; // jumps to after the corresponding ]
    else if (program[i] == ']' && *ptr != 0)
      i = loopStart.top(); // return to the corresponding [
    else
      loopStart.pop(); // loop ended
  }

  delete[] mem;
  return 0;
}

void BrainF::print(std::ostream &fout) {
  size_t indent_level = 0;
  std::string indent = "	";
  for (auto i = program.begin(); i < program.end(); ++i) {
    if (*i == ']')
      indent_level--;
    for (auto i = 0; i < indent_level; ++i)
      fout << indent;
    fout << *i << "\n";
    if (*i == '[')
      indent_level++;
  }
}

void BrainF::printC(std::ostream &fout) {
  size_t indent_level = 1;
  std::string indent = "	";
  size_t indent_width = 4;
  std::string cmd;
  fout << "#include <stdio.h>\n"
       << "#include <stdlib.h>\n"
       << "\n"
       << "int\n"
       << "main() {\n"
       << "	char *mem = (char*) malloc(30000);\n"
       << "	char *ptr = mem;\n"
       << "\n";
  for (auto i = program.begin(); i < program.end(); ++i) {
    if (*i == ']')
      indent_level--;
    switch (*i) {
    case '>':
      cmd = "++ptr;";
      break;
    case '<':
      cmd = "--ptr;";
      break;
    case '+':
      cmd = "++*ptr;";
      break;
    case '-':
      cmd = "--*ptr;";
      break;
    case '.':
      cmd = "putchar(*ptr);";
      break;
    case ',':
      cmd = "*ptr = getchar();";
      break;
    case '[':
      cmd = "while (*ptr) {";
      break;
    case ']':
      cmd = "}";
      break;
    }
    for (auto i = 0; i < indent_level; ++i)
      fout << indent;
    fout << cmd << "\n";
    if (*i == '[')
      indent_level++;
  }
  fout << "\n"
       << "	free(mem);\n"
       << "	return 0;\n"
       << "}\n";
}
