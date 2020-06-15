#include "symbol_table.h"

struct tableNode * declareVariable(char* id, struct value* variableValue){
    struct tableNode * new_symbol = (struct tableNode *)malloc(sizeof(struct tableNode));

    new_symbol->identifier = id;
    new_symbol->value = variableValue;
    new_symbol->next = NULL;

    return new_symbol;
}

struct tableNode* getVariable(struct tableNode *head, char* id){
    if(head == NULL) return NULL;
    if(strcmp(head->identifier, id) == 0) return head;
    return getVariable(head->next, id);
}

bool setVariableValue(variable* id, struct value *newValue) {
    if(typesMatch(id->value, newValue)){
        if(!id){
            return false;
        }else {
            id->value = newValue;
            return true;
        }
    }
    return false;
} 

struct value *getVariableValue(struct tableNode *head, char *id){
    struct tableNode *p = getVariable(head, id);
    if(!p){
        printf("Declaration error!: %s was not declared\n", id);
        return NULL; // default value
    }
    return p->value;
}

bool variableHasBeenDeclared(struct tableNode *head, char *id) {
    if(head == NULL) return false;
    if(strcmp(head->identifier, id) == 0) return true;
    return getVariable(head->next, id);
}

bool variableHasValueAssigned(struct tableNode *head, char *id){
    if(head == NULL) return false;
    if(strcmp(head->identifier, id) == 0) return head->value != NULL;
    return getVariable(head->next, id);
}

char *getVariableId(struct tableNode *var){
    return var->identifier;
}

void printVariable(struct tableNode * var) {
    struct value * val = var->value;
    if(val->type == TYPE_INT){
        printf("var %s: %s = %d ", var->identifier, getTypeAsString(val), val->value.int_val);
    }
    if(val->type == TYPE_FLOAT){
        printf("var %s: %s = %d ", var->identifier, getTypeAsString(val), val->value.int_val);
    }
}

void displaySymbolTable(struct tableNode *head){
    printf("\tvariable  |\ttype \t|\tvalue\n");
    struct value *currentVariableValue = NULL;
    while(head != NULL) {
        currentVariableValue = head->value;

        if(currentVariableValue->type == TYPE_INT){
            printf("\t%s \t\tint \t", head->identifier);
            printf(" \t%d ", currentVariableValue->value.int_val);
        }

        if(currentVariableValue->type == TYPE_FLOAT) {
            printf("\t%s \t\tfloat \t", head->identifier);
            printf(" \t%.2f ", currentVariableValue->value.float_val);
        }

        printf("\n");
        head = head->next;
    }
}

void freeSymbolTable(struct tableNode **head){
    while((*head) != NULL){
        free((*head));
        (*head) = (*head)->next;
    }
}