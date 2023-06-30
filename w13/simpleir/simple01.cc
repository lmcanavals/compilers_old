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
	auto TheModule = std::make_unique<Module>("My cool jit", *TheContext);
	auto TheBuilder = std::make_unique<IRBuilder<>>(*TheContext);

  Type *Tys[] = { Type::getInt8PtrTy(*TheContext), Type::getInt32Ty(*TheContext) };
  Function *memset_func = Intrinsic::getDeclaration(TheModule.get(), Intrinsic::memset,
                                                    Tys);
	auto getchar_func =
      TheModule->getOrInsertFunction("getchar", IntegerType::getInt32Ty(*TheContext));

	std::vector<Type*> Doubles(0, Type::getDoubleTy(*TheContext));
	FunctionType* FT = FunctionType::get(Type::getDoubleTy(*TheContext), Doubles, false);
	Function* Func = Function::Create(FT, Function::ExternalLinkage, "func", TheModule.get());

	BasicBlock* BB = BasicBlock::Create(*TheContext, "entry", Func);
	TheBuilder->SetInsertPoint(BB);

	TheModule->print(errs(), nullptr);

	return 0;
}

