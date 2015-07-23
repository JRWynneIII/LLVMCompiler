%{
#define VTYPE(type, value) printf("%s(%s)\n",type,value); 
#define TYPE(type) printf("%s\n",type)
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "olugLang.tab.hpp"
#include "tree.h"
using namespace std;
YY_BUFFER_STATE getCurBuf() { return YY_CURRENT_BUFFER; }
int lineNum = 1;
%}
%option noyywrap
%option header-file="lex.h"
NUMBER [0-9]+
%%
#.*$ {}
{NUMBER}(\.{NUMBER}|(\.{NUMBER})?[eE][+-]?{NUMBER}) { yylval.doubleVal = atof(yytext); return FLOAT; }
{NUMBER} { yylval.intVal = atof(yytext); return NUMBER; }
[\t ] {}
'\\n' { yylval.charVal = '\n'; return CHARACTER; }
'.' { yylval.charVal = yytext[1]; return CHARACTER; }
"begin" { return _BEGIN; }
"Begin" { return _BEGIN; }
"BEGIN" { return _BEGIN; }
"end" { return END; }
"End" { return END; }
"END" { return END; }
"extern" { return EXTERN; }
"Extern" { return EXTERN; }
"EXTERN" { return EXTERN; }
"int" { return INT; }
"double" { return DOUBLE; }
"char" { return CHAR; }
"for" { return FOR; }
"For" { return FOR; }
"FOR" { return FOR; }
"to" { return TO; }
"To" { return TO; }
"TO" { return TO; }
"next" { return NEXT; }
"Next" { return NEXT; }
"NEXT" { return NEXT; }
"var" { return VAR; }
"VAR" { return VAR; }
"Var" { return VAR; }
"CALL" { return CALL; }
"Call" { return CALL; }
"call" { return CALL; }
"let" { return LET; }
"Let" { return LET; }
"LET" { return LET; }
"if" { return IF; }
"If" { return IF; }
"IF" { return IF; }
"is" { return IS; }
"Is" { return IS; }
"IS" { return IS; }
"isnot" { return ISNOT; }
"IsNot" { return ISNOT; }
"ISNOT" { return ISNOT; }
"^" { return CAROT; }
"->" { return RARROW; }
"<-" { return LARROW; }
"=" { return EQUAL; }
"==" { return COMPEQUAL; }
">" { return GT; }
"<" { return LT; }
">=" { return GTE; }
"<=" { return LTE; }
"!=" { return NEQUAL; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MUL; }
"/" { return DIV; }
"%" { return MOD; }
"!" { return EMARK; }
"?" { return QMARK; }
"&" { return AND; }
"|" { return OR; }
"[" { return LSBRACE; }
"]" { return RSBRACE; }
"(" { return LPAREN; }
")" { return RPAREN; }
"{" { return LBRACE; }
"}" { return RBRACE; }
"@" { return AT; }
"." { return DOT; }
"," { return COMMA; }
":" { return COLON; }
";" { return SEMICOLON; }
[a-z_][a-zA-Z0-9_]* { yylval.strVal = strdup(yytext); return ID; }
\"([^"]|\\.)*\" { 
  int len = strlen(yytext);
  char st[len+1];
  int counter = 0;
  for (int i = 0; i<=len; i++)
  {
    if (yytext[i] != '"')
    { 
      st[counter] = yytext[i];
      counter++;
    }
  }
  yylval.strVal = strdup(st);
  return STRING; 
}

\n {lineNum++; }
. { fprintf(stderr, "Unknown token '%s'\n", yytext); }

