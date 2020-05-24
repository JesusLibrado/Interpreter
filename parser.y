/********* PROLOGUE *********/
%{
    #include <stdio.h>
    #include <stdbool.h>
    #include "value.h"
    #include "symbol_table.h"
    int yylex(void);
    void yyerror(char *);

    struct tableNode *head = NULL;

    void variable_declaration_error(char *id);
    void variable_input_error(char *id);
    void variable_operation_mismatch(char *id);

%}

/********* DECLARATIONS *********/

%union{
    int var_type;
    bool boolean;
    char *identifier;
    struct variableValue* value;
}

%token PROGRAM_TOKEN READ_TOKEN PRINT_TOKEN
%token IF_TOKEN IFELSE_TOKEN WHILE_TOKEN FOR_TOKEN TO_TOKEN DO_TOKEN STEP_TOKEN
%token SET_TOKEN VAR_TOKEN INT_TOKEN FLOAT_TOKEN
%token ADDITION_TOKEN SUBSTRACTION_TOKEN MULTIPLICATION_TOKEN DIVISION_TOKEN
%token EQUAL_TOKEN LT_TOKEN GT_TOKEN LTE_TOKEN GTE_TOKEN
%token OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET OPEN_PARENTHESIS CLOSE_PARENTHESIS SEMI_COLON_TOKEN COLON_TOKEN

%token<value> INTEGER FLOAT
%token<identifier> IDENTIFIER

%type<value> factor expr term tipo
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
    if(!variableHasBeenDeclared(head, $2)){
        declareVariable(&head, $2, $4); 
    }else {
        variable_declaration_error($2);
        YYERROR;
    }
};

tipo: 
    INT_TOKEN       {$$ = getInteger(0);}
    | FLOAT_TOKEN   {$$ = getFloat(0.0);}
;

stmt: 
    assign_stmt
    | if_stmt
    | iter_stmt
    | cmp_stmt
;

assign_stmt:
    SET_TOKEN IDENTIFIER expr SEMI_COLON_TOKEN {
        if(!variableHasBeenDeclared(head, $2)){
            variable_declaration_error($2);
            YYERROR;
        } 
        if(!setVariableValue(head, $2, $3)){
            variable_input_error($2);
            YYERROR;
        }
        
    }
    | READ_TOKEN IDENTIFIER SEMI_COLON_TOKEN {
        printf("Reading something\n");
    }
    | PRINT_TOKEN expr SEMI_COLON_TOKEN {
        printValue($2);
        printf("\n");
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
    expr ADDITION_TOKEN term        {$$ = valueOperation($1, $3, ADDITION_OP);}
    | expr SUBSTRACTION_TOKEN term  {$$ = valueOperation($1, $3, SUBSTRACTION_OP);}
    | term                          {$$ = $1;}
;

term:
    term MULTIPLICATION_TOKEN factor    {$$ = valueOperation($1, $3, MULTIPLICATION_OP);}
    | term DIVISION_TOKEN factor        {$$ = valueOperation($1, $3, DIVISION_OP);}
    | factor                            {$$ = $1;}
;

factor: 
    OPEN_PARENTHESIS expr CLOSE_PARENTHESIS {$$ = $2;}
    | IDENTIFIER                            {$$ = getVariableValue(head, $1);}
    | INTEGER                               {$$ = $1;}
    | FLOAT                                 {$$ = $1;}
;

expression: 
    expr LT_TOKEN expr          {$$ = valueEvaluation($1, $3, LT_OP);}
    | expr GT_TOKEN expr        {$$ = valueEvaluation($1, $3, GT_OP);}
    | expr EQUAL_TOKEN expr     {$$ = valueEvaluation($1, $3, EQUAL_OP);}
    | expr LTE_TOKEN expr       {$$ = valueEvaluation($1, $3, LTE_OP);}
    | expr GTE_TOKEN expr       {$$ = valueEvaluation($1, $3, GTE_OP);}
;

%%


/********* EPILOGUE *********/

void variable_declaration_error(char *id){
    printf("Error: %s was already declared or was not found\n", id);
    
}
void variable_input_error(char *id){
    printf("Error: %s input mismatch\n", id);
    
}

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(int argc, char **argv) {
    if(argc >= 2) {
	    freopen(argv[1], "r", stdin);
	}
    int parse = yyparse();
    displaySymbolTable(head);
    
    //free_table();
    return 0;
}