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

IRBuilder<> Builder(getGlobalContext());
Module* theModule;
SymbolTable<string,Value*> symbols;
map<string,string> typeTab;
extern vector<ExprAST*> funcLines;
extern FILE* yyin;
extern FunctionPassManager* theFPM;

int main(int argc, char* argv[])
{
  LLVMContext &Context = getGlobalContext();
  theModule = new Module("olangc", Context);
  string name = "olangc";

  if (argc > 1)
  {
    yyin = fopen(argv[1],"r");
    name = argv[1];
  }
  yyparse();

  for(auto i : funcLines)
  {
    Value* cur = i->Codegen();
    if(!cur)
      ERROR("Error reading the AST!!");
  }

  legacy::FunctionPassManager opt(theModule);
 // opt.add(createAggressiveDCEPass());
 // opt.add(createBasicAliasAnalysisPass());
 // opt.add(createPromoteMemoryToRegisterPass());
 // opt.add(createInstructionCombiningPass());
 // opt.add(createReassociatePass());
 // opt.add(createGVNPass());
 // opt.add(createCFGSimplificationPass());
 // opt.add(createVerifierPass());
  opt.doInitialization();
  for (Module::iterator it = theModule->begin(); it != theModule->end(); ++it)
    opt.run(*it);
  opt.doFinalization();
  theModule->dump();
  //Write to the file
  string Errors, ErrorCatch;
  string outFile(argv[1]);
  outFile += ".ll";
  system(string("touch " + outFile).c_str());
  int fd = open(outFile.c_str(), O_RDWR | O_TRUNC | O_CREAT);
  if (fd <= 0)
  {
    cerr << "FILE NOT OPENED\nfd = " << fd << endl;
    exit(EXIT_FAILURE);
  }
  raw_fd_ostream bcFile(fd, false);
  WriteBitcodeToFile(theModule,bcFile);
  fflush(stdout);
}
