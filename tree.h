#define DEBUG 0
#ifndef TREE_H
#define TREE_H
#include<iostream>
#include<map>
#include<vector>
#include<stdlib.h>
#include "llvm/Analysis/Passes.h"
#include "llvm/IR/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
using namespace std;
using namespace llvm;

extern map<string,string> typeTab;

class ExprAST 
{
public:
  virtual ~ExprAST() {}
  virtual string getType() = 0;
  virtual string getName() = 0;
  virtual Value *Codegen() = 0;
};

class LetExprAST : public ExprAST
{
  string Name;
  ExprAST* RHS;
public:  
  LetExprAST(const string& name, ExprAST* rhs) : Name(name), RHS(rhs) {}
  virtual string getType() { return typeTab[Name]; }
  virtual string getName() { return Name; }
  virtual Value* Codegen();
};

class IfExprAST : public ExprAST
{
  ExprAST *Cond;
  ExprAST* Then;
public:
  IfExprAST(ExprAST *cond, ExprAST* then) : Cond(cond), Then(then) {}
  virtual string getType() { return Cond->getType(); }
  virtual string getName() { return Cond->getName(); }
  virtual Value *Codegen();
};

class GotoExprAST : public ExprAST
{
  string Label;
public:
  GotoExprAST(string label) : Label(label) {}
  virtual string getType() { return "goto"; }
  virtual string getName() { return Label; }
  virtual Value* Codegen();
};

class LabelExprAST : public ExprAST
{
  string Label;
public:
  LabelExprAST(string label) : Label(label) {}
  virtual string getType() { return "label"; }
  virtual string getName() { return Label; }
  virtual Value* Codegen();
};

class IntExprAST : public ExprAST 
{
public:
  int Val;
  IntExprAST(double val) : Val(val) {}
  virtual string getType() { return "int"; }
  virtual string getName() { return "int"; }
  virtual Value *Codegen();
};

class DoubleExprAST : public ExprAST 
{
public:
  double Val;
  DoubleExprAST(double val) : Val(val) {}
  virtual string getType() { return "double"; }
  virtual string getName() { return "double"; }
  virtual Value *Codegen();
};

class stringExprAST : public ExprAST
{
public:
  const char* Val;
  double Size;
  stringExprAST(const char* val, double size, bool isPString = false) : Val(val), Size(size) {}
  virtual string getType() { return "string"; }
  virtual string getName() { string str(Val); return str; }
  virtual Value* Codegen();
};

class CharExprAST : public ExprAST
{
public:
  char Val;
  CharExprAST(char val) : Val(val) {}
  virtual string getType() { return "char"; }
  virtual string getName() { return "char"; }
  virtual Value* Codegen();
};

class VariableRefAST : public ExprAST 
{
  string Name;
public:
  VariableRefAST(const string &name) : Name(name) {}
  virtual string getName() { return Name; }
  virtual string getType() { return typeTab[Name]; }
  virtual Value *Codegen();
};

class VarInitExprAST : public ExprAST
{
  string Name;
  string Type;
public:
  VarInitExprAST(const string &name, const string &type) : Name(name), Type(type) {}
  virtual string getName() { return Name; }
  virtual string getType() { return Type; }
  virtual Value* Codegen();
};

class BinaryExprAST : public ExprAST 
{
  char Op;
  ExprAST *LHS, *RHS;
  Value* L, *R;
  string lty, rty;
  string Var;
public:
  BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs) : Op(op), LHS(lhs), RHS(rhs) {}
  BinaryExprAST(char op, const string& var, ExprAST *rhs) : Op(op), Var(var), RHS(rhs) {}
  virtual string getType() { return LHS->getType(); }
  string getLHSVar() { return dynamic_cast<VariableRefAST*>(LHS)->getName(); }
  string getRHSVar() { return dynamic_cast<VariableRefAST*>(RHS)->getName(); }
  virtual string getName() { return Var; }
  virtual Value *Codegen();
private:
  bool checkTypes();  //Checks if the types match
  void convertTypes();  //Will up/downconvert types as nessicary
  bool isPtrOp();   //Returns true if the operation involves pointers
  bool isArrayOp();
  Value* doOp();
  Value* doPtrOp();
  Value* doAssignmentOp();
};

class CallExprAST : public ExprAST 
{
  string Callee;
  vector<ExprAST*> Args;
public:
  CallExprAST(const string &callee, vector<ExprAST*> &args) : Callee(callee), Args(args) {}
  virtual string getType() { return "None"; }
  virtual string getName() { return Callee; }
  virtual Value *Codegen();
};

class PrototypeAST : public ExprAST
{
  string Name;
  vector<VarInitExprAST*> Args;
  string Ty;
public:
  PrototypeAST(const string &name, const vector<VarInitExprAST*> &args) : Name(name), Args(args) {}
  virtual string getType() { return Ty; }
  virtual string getName() { return Name; }
  Function *Codegen();
  void CreateArgumentAllocas(Function *F);
};

class FunctionAST : public ExprAST
{
  PrototypeAST *Proto;
  vector<ExprAST*> Body;
public:
  FunctionAST(PrototypeAST *proto, vector<ExprAST*> body) : Proto(proto), Body(body) {}
  virtual string getType() { return Proto->getType(); }
  virtual string getName() { return Proto->getName(); }
  
  Function *Codegen();
};

template <typename T, typename U>
class SymbolTable
{
private:
  map<T,U> _NamedValues;
  map<T,U> _GlobalValues;
public:
  SymbolTable() {}
  ~SymbolTable() {}
  typedef typename std::map<T,U>::iterator iterator;
  typedef typename std::map<T,U>::const_iterator const_iterator;
  iterator begin() { return _NamedValues.begin(); }
  const_iterator begin() const { return _NamedValues.begin(); }
  iterator end() { return _GlobalValues.end(); }
  const_iterator end() const { return _GlobalValues.end(); }
  iterator find(T key) 
  {
    if (_NamedValues.find(key) == _NamedValues.end())
      return _GlobalValues.find(key);
    else
      return _NamedValues.find(key);
  }
  void clear() { _NamedValues.clear(); }
  void clearAll() { this->clear(); _GlobalValues.clear(); }
  void addGlobal(T key, U val) { _GlobalValues[key] = val; }
  U& operator[](T key) 
  { 
    if (_NamedValues[key])
      return _NamedValues[key];
    else
      return _GlobalValues[key];
  }
  U operator[] (T key) const
  { 
    if (_NamedValues[key])
      return _NamedValues[key];
    else
      return _GlobalValues[key];
  }
  void dump()
  {
    //THIS IS HACKY. For some reason clang won't allow map<T,U>::iterator here. Gives a missing semicolon error
    map<string,Value*>::iterator it;
    cout << "\nDumping vars: \n";
    for(it=_NamedValues.begin();it!=_NamedValues.end(); it++)
    {
      cout << it->first << ": " << it->second;
      cout << "\tType: " << typeTab[it->first] << endl;
    }
    cout << "\nDumping global vars: \n";
    for(it=_GlobalValues.begin();it!=_GlobalValues.end(); it++)
    {
      cout << it->first << ": " << it->second;
      cout << "\tType: " << typeTab[it->first] << endl;
    }
  }
};

void createExtern(PrototypeAST* P);
void ERROR(string err);

#endif
