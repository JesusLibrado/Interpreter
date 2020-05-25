
#include "value.h"
#include "symbol_table.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

variable * symbol_table;

#define IDENTIFIER_NODE 1
#define VALUE_NODE 2
#define EXPR_NODE 3
#define READ_NODE 4
#define PRINT_NODE 5
#define SET_NODE 6
#define IF_NODE 7
#define IFELSE_NODE 8
#define WHILE_NODE 9
#define FOR_NODE 10


struct treeNode {
    int nodetype;
    union node * node;
    struct treeNode * next;
}typedef tree_node;


struct idNode {
    variable * symbol;
}typedef id_node;

struct valueNode {
    variable_value * value;
}typedef value_node;

struct exprNode{
    variable * symbol;
    variable_value * value;
    int operationType;
}typedef expr_node;

struct printNode {
    tree_node * expr;
}typedef print_node;

struct setNode {
    tree_node * id;
    tree_node * expr;
}typedef set_node;

struct readNode {
    tree_node * id;
}typedef read_node;

union node {
    id_node * id;
    value_node * value;
    read_node * read;
    print_node * print;
    set_node * set;
    expr_node* expr;
} typedef instruction;


tree_node * syntax_tree;

struct treeNode * getNewNode(int, union node *, struct treeNode *);
struct treeNode * getNewReadNode(struct treeNode *);
struct treeNode * getNewValueNode(variable_value *);
struct treeNode * getNewIdNode(variable *);


struct treeNode * getNewPrintNode(struct treeNode *);
struct treeNode * getNewSetNode(variable *, variable_value *);

void printSyntaxTree(struct treeNode *);