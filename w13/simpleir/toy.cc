#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;

int main() {
	auto TheContext = std::make_unique<LLVMContext>();
	auto TheModule = std::make_unique<Module>("main.bf", *TheContext);
	auto TheBuilder = std::make_unique<IRBuilder<>>(*TheContext);

	FunctionType* FT = FunctionType::get(Type::getInt32Ty(*TheContext), false);
	Function* MainFunc = Function::Create(FT, Function::ExternalLinkage, "main", TheModule.get());

	TheBuilder->SetInsertPoint(BasicBlock::Create(*TheContext,"", MainFunc));

	Value* a = TheBuilder->CreateAlloca(TheBuilder->getInt8PtrTy(), nullptr, "a");
	MainFunc->getParent()->getOrInsertFunction("calloc", TheBuilder->getInt8PtrTy());

	TheModule->print(errs(), nullptr);

	return 0;
}

