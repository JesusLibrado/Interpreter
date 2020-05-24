%{
    #include <stdlib.h>
    #include <string.h>
    #include "parser.tab.h"
    #include "value.h"

    

%}

/******* CONSTANTS *******/
digit [0-9]
alpha [a-zA-Z]

/********* RULES *********/
%%

[[:space:]]+

"program"						{return PROGRAM_TOKEN;}
"set"							{return SET_TOKEN;}
"var"							{return VAR_TOKEN;}
"int"							{return INT_TOKEN;}
"float"							{return FLOAT_TOKEN;}
"read"							{return READ_TOKEN;}
"print"							{return PRINT_TOKEN;}
"if"							{return IF_TOKEN;}
"ifelse"						{return IFELSE_TOKEN;}
"while"							{return WHILE_TOKEN;}
"for"							{return FOR_TOKEN;}
"step"							{return STEP_TOKEN;}
"to"							{return TO_TOKEN;}
"do"							{return DO_TOKEN;}
"+"								{return ADDITION_TOKEN;}
"-"								{return SUBSTRACTION_TOKEN;}
"*"								{return MULTIPLICATION_TOKEN;}
"/"								{return DIVISION_TOKEN;}
"="								{return EQUAL_TOKEN;}
"<"								{return LT_TOKEN;}
"<="							{return LTE_TOKEN;}
">"								{return GT_TOKEN;}
">="							{return GTE_TOKEN;}
"{"								{return OPEN_CURLY_BRACKET;}
"}"								{return CLOSE_CURLY_BRACKET;}
"("								{return OPEN_PARENTHESIS;}
")"								{return CLOSE_PARENTHESIS;}
";"                             {return SEMI_COLON_TOKEN;}	
":"                             {return COLON_TOKEN;}	

{alpha}+                        {yylval.id = strdup(yytext); /*printf("Identifier: %s\n", yytext);*/ return IDENTIFIER;}

{digit}+                        {yylval.number = atof(yytext); /*printf("Integer: %s\n", yytext);*/ return INTEGER;}
{digit}+.{digit}+               {yylval.number = atof(yytext); /*printf("Float: %s\n", yytext);*/ return FLOAT;}


%%

int yywrap(void) {}