
#include "syntax_tree.h"

#include <stdlib.h>
#include <stdio.h>

struct value * execute(struct treeNode *);
void executeRead(struct treeNode *);
void executePrint(struct treeNode *);
void executeSet(struct treeNode *);
struct value * executeIf(struct treeNode *);
struct value * executeIfElse(struct treeNode *);
struct value * executeWhile(struct treeNode *);
struct value * executeFor(struct treeNode *);
struct value * executeExpr(struct treeNode *);
struct value * executeTerm(struct treeNode *);
struct value * executeFactor(struct treeNode *);
struct value * executeFunction(struct treeNode *);
struct value * executeReturn(struct treeNode *);
bool executeExpression(struct treeNode *);