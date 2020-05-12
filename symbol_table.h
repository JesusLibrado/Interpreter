#include <stdlib.h>
#include <string.h>

struct node {
    void *value;
    int type; // int:1 | float:2
    char *identifier;
    struct node *next;
} typedef Symbol;

void print_table(struct node *head){
    printf("\n[");
    while(head != NULL){
        printf("%s: %s ", head->identifier, (head->type==1)?"int":"float");
        printf("-> ");
        head = head->next;
    }
    //printf("%s: %s ", head->identifier, (head->type==1)?"int":"float");
    printf("null ]\n");
}

void declare_var(struct node **head_ref, char *id, int var_type) {
    struct node * new_symbol = (struct node *)malloc(sizeof(struct node));

    new_symbol->identifier = id;
    new_symbol->type = var_type;
    new_symbol->next = (*head_ref);

    (*head_ref) = new_symbol;
}

// void assign_value(char *id, void *var_value, size_t data_size) {
//     Symbol *p = head;
//     while(p != NULL && strcmp(p->identifier, id) != 0){
//         p = p->next;
//     }
//     if(p!=NULL){
//         int i; 
//         for (i=0; i<data_size; i++) {   
//             //printf("%c ", (char)(var_value + i));
//             *(char *)(p->value + i) = *(char *)(var_value + i);
//         }
//     }
// }   

struct node * find(struct node *head, char *id) {
    if(head == NULL) return NULL;
    if(strcmp(head->identifier, id) == 0) return head;
    return find(head->next, id);
}

// void free_table(){
//     while(head != NULL){
//         free(head);
//         head = head->next;
//     }
// }
