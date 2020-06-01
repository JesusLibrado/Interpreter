/********* PROLOGUE *********/
%{
    #include <stdio.h>
    #include <stdbool.h>
    #include "interpreter.h"

    extern FILE * yyin;
    extern int yylineno;
    extern char * yytext;

    int yylex(void);
    void yyerror(char *);

    struct tableNode *head = NULL;
    struct treeNode *root = NULL;

    void variable_declaration_error(char *id);
    void variable_input_error(char *id);
    void variable_operation_mismatch(char *id);


%}

/********* DECLARATIONS *********/

%union{
    int var_type;
    bool boolean;
    char *identifier;
    struct value* value;
    struct treeNode* node;
}

%token PROGRAM_TOKEN READ_TOKEN PRINT_TOKEN
%token IF_TOKEN IFELSE_TOKEN WHILE_TOKEN FOR_TOKEN TO_TOKEN DO_TOKEN STEP_TOKEN
%token SET_TOKEN VAR_TOKEN INT_TOKEN FLOAT_TOKEN
%token ADDITION_TOKEN SUBSTRACTION_TOKEN MULTIPLICATION_TOKEN DIVISION_TOKEN
%token EQUAL_TOKEN LT_TOKEN GT_TOKEN LTE_TOKEN GTE_TOKEN
%token OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET OPEN_PARENTHESIS CLOSE_PARENTHESIS SEMI_COLON_TOKEN COLON_TOKEN

%token<value> INTEGER FLOAT
%token<identifier> IDENTIFIER

%type<value> tipo
%type<node> prog stmt assign_stmt stmt_lst cmp_stmt 
%type<node> if_stmt iter_stmt
%type<node> factor expr term expression

/********* GRAMMAR RULES *********/

%start prog

%%

prog: PROGRAM_TOKEN IDENTIFIER OPEN_CURLY_BRACKET opt_decls CLOSE_CURLY_BRACKET stmt {
    root = $6;
};

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
    assign_stmt {$$ = $1;}
    | if_stmt   {$$ = $1;}
    | iter_stmt {$$ = $1;}
    | cmp_stmt  {$$ = $1;}
;

assign_stmt:
    SET_TOKEN IDENTIFIER expr SEMI_COLON_TOKEN {
        if(!variableHasBeenDeclared(head, $2)){
            variable_declaration_error($2);
            YYERROR;
        } 
        // if(!setVariableValue(head, $2, $3)){
        //     variable_input_error($2);
        //     YYERROR;
        // }
        struct treeNode * id_node = getIdNode(getVariable(head, $2));
        $$ = getSetNode(id_node, $3);
    }
    | READ_TOKEN IDENTIFIER SEMI_COLON_TOKEN {
        if(!variableHasBeenDeclared(head, $2)){
            variable_input_error($2);
            YYERROR;
        }
        struct treeNode * id_node = getIdNode(getVariable(head, $2));
        $$ = getReadNode(id_node);
        
    }
    | PRINT_TOKEN expr SEMI_COLON_TOKEN {
        $$ = getPrintNode($2);
    }
;

if_stmt: 
    IF_TOKEN OPEN_PARENTHESIS expression CLOSE_PARENTHESIS stmt    {
            $$ = getIfNode($3, reverseSyntaxTree($5));
        }
    | IFELSE_TOKEN OPEN_PARENTHESIS expression CLOSE_PARENTHESIS stmt stmt {
            $$ = getIfElseNode($3, reverseSyntaxTree($5), reverseSyntaxTree($6));
        }
;

iter_stmt: 
    WHILE_TOKEN OPEN_PARENTHESIS expression CLOSE_PARENTHESIS stmt { $$ = getWhileNode($3, $5); }
    | FOR_TOKEN SET_TOKEN IDENTIFIER expr TO_TOKEN expression STEP_TOKEN expr DO_TOKEN stmt { 
            struct treeNode * id_node = getIdNode(getVariable(head, $3));
            $$ = getForNode(id_node, $4, $6, $8, $10); 
        }
;

cmp_stmt: 
    OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET { $$ = NULL;}
    | OPEN_CURLY_BRACKET stmt_lst CLOSE_CURLY_BRACKET { $$ = $2;}
;

stmt_lst: 
    stmt            {$$ = $1;}
    | stmt_lst stmt {$2->next = $1;$$ = $2;}
;

expr: 
    expr ADDITION_TOKEN term        {
            $$ = getExprNode(ADDITION_OP, $1, $3);
        }
    | expr SUBSTRACTION_TOKEN term  {
            $$ = getExprNode(SUBSTRACTION_OP, $1, $3);
        }
    | term                          {
            $$ = $1;
        }
;

term:
    term MULTIPLICATION_TOKEN factor    {
            $$ = getTermNode(MULTIPLICATION_OP, $1, $3);
        }
    | term DIVISION_TOKEN factor        {
            $$ = $$ = getTermNode(DIVISION_OP, $1, $3);
        }
    | factor                            {$$ = $1;}
;

factor: 
    OPEN_PARENTHESIS expr CLOSE_PARENTHESIS {$$ = reverseSyntaxTree($2);}
    | IDENTIFIER                            {$$ = getIdNode(getVariable(head, $1));}
    | INTEGER                               {$$ = getValueNode($1);}
    | FLOAT                                 {$$ = getValueNode($1);}
;

expression: 
    expr LT_TOKEN expr          {
            $$ = getExpressionNode(LT_OP, $1, $3);
        }
    | expr GT_TOKEN expr        {
            $$ = getExpressionNode(GT_OP, $1, $3);
        }
    | expr EQUAL_TOKEN expr     {
            $$ = getExpressionNode(EQUAL_OP, $1, $3);
        }
    | expr LTE_TOKEN expr       {
            $$ = getExpressionNode(LTE_OP, $1, $3);
        }
    | expr GTE_TOKEN expr       {
            $$ = getExpressionNode(GTE_OP, $1, $3);
        }
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
    fprintf(stdout, "%s at line %d\n", s, yylineno);
}

int main(int argc, char **argv) {
    if ((yyin = fopen(argv[1], "r")) == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }
    int parse = yyparse();
    symbol_table = head;
    execute(reverseSyntaxTree(root));
    printf("\n");
    displaySymbolTable(symbol_table);
    //free_table();
    return 0;
}