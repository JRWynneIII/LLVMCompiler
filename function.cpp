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

Function* FunctionAST::Codegen()
{
  Function* F = Proto->Codegen();
  if(!F)
    return 0;

  BasicBlock* BB = BasicBlock::Create(getGlobalContext(), "entry", F);
  Builder.SetInsertPoint(BB);

  Proto->CreateArgumentAllocas(F);

  Value* last;
  for(auto i : Body)
  {
    last = i->Codegen();
    if(!last)
      break;
  }
  if(last)
  {
    Builder.CreateRet(last);
    verifyFunction(*F);
    symbols.clear();
    return F;
  }
  //Erase the function if theres an error
  //theModule->dump();
  F->eraseFromParent();
  ERROR("Invalid Function Definition");
  return 0;
}

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

Type *typeOf(VarInitExprAST* type) 
{
  if (type->getType() == "int") 
  {
    return Type::getInt32Ty(getGlobalContext());
  }
  else if (type->getType() == "double") 
  {
    return Type::getDoubleTy(getGlobalContext());
  }
  else if (type->getType() == "char") 
  {
    return Type::getInt8Ty(getGlobalContext());
  }
  return 0;
}


Function* PrototypeAST::Codegen()
{
  vector<Type*> argTypes;
  for(auto i : Args)
    argTypes.push_back(typeOf(i));
  FunctionType* FT;
  Function* F;
  if(Args.empty())
    FT = FunctionType::get(Builder.getInt32Ty(),false);
  else
    FT = FunctionType::get(Builder.getInt32Ty(),makeArrayRef(argTypes),false);

  F = Function::Create(FT, Function::ExternalLinkage, Name, theModule);
  if(F->getName() != Name)
  {
    F->eraseFromParent();
    F = theModule->getFunction(Name);
    if(!F->empty())
      ERROR("Redefinition of Function: " + Name);
    if(F->arg_size() != Args.size())
      ERROR("Incorrect number of arguments for Function: " + Name);
  }
  unsigned Idx = 0;
  if (!Args.empty())
  {
    for (Function::arg_iterator AI = F->arg_begin(); Idx != Args.size(); ++AI, ++Idx)
      AI->setName(Args[Idx]->getName());
  }
  return F;

}

void PrototypeAST::CreateArgumentAllocas(Function *F)
{
  Function::arg_iterator AI = F->arg_begin();
  for(unsigned Idx = 0, e = Args.size(); Idx !=e; ++Idx, ++AI)
  {
    AllocaInst* Alloca = CreateEntryBlockAlloca(Args[Idx]->getName(), Args[Idx]->getType());
    Builder.CreateStore(AI,Alloca);
    symbols[Args[Idx]->getName()] = Alloca;
    typeTab[Args[Idx]->getName()] = Args[Idx]->getType();
  }
}

Value* CallExprAST::Codegen()
{
  Function* CalleeF = theModule->getFunction(Callee);
  if (CalleeF == 0)
    ERROR("Unknown Function Reference: " + Callee);
  if (CalleeF->arg_size() != Args.size())
    ERROR("Incorrect number of arguments: " + Callee);
  vector<Value*> ArgsV;
  for(auto i : Args)
  {
    ArgsV.push_back(i->Codegen());
    if (ArgsV.back() == 0)
      return 0;
  }
  return Builder.CreateCall(CalleeF,ArgsV,"call");
}
