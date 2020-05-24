%{
    #include <stdlib.h>
    #include <string.h>
    #include "value.h"
    #include "parser.tab.h"

    int integer_value(int);
    int float_value(int);
    int identifier_value(int);

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

{alpha}+                        {return identifier_value(IDENTIFIER);}

{digit}+                        {return integer_value(INTEGER);}
{digit}+.{digit}+               {return float_value(FLOAT);}


%%

int integer_value(int token) {
    yylval.value = getInteger(atoi(yytext));
    return token;
}
int float_value(int token) {
    yylval.value = getFloat(atof(yytext));
    return token;
}
int identifier_value(int token) {
    yylval.identifier = strdup(yytext);
    return token;
}

int yywrap(void) {}