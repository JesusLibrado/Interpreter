#ifndef _VARIABLE_HEADER_
#define _VARIABLE_HEADER_

#include <stdlib.h>
#include <time.h> 
#include <stdio.h>
#include <string.h>
#include "value.h"

struct tableNode {
    char *identifier;
    variable_value *value;
    struct tableNode *next;
} typedef variable;

void displaySymbolTable(struct tableNode *);
void freeSymbolTable(struct tableNode **head);

void declareVariable(struct tableNode **, char *, variable_value*);
bool setVariableValue(struct tableNode *, char *, variable_value*);

char *getVariableId(struct tableNode *);

variable_value *getVariableValue(struct tableNode *, char *);
variable *getVariable(struct tableNode *, char *);

bool variableHasBeenDeclared(struct tableNode *, char *);
bool variableHasValueAssigned(struct tableNode *, char *);

#endif