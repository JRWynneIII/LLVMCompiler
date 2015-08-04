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

Value* ForExprAST::Codegen()
{
  Function *TheFunction = Builder.GetInsertBlock()->getParent();
  BasicBlock *PreheaderBB = Builder.GetInsertBlock();
  // Get alloca for the variable in the entry block.
  string Ty = Start->getType();
  string VarName = dynamic_cast<VariableRefAST*>(Start)->getName();
  Value *Alloca;
  if(symbols.find(VarName) == symbols.end())
    ERROR("Value must be defined before being used as a loop induction variable!");
  Alloca = symbols[VarName];
  Value* StartVal = dynamic_cast<VariableRefAST*>(Start)->Codegen();

  BasicBlock *LoopBB = BasicBlock::Create(getGlobalContext(), "loop", TheFunction);

  // Insert an explicit fall through from the current block to the LoopBB.
  Builder.CreateBr(LoopBB);
  Builder.SetInsertPoint(LoopBB);
  PHINode *Variable;

  Variable = Builder.CreatePHI(Type::getInt32Ty(getGlobalContext()), 2, VarName.c_str());
  Variable->addIncoming(StartVal, PreheaderBB);

  Value *EndCond = End->Codegen();
  if (EndCond == 0)
    return EndCond;


  Value *StepVal = ConstantInt::get(Type::getInt32Ty(getGlobalContext()), 1);

  Value *CurVar = Builder.CreateLoad(Alloca, VarName.c_str());
  //if (typeTab[VarName] != "int")
    Builder.CreateFPToSI(CurVar, Type::getInt32Ty(getGlobalContext())); 
  Value *NextVar = Builder.CreateAdd(CurVar, StepVal, "nextvar");

  if (Ty != "int")
    EndCond = Builder.CreateFPToSI(EndCond,Type::getInt32Ty(getGlobalContext()));
  EndCond = Builder.CreateICmpSLT(CurVar, EndCond, "loopcond");

  vector<ExprAST*>::iterator it = Body.begin();
  for(it = Body.begin(); it != Body.end(); it++)
  {
    if((*it)->Codegen() == 0)
      return 0;
  }

  Builder.CreateStore(NextVar, Alloca);

  BasicBlock *LoopEnd = Builder.GetInsertBlock();
  BasicBlock *AfterBB = BasicBlock::Create(getGlobalContext(), "afterloop", TheFunction);
  Builder.CreateCondBr(EndCond, LoopBB, AfterBB);
  Builder.SetInsertPoint(AfterBB);
  Variable->addIncoming(NextVar,LoopEnd);

  return Constant::getNullValue(Type::getDoubleTy(getGlobalContext()));
}

Value* IfExprAST::Codegen()
{
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
