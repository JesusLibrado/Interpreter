#include "syntax_tree.h"

struct treeNode * getNewNode(int type, instruction * instr, tree_node *nextTreeNode){
    struct treeNode * newTreeNode = (struct treeNode *)malloc(sizeof(tree_node));

    newTreeNode->nodetype = type;
    newTreeNode->node = instr;
    newTreeNode->next = nextTreeNode;

    return newTreeNode;
}


struct treeNode * getSetNode(struct treeNode * var, struct treeNode * e){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->set = (struct setNode *)malloc(sizeof(struct setNode));
    newInstr->set->id = NULL;
    newInstr->set->id = var;
    newInstr->set->expr = NULL;
    newInstr->set->expr = e;

    return getNewNode(SET_NODE, newInstr, NULL);

}
struct treeNode * getExprNode(int op, struct treeNode * e, struct treeNode * t){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->expr = (struct exprNode *)malloc(sizeof(struct exprNode));
    newInstr->expr->operation = op;
    newInstr->expr->expr = NULL;
    newInstr->expr->expr = e;
    newInstr->expr->term = NULL;
    newInstr->expr->term = t;

    return getNewNode(EXPR_NODE, newInstr, NULL);
}
struct treeNode * getTermNode(int op, struct treeNode * t, struct treeNode * f){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->term = (struct termNode *)malloc(sizeof(struct termNode));
    newInstr->term->operation = op;
    newInstr->term->term = NULL;
    newInstr->term->term = t;
    newInstr->term->factor = NULL;
    newInstr->term->factor = f;

    return getNewNode(TERM_NODE, newInstr, NULL);
}

struct treeNode * getPrintNode(struct treeNode * node){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->print = (struct printNode *)malloc(sizeof(struct printNode));
    newInstr->print->expr = NULL;
    newInstr->print->expr = node;

    return getNewNode(PRINT_NODE, newInstr, NULL);
}

struct treeNode * getReadNode(struct treeNode * node){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->read = (struct readNode *)malloc(sizeof(struct readNode));
    newInstr->read->id = node;

    return getNewNode(READ_NODE, newInstr, NULL);
}

struct treeNode * getValueNode(variable_value * val){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->value = (struct valueNode *)malloc(sizeof(struct valueNode));
    newInstr->value->val = val;

    return getNewNode(VALUE_NODE, newInstr, NULL);
}

struct treeNode * getIdNode(variable * var){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));
    
    newInstr->id = (struct idNode *)malloc(sizeof(struct idNode));
    newInstr->id->symbol = var;
    return getNewNode(IDENTIFIER_NODE, newInstr, NULL);
}

void printSyntaxTree(struct treeNode *root){
    if(root==NULL) {printf("\n"); return;}
    switch(root->nodetype) {
        case VALUE_NODE:
                printValue(root->node->value->val);
            break;
        case IDENTIFIER_NODE:
                printVariable(root->node->id->symbol);
            break;
        case READ_NODE:
                printf("[Read]----\n");
                printSyntaxTree(root->node->read->id);
            break;
        case SET_NODE:
                printf("[Set]----\n");
                printSyntaxTree(root->node->set->id);
                printSyntaxTree(root->node->set->expr);
            break;
        case PRINT_NODE:
                printf("[Print]----\n");
                printSyntaxTree(root->node->print->expr);
            break;
        case EXPR_NODE:
                printf("[Expr]----\n");
                printSyntaxTree(root->node->expr->expr);
                printf("(-- op --)\n");
                printSyntaxTree(root->node->expr->term);
            break;
        case TERM_NODE:
                printf("[Term]----\n");
                printSyntaxTree(root->node->term->term);
                printf("(-- op --)\n");
                printSyntaxTree(root->node->term->factor);
            break;
        default: printf("ERROR: unknown root type \n"); break;
    }
    printSyntaxTree(root->next);
}

struct treeNode * reverseSyntaxTree(struct treeNode * root){
    if (root == NULL || root->next == NULL)  return root; 
    struct treeNode * rest = reverseSyntaxTree(root->next); 
    root->next->next = root;
    root->next = NULL; 
    return rest; 
}