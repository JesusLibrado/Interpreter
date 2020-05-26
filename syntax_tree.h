
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
#define EXPRESSION_NODE 12


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
struct expressionNode {
    int condition;
    tree_node * left;
    tree_node * right;
}typedef expression_node;
struct ifNode {
    tree_node * condition;
    tree_node * statement;
}typedef if_node;
struct ifElseNode{
    tree_node * condition;
    tree_node * if_statement;
    tree_node * else_statement;
}typedef if_else_node;
struct whileNode{
    tree_node * condition;
    tree_node * statement;
}typedef while_node;
struct forNode{
    tree_node * id;
    tree_node * id_value;
    tree_node * to;
    tree_node * step;
    tree_node * do_;
}typedef for_node;

union node {
    id_node * id;
    value_node * value;
    read_node * read;
    print_node * print;
    set_node * set;
    expr_node* expr;
    term_node* term;
    expression_node* expression;
    if_node * if_;
    if_else_node * if_else;
    for_node * for_;
    while_node * while_;
} typedef instruction;





tree_node * syntax_tree;

struct treeNode * reverseSyntaxTree(struct treeNode *);
struct treeNode * getNewNode(int, union node *, struct treeNode *);
struct treeNode * getExprNode(int, struct treeNode *, struct treeNode *);
struct treeNode * getTermNode(int, struct treeNode *, struct treeNode *);
struct treeNode * getExpressionNode(int, struct treeNode *, struct treeNode *);
struct treeNode * getIfElseNode(struct treeNode *, struct treeNode *, struct treeNode *);
struct treeNode * getSetNode(struct treeNode *, struct treeNode *);
struct treeNode * getIfNode(struct treeNode *, struct treeNode *);
struct treeNode * getWhileNode(struct treeNode *, struct treeNode *);
struct treeNode * getReadNode(struct treeNode *);
struct treeNode * getPrintNode(struct treeNode *);
struct treeNode * getValueNode(variable_value *);
struct treeNode * getIdNode(variable *);
struct treeNode * getForNode(
    struct treeNode *,
    struct treeNode *,
    struct treeNode *,
    struct treeNode *,
    struct treeNode *
);

void printSyntaxTree(struct treeNode *);