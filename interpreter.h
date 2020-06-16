
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
struct value * executeExpr(struct treeNode *);
struct value * executeTerm(struct treeNode *);
struct value * executeFactor(struct treeNode *);
struct value * executeFunction(struct treeNode *);
bool executeExpression(struct treeNode *);