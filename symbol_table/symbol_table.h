#ifndef _VARIABLE_HEADER_
#define _VARIABLE_HEADER_

#include "value.h"
#include <string.h>

struct tableNode {
    char *identifier;
    struct value *value;
    struct tableNode *next;
} typedef variable;

void displaySymbolTable(struct tableNode *);
void freeSymbolTable(struct tableNode **);
void printVariable(struct tableNode *);

struct tableNode * declareVariable(char *, struct value*);
bool setVariableValue(struct tableNode *, struct value*);

char *getVariableId(struct tableNode *);

struct value *getVariableValue(struct tableNode *, char *);
struct tableNode *getVariable(struct tableNode *, char *);

bool variableHasBeenDeclared(struct tableNode *, char *);
bool variableHasValueAssigned(struct tableNode *, char *);

#endif