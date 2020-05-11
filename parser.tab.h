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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    PROGRAM_TOKEN = 258,
    READ_TOKEN = 259,
    PRINT_TOKEN = 260,
    IF_TOKEN = 261,
    IFELSE_TOKEN = 262,
    WHILE_TOKEN = 263,
    FOR_TOKEN = 264,
    TO_TOKEN = 265,
    DO_TOKEN = 266,
    STEP_TOKEN = 267,
    SET_TOKEN = 268,
    VAR_TOKEN = 269,
    INT_TOKEN = 270,
    FLOAT_TOKEN = 271,
    ADDITION_TOKEN = 272,
    SUBSTRACTION_TOKEN = 273,
    MULTIPLICATION_TOKEN = 274,
    DIVISION_TOKEN = 275,
    EQUAL_TOKEN = 276,
    LT_TOKEN = 277,
    GT_TOKEN = 278,
    LTE_TOKEN = 279,
    GTE_TOKEN = 280,
    OPEN_CURLY_BRACKET = 281,
    CLOSE_CURLY_BRACKET = 282,
    OPEN_PARENTHESIS = 283,
    CLOSE_PARENTHESIS = 284,
    SEMI_COLON_TOKEN = 285,
    INTEGER = 286,
    FLOAT = 287,
    IDENTIFIER = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 10 "parser.y" /* yacc.c:1909  */

    //int type_integer;
    //float type_float;
    float number;
    char * id;

#line 95 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
