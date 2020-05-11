#include <stdlib.h>
#include <string.h>

struct node {
    int type;
    char *identifier;
    struct node *next;
} typedef Symbol;

struct node* head = NULL;

void print_table(){
    Symbol *p = head;
    printf("\n[");
    while(p != NULL){
        printf("%s: %d -> ", p->identifier, p->type);
        p = p->next;
    }
    printf("]\n");
}

void declare_var(char *id, int var_type) {
    printf("Declaration of %s\n", id);
    Symbol * new_symbol = (Symbol *)malloc(sizeof(Symbol));

    new_symbol->identifier = id;
    new_symbol->type = var_type;
    new_symbol->next = head;

    head = new_symbol;
    print_table();
}

int is_declared(char *id) {
    Symbol *p = head;
    while(p != NULL){
        if(strcmp(p->identifier, id) == 0)
            return 1;
        p = p->next;
    }
    return 0;
}

void free_table(){
    while(head != NULL){
        free(head);
        head = head->next;
    }
}
