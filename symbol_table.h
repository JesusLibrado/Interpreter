#include <stdlib.h>

struct node {
    char *identifier;
    struct node *next;
} typedef Symbol;

struct node* head = NULL;

void print_table(){
    Symbol *p = head;
    printf("\n[");
    while(p != NULL){
        printf("%s -> ", p->identifier);
        p = p->next;
    }
    printf("]\n");
}

void declare(char *id) {
    printf("Declaration of %s\n", id);
    Symbol * new_symbol = (Symbol *)malloc(sizeof(Symbol));

    new_symbol->identifier = id;
    new_symbol->next = head;

    head = new_symbol;
    print_table();
}

void free_table(){
    free(head);
}
