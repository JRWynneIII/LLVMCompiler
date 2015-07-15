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

Value* BinaryExprAST::Codegen()
{
  Value* L = LHS->Codegen();
  Value* R = RHS->Codegen();
  bool isInt = true;
  if(!L || !R)
    return 0;
  string lty = LHS->getType();
  string rty = RHS->getType();
  if(lty != rty)
    ERROR("Types do not match: " + RHS->getName() + " " + LHS->getName());
  if(lty == "double")
    isInt = false;
  switch(Op)
  {
    case '+':
      if(!isInt)
        return Builder.CreateFAdd(L, R, "addVal");
      else
        return Builder.CreateAdd(L,R,"addVal");
    case '-':
      if(!isInt)
        return Builder.CreateFSub(L, R, "subVal");
      else
        return Builder.CreateSub(L,R,"subVal");
    case '*':
      if(!isInt)
        return Builder.CreateFMul(L, R, "mulVal");
      else
        return Builder.CreateMul(L,R,"mulVal");
    case '/':
      if(!isInt)
        return Builder.CreateFDiv(L, R, "divVal");
      else
        return Builder.CreateUDiv(L,R,"divVal");
    default:
      break;
  }
  return 0;
}

Value* LetExprAST::Codegen()
{
  VariableRefAST* LHS = new VariableRefAST(Name);
  Value* lhs = LHS->Codegen();
  if(!lhs)
   ERROR("lvalue must be a variable!");
  Value* rhs = RHS->Codegen();
  if(!rhs)
    ERROR("Invalid rvalue for assignment op!");  
  Value* Alloca = symbols[Name];
  if(!Alloca)
    ERROR("Variable not declared: " + Name);
  return Builder.CreateStore(rhs,Alloca);
}
