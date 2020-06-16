#ifndef _FUNCTIONS_HEADER_
#define _FUNCTIONS_HEADER_

#include <stdlib.h>
#include "../syntax_tree.h"

struct functionNode {
    char * identifier;
    struct tableNode * params;
    struct tableNode * scope;
    struct value * returnValue;
    struct treeNode * body;
    struct functionNode * next;
};

void displayFunctionTable(struct functionNode *);
void printFunction(struct functionNode *);
void printFunction(struct functionNode *);
struct functionNode * declareFunction(
    char *, 
    struct tableNode *,
    struct tableNode *,
    struct value *,
    struct treeNode *
);

char * getFunctionId(struct functionNode *);

struct functionNode * getFunction(struct functionNode *, char *);

bool functionHasBeenDeclared(struct functionNode *, char *);

#endif