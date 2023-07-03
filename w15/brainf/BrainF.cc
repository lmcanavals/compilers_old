#include "BrainF.hh"
#include <asm-generic/errno.h>

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

// TODO write produce function, add it to class, etc.
std::string BrainF::produce(char last, size_t counter) {
	if (last == '>')
		return std::string("ptr += ") + std::to_string(counter) + std::string(";");
	if (last == '<')
		return std::string("ptr -= ") + std::to_string(counter) + std::string(";");
	if (last == '+')
		return std::string("*ptr += ") + std::to_string(counter) + std::string(";");
	if (last == '-')
		return std::string("*ptr -= ") + std::to_string(counter) + std::string(";");
	if (last == '.')
		return "putchar(*ptr);";
	if (last == ',')
		return "*ptr = getchar();";
	if (last == '[') 
		return "while (*ptr) {";
	if (last == ']')
		return "}";
	return "";
}

void BrainF::printC(std::ostream &fout) {
  size_t indent_level = 1;
  size_t indent_width = 4;
  char last = 0;
  size_t counter = 0;
  auto putIndent = [&fout](int n) {
    for (auto i = 0; i < n; ++i)
      fout << "\t";
  };

  fout << "#include <stdio.h>\n"
       << "#include <stdlib.h>\n"
       << "\n"
       << "int\n"
       << "main() {\n"
       << "	char *mem = (char*) malloc(30000);\n"
       << "	char *ptr = mem;\n";
  for (auto i = program.begin(); i < program.end(); ++i) {
    if (last == ']')
      indent_level--;
    if (*i != last && last != 0) {
      putIndent(indent_level);
      fout << produce(last, counter) << "\n";
			counter = 1;
    } else
      ++counter;
    if (last == '[')
      indent_level++;
		last = *i;
  }
  putIndent(indent_level);
  fout << produce(last, counter) << "\n";

  fout << "\n"
       << "	free(mem);\n"
       << "	return 0;\n"
       << "}\n";
}
