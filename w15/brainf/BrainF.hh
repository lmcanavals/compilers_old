#ifndef __BRAINF_H__
#define __BRAINF_H__

#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

class BrainF {
  std::vector<char> program;
  std::stack<size_t> loopStart;
  std::map<size_t, size_t> loopEnd;

public:
  int parse(std::istream &sourceFile);
  int run(const size_t memSize = 30000, std::istream &fin = std::cin,
          std::ostream &fout = std::cout);
  void print(std::ostream &fout);
	std::string produce(char last, size_t counter);
  void printC(std::ostream &fout);
};

#endif
