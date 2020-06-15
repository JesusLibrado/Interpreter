#include "function_table.h"


struct functionNode * getFunction(struct functionNode * head, char * id){
    if(head == NULL) return NULL;
    if(strcmp(head->identifier, id) == 0) return head;
    return getFunction(head->next, id);
}

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

void printFunction(struct functionNode * head){
    printf("%s(", head->identifier);
    struct tableNode * param_p = head->params;
    while(param_p != NULL){
        printVariable(param_p);
        if(param_p->next!=NULL)
            printf(", ");
        param_p = param_p->next;
    }
    if(head->returnValue->type == TYPE_INT){
        printf("): int");
    } 
    if(head->returnValue->type == TYPE_FLOAT){
        printf("): float");
    }
    if(head->scope){
        printf(" { \n");
        displaySymbolTable(head->scope);
        printf("} \n");
    }
    else {
        printf(";\n");
    }
    if(head->body){
        printSyntaxTree(head->body);
    }
}

char * getFunctionId(struct functionNode * head){
    return head->identifier;
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