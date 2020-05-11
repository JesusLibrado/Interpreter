#include <stdlib.h>

struct node {
    char *identifier;
    struct node *next;
} typedef Symbol;

struct node* head = NULL;

void insert_table(char *id) {
    Symbol * new_symbol = (Symbol *)malloc(sizeof(Symbol));

    new_symbol->identifier = id;
    new_symbol->next = head;

    head = new_symbol;
}

void print_table(){
    Symbol *p = head;
    while(p != NULL){
        printf("Id: %s\n", p->identifier);
        p = p->next;
    }
}
