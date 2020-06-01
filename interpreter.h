
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
struct variableValue * executeExpr(struct treeNode *);
struct variableValue * executeTerm(struct treeNode *);
struct variableValue * executeFactor(struct treeNode *);
bool executeExpression(struct treeNode *);