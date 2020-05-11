%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "parser.tab.h"

    void syntaxError();
%}

/******* CONSTANTS *******/
digit [0-9]
alpha [a-zA-Z]
alphanumeric [A-Za-z0-9]

/********* RULES *********/
%%

"program"						{printf("Terminal: %s\n", yytext);return PROGRAM_TOKEN;}
"set"							{printf("Terminal: %s\n", yytext);return SET_TOKEN;}
"var"							{printf("Terminal: %s\n", yytext);return VAR_TOKEN;}
"int"							{printf("Terminal: %s\n", yytext);return INT_TOKEN;}
"float"							{printf("Terminal: %s\n", yytext);return FLOAT_TOKEN;}
"read"							{printf("Terminal: %s\n", yytext);return READ_TOKEN;}
"print"							{printf("Terminal: %s\n", yytext);return PRINT_TOKEN;}
"if"							{printf("Terminal: %s\n", yytext);return IF_TOKEN;}
"ifelse"						{printf("Terminal: %s\n", yytext);return IFELSE_TOKEN;}
"while"							{printf("Terminal: %s\n", yytext);return WHILE_TOKEN;}
"for"							{printf("Terminal: %s\n", yytext);return FOR_TOKEN;}
"to"							{printf("Terminal: %s\n", yytext);return TO_TOKEN;}
"do"							{printf("Terminal: %s\n", yytext);return DO_TOKEN;}
"+"								{printf("Terminal: %s\n", yytext);return ADDITION_TOKEN;}
"-"								{printf("Terminal: %s\n", yytext);return SUBSTRACTION_TOKEN;}
"*"								{printf("Terminal: %s\n", yytext);return MULTIPLICATION_TOKEN;}
"/"								{printf("Terminal: %s\n", yytext);return DIVISION_TOKEN;}
"="								{printf("Terminal: %s\n", yytext);return EQUAL_TOKEN;}
"<"								{printf("Terminal: %s\n", yytext);return LT_TOKEN;}
"<="							{printf("Terminal: %s\n", yytext);return LTE_TOKEN;}
">"								{printf("Terminal: %s\n", yytext);return GT_TOKEN;}
">="							{printf("Terminal: %s\n", yytext);return GTE_TOKEN;}
"{"								{printf("Terminal: %s\n", yytext);return OPEN_CURLY_BRACKET;}
"}"								{printf("Terminal: %s\n", yytext);return CLOSE_CURLY_BRACKET;}
"("								{printf("Terminal: %s\n", yytext);return OPEN_PARENTHESIS;}
")"								{printf("Terminal: %s\n", yytext);return CLOSE_PARENTHESIS;}
";"                             {printf("Terminal: %s\n", yytext);return SEMI_COLON_TOKEN;}	

{alpha}+{alphanumeric}*         {sscanf(yytext, "%s", yylval.id); return IDENTIFIER;}

{digit}+                        {yylval.number = atoi(yytext); return INTEGER;}
{digit}+"."{digit}+             {yylval.number = atoi(yytext); return FLOAT;}

.                               {syntaxError(); return OTHER;}

%%

void syntaxError(){
    printf("Syntax error (text=%s) at line: %d\n", yytext, yylineno);
}

int yywrap(void) {}