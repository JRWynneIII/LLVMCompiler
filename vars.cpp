#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
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
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "olugLang.tab.hpp"
using namespace std;
using namespace llvm;

extern IRBuilder<> Builder;
extern Module* theModule;
extern SymbolTable<string,Value*> symbols;
extern map<string,string> typeTab;

static AllocaInst *CreateEntryBlockAlloca(const string &VarName, string type) 
{
  if (type == "double")
    return Builder.CreateAlloca(Type::getDoubleTy(getGlobalContext()), 0, VarName.c_str());
  else if (type == "int")
    return Builder.CreateAlloca(Type::getInt32Ty(getGlobalContext()), 0, VarName.c_str());
  else if (type == "char")
    return Builder.CreateAlloca(Type::getInt8Ty(getGlobalContext()), 0, VarName.c_str());
  return 0;
}

Value* VariableRefAST::Codegen()
{
  Value* V = symbols[Name];
  if(!V)
    ERROR("Unknown variable reference: " + Name);
  return Builder.CreateLoad(V,Name);
}

Value* VarInitExprAST::Codegen()
{
  if(symbols.find(Name) == symbols.end())
  {
    AllocaInst* Alloca;
    Function* F = Builder.GetInsertBlock()->getParent();
    Value* Initial;
    typeTab[Name] = Type;
    Alloca = CreateEntryBlockAlloca(Name,Type);
    if(!Alloca)
      ERROR("Invalid type for: " + Name);
    symbols[Name] = Alloca;
    return Alloca;
  }
  else
    ERROR("Variable already exists: " + Name);
}
