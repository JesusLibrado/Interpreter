#ifndef _VARIABLE_HEADER_
#define _VARIABLE_HEADER_

#include "value.h"
#include <string.h>

struct tableNode {
    char *identifier;
    struct variableValue *value;
    struct tableNode *next;
} typedef variable;

void displaySymbolTable(struct tableNode *);
void freeSymbolTable(struct tableNode **);
void printVariable(struct tableNode *);

void declareVariable(struct tableNode **, char *, struct variableValue*);
bool setVariableValue(struct tableNode *, struct variableValue*);

char *getVariableId(struct tableNode *);

struct variableValue *getVariableValue(struct tableNode *, char *);
struct tableNode *getVariable(struct tableNode *, char *);

bool variableHasBeenDeclared(struct tableNode *, char *);
bool variableHasValueAssigned(struct tableNode *, char *);

#endif