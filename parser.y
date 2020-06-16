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
    struct functionNode *functions = NULL;
    struct treeNode *root = NULL;

    void variable_declaration_error(char *id);
    void variable_input_error(char *id);
    void variable_operation_mismatch(char *id);


%}

/********* DECLARATIONS *********/

%union{
    char * identifier;
    struct value * value;
    struct functionNode * _function;
    struct tableNode * symbol;
    struct treeNode * node;
}

%token PROGRAM_TOKEN READ_TOKEN PRINT_TOKEN
%token FUN_TOKEN RETURN_TOKEN
%token IF_TOKEN IFELSE_TOKEN WHILE_TOKEN FOR_TOKEN TO_TOKEN DO_TOKEN STEP_TOKEN
%token SET_TOKEN VAR_TOKEN INT_TOKEN FLOAT_TOKEN
%token ADDITION_TOKEN SUBSTRACTION_TOKEN MULTIPLICATION_TOKEN DIVISION_TOKEN
%token EQUAL_TOKEN LT_TOKEN GT_TOKEN LTE_TOKEN GTE_TOKEN
%token OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET OPEN_PARENTHESIS CLOSE_PARENTHESIS SEMI_COLON_TOKEN COLON_TOKEN COMMA_TOKEN

%token<value> INTEGER FLOAT
%token<identifier> IDENTIFIER

%type<value> tipo
%type<_function> opt_fun_decls fun_dec fun_decls
%type<symbol> opt_decls dec decls param params oparams
%type<node> stmt assign_stmt stmt_lst cmp_stmt 
%type<node> if_stmt iter_stmt
%type<node> factor expr term expression opt_exprs expr_lst

/********* GRAMMAR RULES *********/

%start prog

%%

prog: PROGRAM_TOKEN IDENTIFIER OPEN_CURLY_BRACKET opt_decls {
        head = $4;
        symbol_table = $4;
    } opt_fun_decls {
        functions = $6;
        function_table = functions;
    } CLOSE_CURLY_BRACKET stmt {
        root = $9;
};

opt_decls: 
    decls       {$$ = $1;}
    | %empty    {$$ = NULL;}
;

decls: 
    dec SEMI_COLON_TOKEN decls {
        if(variableHasBeenDeclared($1, getVariableId($3))){
            variable_declaration_error(getVariableId($3));
            YYERROR;
        }
        $1->next = $3;
        $$ = $1;
    }
    | dec {$$ = $1;}
;

dec: VAR_TOKEN IDENTIFIER COLON_TOKEN tipo {
    $$ = declareVariable($2, $4);
};

tipo: 
    INT_TOKEN       {$$ = getInteger(0);}
    | FLOAT_TOKEN   {$$ = getFloat(0.0);}
;

opt_fun_decls:
    fun_decls   {$$ = $1;}
    | %empty    {$$ = NULL;}
;

fun_decls:
    fun_decls fun_dec   {
            if(functionHasBeenDeclared($1, getFunctionId($2))){
                variable_declaration_error(getFunctionId($2));
                YYERROR;
            }
            $2->next = $1; 
            $$ = $2;
        }
    | fun_dec           {$$ = $1;}
;

fun_dec:
    FUN_TOKEN IDENTIFIER OPEN_PARENTHESIS oparams CLOSE_PARENTHESIS COLON_TOKEN tipo OPEN_CURLY_BRACKET opt_decls {
        mergeTables($4, $9);
        head = $9;
    } CLOSE_CURLY_BRACKET stmt {
        struct functionNode * new_function = declareFunction(
            $2,
            $4,
            $9,
            $7,
            reverseSyntaxTree($12)
        );
        $$ = new_function;
    }
    | FUN_TOKEN IDENTIFIER OPEN_PARENTHESIS oparams CLOSE_PARENTHESIS COLON_TOKEN tipo SEMI_COLON_TOKEN
    {
        struct functionNode * new_function = declareFunction(
            $2,
            $4,
            NULL,
            $7,
            NULL
        );
        $$ = new_function;
    }
;

oparams:
    params      {$$ = $1;}
    | %empty    {$$ = NULL;}
;

params:
    param COMMA_TOKEN params {
        if(variableHasBeenDeclared($1, getVariableId($3))){
            variable_declaration_error(getVariableId($3));
            YYERROR;
        }
        $1->next = $3;
        $$ = $1;
    }
    | param {$$ = $1;}
;

param: VAR_TOKEN IDENTIFIER COLON_TOKEN tipo {
    $$ = declareVariable($2, $4);
};

stmt: 
    assign_stmt {$$ = $1;}
    | if_stmt   {$$ = $1;}
    | iter_stmt {$$ = $1;}
    | cmp_stmt  {$$ = $1;}
;

assign_stmt:
    SET_TOKEN IDENTIFIER expr SEMI_COLON_TOKEN {
        struct tableNode * var = NULL;
        if(variableHasBeenDeclared(head, $2)){
            var = getVariable(head, $2);
        }
        else if(variableHasBeenDeclared(symbol_table, $2)){
            var = getVariable(symbol_table, $2);
        } else {
            variable_declaration_error($2);
            YYERROR;
        }
        struct treeNode * expr_node = $3;
        if(!setVariableValue(var, executeExpr(expr_node))){
            variable_input_error($2);
            YYERROR;
        }
        struct treeNode * id_node = getIdNode(var);
        $$ = getSetNode(id_node, expr_node);
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
    | RETURN_TOKEN expr {
        $$ = getReturnNode($2);
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
    OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET              {$$ = NULL;}
    | OPEN_CURLY_BRACKET stmt_lst CLOSE_CURLY_BRACKET   {$$ = $2;}
;

stmt_lst: 
    stmt            {$$ = $1;}
    | stmt_lst stmt {$2->next = $1; $$ = $2;}
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
    | IDENTIFIER                            {
            struct tableNode * var = NULL;
            if(variableHasBeenDeclared(head, $1)){
                var = getVariable(head, $1);
            }
            else if(variableHasBeenDeclared(symbol_table, $1)){
                var = getVariable(symbol_table, $1);
            } else {
                variable_declaration_error($1);
                YYERROR;
            }
            $$ = getIdNode(var);
        }
    | INTEGER                               {$$ = getValueNode($1);}
    | FLOAT                                 {$$ = getValueNode($1);}
    | IDENTIFIER OPEN_PARENTHESIS opt_exprs CLOSE_PARENTHESIS {
        if(!functionHasBeenDeclared(function_table, $1)){
            variable_declaration_error($1);
            YYERROR;
        }
        $$ = getFunctionNode(getFunction(function_table, $1), $3);
    }
; 

opt_exprs: 
    expr_lst {$$ = reverseSyntaxTree($1);} 
    | %empty {$$ = NULL;}
;

expr_lst: 
    expr_lst COMMA_TOKEN expr   {$3->next = $1; $$ = $3;}
    | expr                      {$$ = $1;}
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
    printf("Error: %s type mismatch\n", id);
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
    syntax_tree = reverseSyntaxTree(root);
    // printf("\n------- Function Table ---------\n");
    // displayFunctionTable(function_table);
    printf("\n----- Execute Syntax Tree ------\n");
    printSyntaxTree(syntax_tree);
    //execute(syntax_tree);
    printf("\n\t-------- Final Symbol Table ---------\n");
    displaySymbolTable(symbol_table);
    if(argv[2]){
        if(strcmp(argv[2], "--print-tree")==0){
            printf("\n----- Reduced Syntax Tree ------\n");
            printSyntaxTree(syntax_tree);
        }
    }
    //free_table();
    return 0;
}