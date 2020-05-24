#include "symbol_table.h"

struct tableNode {
    float value;
    int type; // int:1 | float:2
    char *identifier;
    struct tableNode *next;
} typedef Symbol;

void displaySymbolTable(struct tableNode *head){
    printf("\tvariable  |\ttype \t|\tvalue\n");
    while(head != NULL) {
        if(head->type == 1){
            printf("\t%s \t\tint \t", head->identifier);
            if(head->value)
                printf(" \t%d ", (int)head->value);
        }else {
            printf("\t%s \t\tfloat \t", head->identifier);
            if(head->value)
                printf(" \t%.2f ", head->value);
        }
        printf("\n");
        head = head->next;
    }
}

struct tableNode* findSymbol(struct tableNode *head, char* id){
    if(head == NULL) return NULL;
    if(strcmp(head->identifier, id) == 0) return head;
    return findSymbol(head->next, id);
}

float getSymbolValue(struct tableNode* head, char* id){
    struct tableNode *p = find(head, id);
    if(!p){
        printf("Declaration error!: %s was not declared\n", id);
        return 0; // default value
    }
    return p->value;
}

int getSymbolType(struct tableNode *head, char *id) {
    struct tableNode *p = find(head, id);
    if(!p){
        printf("Declaration error!: %s was not declared\n", id);
        return 0; // doesn't exist
    }
    return p->type;
}

void setSymbolValue(struct tableNode *head_ref, char id[20], float value) {
    struct tableNode *p = find(head_ref, id);
    if(!p){
        printf("Declaration error! %s is not a variable(DEFAULT: 0)\n", id);
    }else {
        p->value = value;
    }
}  

void declareVariable(struct tableNode **head_ref, char* id, int var_type){
    struct tableNode * new_symbol = (struct tableNode *)malloc(sizeof(struct tableNode));

    new_symbol->identifier = id;
    new_symbol->type = var_type;
    new_symbol->next = (*head_ref);

    (*head_ref) = new_symbol;
}

void freeSymbolTable(struct tableNode **head){
    while((*head) != NULL){
        free((*head));
        (*head) = (*head)->next;
    }
}