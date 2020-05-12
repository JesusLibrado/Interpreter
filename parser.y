/********* PROLOGUE *********/
%{
    #include <stdio.h>
    #include "symbol_table.h"
    int yylex(void);
    void yyerror(char *);

    struct node *head = NULL;

%}

/********* DECLARATIONS *********/

%union{
    int var_type;
    int boolean; // 1: true | 0: false
    float number;
    char *id;
}

%token PROGRAM_TOKEN READ_TOKEN PRINT_TOKEN
%token IF_TOKEN IFELSE_TOKEN WHILE_TOKEN FOR_TOKEN TO_TOKEN DO_TOKEN STEP_TOKEN
%token SET_TOKEN VAR_TOKEN INT_TOKEN FLOAT_TOKEN
%token ADDITION_TOKEN SUBSTRACTION_TOKEN MULTIPLICATION_TOKEN DIVISION_TOKEN
%token EQUAL_TOKEN LT_TOKEN GT_TOKEN LTE_TOKEN GTE_TOKEN
%token OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET OPEN_PARENTHESIS CLOSE_PARENTHESIS SEMI_COLON_TOKEN COLON_TOKEN

%token<number> INTEGER FLOAT
%token<id> IDENTIFIER

%type<var_type> tipo
%type<number> factor expr term
%type<boolean> expression

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
    if(!find(head, $2)){
        declare_var(&head, $2, $4);
    }else 
        printf("Declaration error!: %s was already declared\n", $2);
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
    SET_TOKEN IDENTIFIER expr SEMI_COLON_TOKEN {
        if(find(head, $2)){
            assign_value(head, $2, $3);
        } else 
            printf("Assignation error!: %s does not exist\n", $2);
    }
    | READ_TOKEN IDENTIFIER SEMI_COLON_TOKEN {
        read_user_input(head, $2);
    }
    | PRINT_TOKEN expr SEMI_COLON_TOKEN {
        printf("Print: %.2f\n", $2);
    }
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
    expr ADDITION_TOKEN term        {$$ = $1 + $3;}
    | expr SUBSTRACTION_TOKEN term  {$$ = $1 - $3;}
    | term                          {$$ = $1;}
;

term:
    term MULTIPLICATION_TOKEN factor    {$$ = $1 * $3;}
    | term DIVISION_TOKEN factor        {$$ = $1 / $3;}
    | factor                            {$$ = $1;}
;

factor: 
    OPEN_PARENTHESIS expr CLOSE_PARENTHESIS {$$ = $2;}
    | IDENTIFIER                            {$$ = get_value(head, $1);}
    | INTEGER                               {$$ = $1;}
    | FLOAT                                 {$$ = $1;}
;

expression: 
    expr LT_TOKEN expr          {$$ = ($1 < $3);}
    | expr GT_TOKEN expr        {$$ = ($1 > $3);}
    | expr EQUAL_TOKEN expr     {$$ = ($1 == $3);}
    | expr LTE_TOKEN expr       {$$ = ($1 <= $3);}
    | expr GTE_TOKEN expr       {$$ = ($1 >= $3);}
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
    print_table(head);
    
    //free_table();
    return 0;
}