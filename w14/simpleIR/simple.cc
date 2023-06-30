#include "llvm/ADT/APInt.h"
#include "llvm/IR/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;

static Function *CreateFibFunction(Module *M, LLVMContext &Context) {
	return nullptr;
}

int main(int argc, char** argv) {
	int n = argc > 1? atol(argv[1]) : 24;

	InitializeNativeTarget();
	InitializeNativeTargetAsmPrinter();
	LLVMContext Context;

	std::unique_ptr<Module> Owner(new Module("test", Context));
	Module *M = Owner.get();

	Function *FibF = CreateFibFunction(M, Context);

	std::string errStr;
	ExecutionEngine *EE = EngineBuilder(std::move(Owner))
		.setErrorStr(&errStr)
		.create();

	if (!EE) {
		errs() << argv[0] << ": Failed to construct ExecutionEngine: " << errStr
			<< "\n";
		return 1;
	}

	errs() << "verifiying... ";
	if (verifyModule(*M)) {
		errs() << argv[0] << ": Error constructing function!\n";
		return 1;
	}

	errs() << "OK\n";
	errs() << "Fibonacci => " << n << "\n";

	std::vector<GenericValue> Args(1);
	Args[0].IntVal = APInt(32, n);
	GenericValue GV = EE->runFunction(FibF, Args);

	outs() << "Result: " << GV.IntVal << "\n";

	return 0;
}
