
#include "value.h"
#include "symbol_table.h"
#include "syntax_tree.h"


#include <stdlib.h>
#include <stdio.h>

void execute(struct treeNode *);

void executeRead(struct treeNode *);
void executePrint(struct treeNode *);