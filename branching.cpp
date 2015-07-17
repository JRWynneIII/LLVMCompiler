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
map<string,BasicBlock*> blocks;

Value* GotoExprAST::Codegen()
{
  BasicBlock* block = blocks[Label];
  return Builder.CreateBr(block);
}

Value* LabelExprAST::Codegen()
{
  BasicBlock* newBlock = BasicBlock::Create(getGlobalContext(),Label,Builder.GetInsertBlock()->getParent());
  blocks[Label] = newBlock;
  Builder.SetInsertPoint(newBlock);
  return Constant::getNullValue(Type::getDoubleTy(getGlobalContext()));
}

Value* IfExprAST::Codegen()
{
  cout << "DO THE THING\n";
  Value* CondV = Cond->Codegen();
  if(!CondV)
    return 0;
  string ty = Cond->getType();
  if(ty == "double")
    Builder.CreateFCmpONE(CondV, ConstantFP::get(getGlobalContext(),APFloat(0.0)), "ifcond");
  else if(ty == "int")
    Builder.CreateICmpNE(CondV,ConstantInt::get(Type::getInt32Ty(getGlobalContext()),0),"ifcond");
  else
    ERROR("Invalid type in if statement");

  Function* F = Builder.GetInsertBlock()->getParent();
  BasicBlock* Entry = Builder.GetInsertBlock();

  BasicBlock* thenBlock = BasicBlock::Create(getGlobalContext(), "then", F);
  BasicBlock* mergeBlock = BasicBlock::Create(getGlobalContext(), "ifcont");

  if (ty == "double")
    CondV = Builder.CreateFPToSI(CondV, Type::getInt32Ty(getGlobalContext()));
  Value* sCond = Builder.CreateSExtOrTrunc(CondV, Type::getInt1Ty(getGlobalContext()));
  Builder.CreateCondBr(sCond, thenBlock, mergeBlock);
  Builder.SetInsertPoint(thenBlock);

  Value* Tlast = Then->Codegen();

  Builder.CreateBr(mergeBlock);
  thenBlock = Builder.GetInsertBlock();
  F->getBasicBlockList().push_back(mergeBlock);
  Builder.SetInsertPoint(mergeBlock);
  return Constant::getNullValue(Type::getDoubleTy(getGlobalContext()));
}
