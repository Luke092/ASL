/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ASSIGN = 258,
    EQUAL = 259,
    NE = 260,
    GT = 261,
    GE = 262,
    KT = 263,
    KE = 264,
    PLUS = 265,
    MINUS = 266,
    MUL = 267,
    DIV = 268,
    PROGRAM = 269,
    TYPE = 270,
    VAR = 271,
    CONST = 272,
    PROC = 273,
    FUNC = 274,
    IN = 275,
    OUT = 276,
    INOUT = 277,
    T_BEGIN = 278,
    END = 279,
    BREAK = 280,
    EXIT = 281,
    IF = 282,
    THEN = 283,
    ELSE = 284,
    ELSIF = 285,
    WHILE = 286,
    DO = 287,
    REPEAT = 288,
    UNTIL = 289,
    FOR = 290,
    TO = 291,
    INPUT = 292,
    OUTPUT = 293,
    AND = 294,
    OR = 295,
    NOT = 296,
    INTEGER = 297,
    STRING = 298,
    BOOLEAN = 299,
    INTCONST = 300,
    BOOLCONST = 301,
    STRCONST = 302,
    ID = 303,
    ERROR = 304,
    ARRAY = 305,
    OF = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
