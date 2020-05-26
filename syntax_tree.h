
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
#define TERM_NODE 11


struct treeNode {
    int nodetype;
    union node * node;
    struct treeNode * next;
}typedef tree_node;



struct idNode {
    variable * symbol;
}typedef id_node;
struct valueNode{
    variable_value * val;
}typedef value_node;
struct readNode {
    tree_node * id;
}typedef read_node;
struct printNode {
    tree_node * expr;
}typedef print_node;
struct setNode {
    tree_node * id;
    tree_node * expr;
}typedef set_node;
struct exprNode {
    int operation;
    tree_node * expr;
    tree_node * term;
}typedef expr_node;
struct termNode {
    int operation;
    tree_node * term;
    tree_node * factor;
}typedef term_node;

union node {
    id_node * id;
    value_node * value;
    read_node * read;
    print_node * print;
    set_node * set;
    expr_node* expr;
    term_node* term;
} typedef instruction;





tree_node * syntax_tree;

struct treeNode * reverseSyntaxTree(struct treeNode *);
struct treeNode * getNewNode(int, union node *, struct treeNode *);
struct treeNode * getExprNode(int, struct treeNode *, struct treeNode *);
struct treeNode * getTermNode(int, struct treeNode *, struct treeNode *);
struct treeNode * getReadNode(struct treeNode *);
struct treeNode * getPrintNode(struct treeNode *);
struct treeNode * getValueNode(variable_value *);
struct treeNode * getIdNode(variable *);


struct treeNode * getSetNode(struct treeNode *, struct treeNode *);

void printSyntaxTree(struct treeNode *);