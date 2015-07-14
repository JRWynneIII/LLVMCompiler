#include<iostream>
#include<fstream>
#include "llvm/Analysis/Passes.h"
#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/ADT/StringRef.h"
#include <cctype>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include<stdio.h>
#include<stdlib.h>
#include "tree.h"
#include "olugLang.tab.hpp"
using namespace std;
using namespace llvm;

void ERROR(string err)
{
  cerr << "\033[31m ERROR: \033[37m " << err << endl;
  exit(EXIT_FAILURE);
}

void createExtern(PrototypeAST* P)
{
  Function* func = P->Codegen();
  if(!func)
  {
    ERROR("Error in declaring extern");
  }
}
