#ifndef _TREE_HEADER_
#define _TREE_HEADER_

#include "headers.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/**
 * 
 *      GLOBAL symbol_table, to be set before sarting the code execution
 * 
 */
struct tableNode * symbol_table;


/**
 * 
 *      GLOBAL function_table, to be set before sarting the code execution
 * 
 */
struct functionNode * function_table;

/**
 * 
 *      GLOBAL nodetypes
 * 
 */
#define IDENTIFIER_NODE 1
#define VALUE_NODE      2
#define EXPR_NODE       3
#define READ_NODE       4
#define PRINT_NODE      5
#define SET_NODE        6
#define IF_NODE         7
#define IFELSE_NODE     8
#define WHILE_NODE      9
#define FOR_NODE        10
#define TERM_NODE       11
#define EXPRESSION_NODE 12


/**
 * This is the most basic node of the syntax tree
 * @param nodetype: int             It specifies what kind of node this is
 * @param node: union node *        A pointer to the its child branch
 * @param next: struct treeNode *   A pointer to the next tree node
 */
struct treeNode {
    int nodetype;
    union node * node;
    struct treeNode * next;
};

/**
 * 
 *      GLOBAL syntax_tree, to be set optionally
 * 
 */
struct treeNode * syntax_tree;

/**
 * This is a function leaf of the tree
 * It contains a pointer to a Function
 * @param fun: struct functionNode *    Stores a function declared in the functions table
 */
struct funNode {
    struct functionNode * fun;
    struct treeNode * attributes;
}typedef fun_node;

/**
 * This is a compound leaf of the tree
 * It contains a pointer to an Identifier
 * @param symbol: struct tableNode *    Stores a variable declared in the symbol table
 */
struct idNode {
    struct tableNode * symbol;
}typedef id_node;


/**
 * This is a simple leaf of the tree
 * It contains a pointer to a value
 * @param val: struct value *           Stores a value structure
 */
struct valueNode{
    struct value * val;
}typedef value_node;


/**
 * This is a READ tree node
 * @param id: struct treeNode *         A pointer to the id node to be read
 */
struct readNode {
    struct treeNode * id;
}typedef read_node;


/**
 * This is a PRINT tree node
 * @param expr: struct treeNode *       A pointer to the expr branch to be printed
 */
struct printNode {
    struct treeNode * expr;
}typedef print_node;


/**
 * This is a SET tree node
 * @param id: struct treeNode *         A pointer to an id node
 * @param expr: struct treeNode *       A pointer to an expr node
 */
struct setNode {
    struct treeNode * id;
    struct treeNode * expr;
}typedef set_node;


/**
 * This is an EXPR tree node
 * @param operation: int                Specifies the operation to be performed
 * @param expr: struct treeNode *       A pointer to the left part of the production (expr)
 * @param term: struct treeNode *       A pointer to the right part of the production (term)
 */
struct exprNode {
    int operation;
    struct treeNode * expr;
    struct treeNode * term;
}typedef expr_node;


/**
 * This is a TERM tree node
 * @param operation: int                Specifies the operation to be performed
 * @param term: struct treeNode *       A pointer to the left part of the production (term)
 * @param factor: struct treeNode *     A pointer to the right part of the production (factor)
 */
struct termNode {
    int operation;
    struct treeNode * term;
    struct treeNode * factor;
}typedef term_node;


/**
 * This is an EXPRESSION tree node
 * @param condition: int                Specifies the condition to be evaluated
 * @param left: struct treeNode *       A pointer to the left part of the production (expr)
 * @param right: struct treeNode *      A pointer to the right part of the production (expr)
 */
struct expressionNode {
    int condition;
    struct treeNode * left;
    struct treeNode * right;
}typedef expression_node;


/**
 * This is an IF tree node
 * @param condition: struct treeNode *       A pointer to the conidition to be evaluated (expression)
 * @param statement: struct treeNode *       A pointer to the branch to be executed if true (stmt)
 */
struct ifNode {
    struct treeNode * condition;
    struct treeNode * statement;
}typedef if_node;


/**
 * This is an IFELSE tree node
 * @param condition: struct treeNode *          A pointer to the conidition to be evaluated (expression)
 * @param if_statement: struct treeNode *       A pointer to the branch to be executed if true (stmt)
 * @param else_statement: struct treeNode *     A pointer to the branch to be executed if false (stmt)
 */
struct ifElseNode{
    struct treeNode * condition;
    struct treeNode * if_statement;
    struct treeNode * else_statement;
}typedef if_else_node;


/**
 * This is  WHILE tree node
 * @param condition: struct treeNode *       A pointer to the conidition to be evaluated (expression)
 * @param statement: struct treeNode *       A pointer to the branch to be executed if true (stmt)
 */
struct whileNode{
    struct treeNode * condition;
    struct treeNode * statement;
}typedef while_node;


/**
 * This is a FOR tree node
 * @param id: struct treeNode *             A pointer to the Id node to be modified (identifier)
 * @param id_value: struct treeNode *       A pointer to the Expr node in which the Id will be set (expr)
 * @param to: struct treeNode *             A pointer to the Expression node evaluation 
 *                                              to set the loop limits (expression)
 * @param step: struct treeNode *           A pointer to the Expr node which specifies the incrementation
 *                                              of the IdNode value (expr)
 * @param do_: struct treeNode *            A pointer to the branch to be executed inside the loop (stmt)
 */
struct forNode{
    struct treeNode * id;
    struct treeNode * id_value;
    struct treeNode * to;
    struct treeNode * step;
    struct treeNode * do_;
}typedef for_node;


/**
 * This is the branch contained inside each tree node
 * Depending on the nodetype specified, each tree node will have different branch types
 * Values can vary in a range of options (shown inside the union{})
 * @note each node inside the union is declared according to their type, 
 *       NOT as a common treeNode
 */
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
    fun_node * fun;
};




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
struct treeNode * getValueNode(struct value *);
struct treeNode * getIdNode(struct tableNode *);
struct treeNode * getFunctionNode(struct functionNode *);
struct treeNode * getForNode(
    struct treeNode *,
    struct treeNode *,
    struct treeNode *,
    struct treeNode *,
    struct treeNode *
);

void printSyntaxTree(struct treeNode *);

#endif