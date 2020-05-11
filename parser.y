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

%token PROGRAM_TOKEN READ_TOKEN PRINT_TOKEN IF_TOKEN IFELSE_TOKEN WHILE_TOKEN FOR_TOKEN TO_TOKEN DO_TOKEN STEP_TOKEN
%token SET_TOKEN VAR_TOKEN INT_TOKEN FLOAT_TOKEN
%token ADDITION_TOKEN SUBSTRACTION_TOKEN MULTIPLICATION_TOKEN DIVISION_TOKEN
%token EQUAL_TOKEN LT_TOKEN GT_TOKEN LTE_TOKEN GTE_TOKEN
%token OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET OPEN_PARENTHESIS CLOSE_PARENTHESIS SEMI_COLON_TOKEN

%token<number> INTEGER FLOAT
%token <id> IDENTIFIER


/********* GRAMMAR RULES *********/

%%

prog: PROGRAM_TOKEN IDENTIFIER '{' opt_decls '}' stmt;

opt_decls: 
    decls
    | %empty
;

decls: 
    decls SEMI_COLON_TOKEN decls 
    | dec
;

dec: VAR_TOKEN IDENTIFIER ':' tipo;

tipo: INT_TOKEN | FLOAT_TOKEN;

stmt: 
    assign_stmt
    | if_stmt
    | iter_stmt
    | cmp_stmt
;

assign_stmt:
    SET_TOKEN IDENTIFIER expr ';'
    | READ_TOKEN IDENTIFIER
    | PRINT_TOKEN expr
;

if_stmt: 
    IF_TOKEN '(' expression ')' stmt
    | IFELSE_TOKEN '(' expression ')' stmt stmt
;

iter_stmt: 
    WHILE_TOKEN '(' expression ')' stmt
    | FOR_TOKEN SET_TOKEN IDENTIFIER expr TO_TOKEN expr STEP_TOKEN expr DO_TOKEN stmt
;

cmp_stmt: 
    '{' '}'
    | '{' stmt_lst '}'
;

stmt_lst: 
    stmt
    | stmt_lst stmt
;

expr: 
    expr ADDITION_TOKEN term
    | expr SUBSTRACTION_TOKEN term
    | term
;

term:
    term MULTIPLICATION_TOKEN factor
    | term DIVISION_TOKEN factor
    | factor
;

factor: 
    '(' expr ')'
    | IDENTIFIER 
    | INTEGER 
    | FLOAT
;

expression: 
    expr LT_TOKEN expr
    | expr GT_TOKEN expr
    | expr EQUAL_TOKEN expr
    | expr LTE_TOKEN expr
    | expr GTE_TOKEN expr
;

%%


/********* EPILOGUE *********/