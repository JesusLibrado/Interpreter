/********* PROLOGUE *********/
%{
    #include <stdio.h>
    #include "symbol_table.h"
    int yylex(void);
    void yyerror(char *);
%}

/********* DECLARATIONS *********/

%union{
    int var_type;
    int int_val;
    float float_val;
    char id[20];
}

%token PROGRAM_TOKEN READ_TOKEN PRINT_TOKEN
%token IF_TOKEN IFELSE_TOKEN WHILE_TOKEN FOR_TOKEN TO_TOKEN DO_TOKEN STEP_TOKEN
%token SET_TOKEN VAR_TOKEN INT_TOKEN FLOAT_TOKEN
%token ADDITION_TOKEN SUBSTRACTION_TOKEN MULTIPLICATION_TOKEN DIVISION_TOKEN
%token EQUAL_TOKEN LT_TOKEN GT_TOKEN LTE_TOKEN GTE_TOKEN
%token OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET OPEN_PARENTHESIS CLOSE_PARENTHESIS SEMI_COLON_TOKEN COLON_TOKEN

%token<int_val> INTEGER
%token<float_val> FLOAT
%token<id> IDENTIFIER

%type<var_type> tipo

/********* GRAMMAR RULES *********/

%start prog

%%

prog: PROGRAM_TOKEN IDENTIFIER OPEN_CURLY_BRACKET opt_decls CLOSE_CURLY_BRACKET stmt;

opt_decls: 
    decls
    | %empty
;

decls: 
    dec SEMI_COLON_TOKEN decls 
    | dec
;

dec: VAR_TOKEN IDENTIFIER COLON_TOKEN tipo {
    if(!is_declared($2))
        declare_var($2, $4);
    else
        printf("Variable was already declared\n");
};

tipo: 
    INT_TOKEN       {$$ = 1;}
    | FLOAT_TOKEN   {$$ = 2;}
;

stmt: 
    assign_stmt
    | if_stmt
    | iter_stmt
    | cmp_stmt
;

assign_stmt:
    SET_TOKEN IDENTIFIER expr SEMI_COLON_TOKEN
    | READ_TOKEN IDENTIFIER
    | PRINT_TOKEN expr
;

if_stmt: 
    IF_TOKEN OPEN_PARENTHESIS expression CLOSE_PARENTHESIS stmt
    | IFELSE_TOKEN OPEN_PARENTHESIS expression CLOSE_PARENTHESIS stmt stmt
;

iter_stmt: 
    WHILE_TOKEN OPEN_PARENTHESIS expression CLOSE_PARENTHESIS stmt
    | FOR_TOKEN SET_TOKEN IDENTIFIER expr TO_TOKEN expr STEP_TOKEN expr DO_TOKEN stmt
;

cmp_stmt: 
    OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET
    | OPEN_CURLY_BRACKET stmt_lst CLOSE_CURLY_BRACKET
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
    OPEN_PARENTHESIS expr CLOSE_PARENTHESIS
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

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(int argc, char **argv) {
    if(argc >= 2) {
	    freopen(argv[1], "r", stdin);
	}
    yyparse();
    //print_table();
    free_table();
    return 0;
}