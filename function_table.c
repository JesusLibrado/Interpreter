#include "function_table.h"


void declareVariabledeclareFunction(
    struct functionNode ** head_ref, 
    char * id, 
    struct tableNode * params,
    struct tableNode * scope,
    struct value * returnValue,
    struct treeNode * body
){
    struct functionNode * new_function = (struct functionNode *)malloc(sizeof(struct functionNode));
    printf("Heerrreeeee\n");
    new_function->identifier = id;
    new_function->params = NULL;
    new_function->params = params;
    new_function->scope = NULL;
    new_function->scope = scope;
    new_function->returnValue = returnValue;
    new_function->body = NULL;
    new_function->body = body;
    new_function->next = (*head_ref);

    (*head_ref) = new_function;
}

void displayFunctionTable(struct functionNode * head){
    printf("\tfunction  |\ttype \t|\tparams\n");
    struct value *currentFunctionValue = NULL;
    while(head != NULL) {
        currentFunctionValue = head->returnValue;

        if(currentFunctionValue->type == TYPE_INT){
            printf("\t%s \t\tint \t", head->identifier);
            printf(" \t");
        }

        if(currentFunctionValue->type == TYPE_FLOAT) {
            printf("\t%s \t\tfloat \t", head->identifier);
            printf(" \t ");
        }

        printf("\n");
        head = head->next;
    }
}