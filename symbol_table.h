#include <stdlib.h>
#include <time.h> 
#include <stdio.h>
#include <string.h>
#include "value.h"

/*

struct tableNode {
    char *identifier;
    variable_value *value;
}typedef variable;

void displaySymbolTable(struct tableNode *head);
void freeSymbolTable(struct tableNode **head);
void declareVariable(struct tableNode **head, char *id);
void setVariableValue(struct tableNode *head, char *id);
variable_value *getVariableValue(struct tableNode *head, char *id);
variable *getVariable(struct tableNode *head, char *id);
bool variableHasBeenDeclared(struct tableNode *head, char *id);
bool variableHasValueAssigned(struct tableNode *head, char *id);
*/

void displaySymbolTable(struct tableNode *head);
void freeSymbolTable(struct tableNode **head);

void declareVariable(struct tableNode **head_ref, char* id, int var_type);
void setSymbolValue(struct tableNode *head_ref, char id[20], float value);

struct tableNode* findSymbol(struct tableNode *head, char* id);

float getSymbolValue(struct tableNode* head, char* id);
int getSymbolType(struct tableNode *head, char *id);


void read_user_input(struct tableNode *head, char *id){
    srand(time(0)); 
    int rand1 = rand()%50;
    printf("Read %s: %d\n", id, rand1);
    assign_value(head, id, (float)rand1);
}
