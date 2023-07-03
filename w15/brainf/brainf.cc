/**
 * clang++ *cc
 * ./a.out < helloworld.bf > helloworld.c
 * clang helloworld.c
 * ./a.out
 * output: Hello World!
 * */

#include "BrainF.hh"

#define MAX 30000

int main() {
	BrainF *bf = new BrainF();

	bf->parse(std::cin);
	//bf->run();
	bf->printC(std::cout);
	//bf->print(std::cout);

	delete bf;

	return 0;
}
