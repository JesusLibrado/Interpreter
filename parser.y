/********* PROLOGUE *********/
%{
    #include <stdio.h>
    int yylex(void);
    void yyerror(char *);
%}

/********* DECLARATIONS *********/

%union{
    //int type_integer;
    //float type_float;
    float number;
    char * id;
}

%token PROGRAM_TOKEN READ_TOKEN PRINT_TOKEN IF_TOKEN IFELSE_TOKEN WHILE_TOKEN FOR_TOKEN TO_TOKEN DO_TOKEN
%token SET_TOKEN VAR_TOKEN INT_TOKEN FLOAT_TOKEN
%token ADDITION_TOKEN SUBSTRACTION_TOKEN MULTIPLICATION_TOKEN DIVISION_TOKEN
%token EQUAL_TOKEN LT_TOKEN GT_TOKEN LTE_TOKEN GTE_TOKEN
%token OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET OPEN_PARENTHESIS CLOSE_PARENTHESIS SEMI_COLON_TOKEN

%token<number> INTEGER FLOAT
%token <id> IDENTIFIER


/********* GRAMMAR RULES *********/

%%

%%


/********* EPILOGUE *********/