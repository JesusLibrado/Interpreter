
#include "value.h"
#include "symbol_table.h"
#include "syntax_tree.h"


#include <stdlib.h>
#include <stdio.h>

void execute(struct treeNode *);

void executeRead(struct treeNode *);
void executePrint(struct treeNode *);
void executeSet(struct treeNode *);
void executeIf(struct treeNode *);
void executeIfElse(struct treeNode *);
void executeWhile(struct treeNode *);
void executeFor(struct treeNode *);
variable_value * executeExpr(struct treeNode *);
variable_value * executeTerm(struct treeNode *);
variable_value * executeFactor(struct treeNode *);
bool executeExpression(struct treeNode *);