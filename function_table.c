#include "function_table.h"

struct functionNode * declareFunction( 
    char * id, 
    struct tableNode * params,
    struct tableNode * scope,
    struct value * returnValue,
    struct treeNode * body
){
    struct functionNode * new_function = (struct functionNode *)malloc(sizeof(struct functionNode));
    
    new_function->identifier = id;
    new_function->params = NULL;
    new_function->params = params;
    new_function->scope = NULL;
    new_function->scope = scope;
    new_function->returnValue = returnValue;
    new_function->body = NULL;
    new_function->body = body;
    new_function->next = NULL;

    return new_function;
}

void displayFunctionTable(struct functionNode * head){
    struct value *currentFunctionValue = NULL;
    while(head != NULL) {
        printf("function\t  |\ttype \t\n");
        currentFunctionValue = head->returnValue;

        if(currentFunctionValue->type == TYPE_INT){
            printf("%s \t\tint \n", head->identifier);
        }

        if(currentFunctionValue->type == TYPE_FLOAT) {
            printf("%s \t\tfloat \n", head->identifier);
        }
        printf("****** params\n");
        displaySymbolTable(head->params);
        printf("****** local symbol table\n");
        displaySymbolTable(head->scope);

        printf("\n");
        head = head->next;
    }
}