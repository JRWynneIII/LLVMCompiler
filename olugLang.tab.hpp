/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_OLUGLANG_TAB_HPP_INCLUDED
# define YY_YY_OLUGLANG_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 22 "olugLang.ypp" /* yacc.c:1909  */

#include "tree.h"

#line 48 "olugLang.tab.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    FLOAT = 259,
    IS = 260,
    ISNOT = 261,
    ID = 262,
    END = 263,
    CHARACTER = 264,
    STRING = 265,
    _BEGIN = 266,
    EXTERN = 267,
    LABEL = 268,
    GOTO = 269,
    VAR = 270,
    CALL = 271,
    IF = 272,
    INT = 273,
    DOUBLE = 274,
    CHAR = 275,
    RARROW = 276,
    LARROW = 277,
    CAROT = 278,
    EQUAL = 279,
    COMPEQUAL = 280,
    GT = 281,
    LT = 282,
    GTE = 283,
    LTE = 284,
    NEQUAL = 285,
    PLUS = 286,
    MINUS = 287,
    MUL = 288,
    DIV = 289,
    MOD = 290,
    EMARK = 291,
    QMARK = 292,
    AND = 293,
    OR = 294,
    LSBRACE = 295,
    RSBRACE = 296,
    LPAREN = 297,
    RPAREN = 298,
    LBRACE = 299,
    RBRACE = 300,
    AT = 301,
    DOT = 302,
    COMMA = 303,
    COLON = 304,
    SEMICOLON = 305
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 30 "olugLang.ypp" /* yacc.c:1909  */

  int intVal;
  char charVal;
  double doubleVal;
  const char* strVal;
  VarInitExprAST* varInit;
  FunctionAST* fdef;
  PrototypeAST* proto;
  CallExprAST* functionCall;
  IfExprAST* _if;
  BinaryExprAST* bo;
  DoubleExprAST* dval;
  IntExprAST* ival;
  ExprAST* expr;
  CharExprAST* charAST;
  std::vector<ExprAST*>* blk;
  std::vector<FunctionAST*>* funcBlk;
  std::vector<VarInitExprAST*>* varBlk;

#line 131 "olugLang.tab.hpp" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_OLUGLANG_TAB_HPP_INCLUDED  */
