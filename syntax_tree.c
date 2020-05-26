#include "syntax_tree.h"

struct treeNode * getNewNode(int type, instruction * instr, tree_node *nextTreeNode){
    struct treeNode * newTreeNode = (struct treeNode *)malloc(sizeof(tree_node));

    newTreeNode->nodetype = type;
    newTreeNode->node = instr;
    newTreeNode->next = nextTreeNode;

    return newTreeNode;
}

struct treeNode * getNewReadNode(struct treeNode * node){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->read = (struct readNode *)malloc(sizeof(struct readNode));
    newInstr->read->id = node;

    return getNewNode(READ_NODE, newInstr, NULL);
}

struct treeNode * getNewValueNode(variable_value * val){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->value->value = val;

    return getNewNode(VALUE_NODE, newInstr, NULL);
}

struct treeNode * getNewIdNode(variable * var){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));
    
    newInstr->id = (struct idNode *)malloc(sizeof(struct idNode));
    newInstr->id->symbol = var;
    return getNewNode(IDENTIFIER_NODE, newInstr, NULL);
}

void printSyntaxTree(struct treeNode *root){
    if(root==NULL) {printf("\n"); return;}
    switch(root->nodetype) {
        case READ_NODE:
                printf("[Read]----\n");
                printSyntaxTree(root->node->read->id);
            break;
        case IDENTIFIER_NODE:
                printVariable(root->node->id->symbol);
            break;
        default: printf("ERROR: unknown root type \n"); break;
    }
    printSyntaxTree(root->next);
}