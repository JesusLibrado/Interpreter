#include "syntax_tree.h"

struct treeNode * getNewNode(int type, instruction * instr, tree_node *nextTreeNode){
    struct treeNode * newTreeNode = (struct treeNode *)malloc(sizeof(tree_node));

    newTreeNode->nodetype = type;
    newTreeNode->node = instr;
    newTreeNode->next = nextTreeNode;

    return newTreeNode;
}

struct treeNode * getWhileNode(struct treeNode * cond, struct treeNode * stmt){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->while_ = (struct whileNode *)malloc(sizeof(struct whileNode));
    newInstr->while_->condition = NULL;
    newInstr->while_->condition = cond;
    newInstr->while_->statement = NULL;
    newInstr->while_->statement = stmt;

    return getNewNode(WHILE_NODE, newInstr, NULL);
}

struct treeNode * getIfElseNode(struct treeNode * cond, struct treeNode * i_stmt, struct treeNode * e_stmt){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->if_else = (struct ifElseNode *)malloc(sizeof(struct ifElseNode));
    newInstr->if_else->condition = NULL;
    newInstr->if_else->condition = cond;
    newInstr->if_else->if_statement = NULL;
    newInstr->if_else->if_statement = i_stmt;
    newInstr->if_else->else_statement = NULL;
    newInstr->if_else->else_statement = e_stmt;

    return getNewNode(IFELSE_NODE, newInstr, NULL);
}

struct treeNode * getForNode(struct treeNode * var, struct treeNode * var_val, struct treeNode * t, struct treeNode * s, struct treeNode * d){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->for_ = (struct forNode *)malloc(sizeof(struct forNode));
    newInstr->for_->id = NULL;
    newInstr->for_->id = var;
    newInstr->for_->id_value = NULL;
    newInstr->for_->id_value = var_val;
    newInstr->for_->to = NULL;
    newInstr->for_->to = t;
    newInstr->for_->step = NULL;
    newInstr->for_->step = s;
    newInstr->for_->do_ = NULL;
    newInstr->for_->do_ = d;

    return getNewNode(FOR_NODE, newInstr, NULL);
}

struct treeNode * getIfNode(struct treeNode * cond, struct treeNode * stmt){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->if_ = (struct ifNode *)malloc(sizeof(struct ifNode));
    newInstr->if_->condition = NULL;
    newInstr->if_->condition = cond;
    newInstr->if_->statement = NULL;
    newInstr->if_->statement = stmt;

    return getNewNode(IF_NODE, newInstr, NULL);
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

struct treeNode * getExpressionNode(int cond, struct treeNode * l, struct treeNode * r){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->expression = (struct expressionNode *)malloc(sizeof(struct expressionNode));
    newInstr->expression->condition = cond;
    newInstr->expression->left = NULL;
    newInstr->expression->left = l;
    newInstr->expression->right = NULL;
    newInstr->expression->right = r;

    return getNewNode(EXPRESSION_NODE, newInstr, NULL);
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

struct treeNode * getValueNode(struct variableValue * val){
    instruction * newInstr = (union node *)malloc(sizeof(instruction));

    newInstr->value = (struct valueNode *)malloc(sizeof(struct valueNode));
    newInstr->value->val = val;

    return getNewNode(VALUE_NODE, newInstr, NULL);
}

struct treeNode * getIdNode(struct tableNode * var){
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
        case EXPRESSION_NODE:
                printf("[Expression]----\n");
                printSyntaxTree(root->node->expression->left);
                printf("(-- cond --)\n");
                printSyntaxTree(root->node->expression->right);
            break;
        case IF_NODE:
                printf("[If]----\n");
                printSyntaxTree(root->node->if_->condition);
                printf("(-- stmt --)\n");
                printSyntaxTree(root->node->if_->statement);
            break;
        case IFELSE_NODE:
                printf("[If Else]----\n");
                printSyntaxTree(root->node->if_else->condition);
                printf("(-- if stmt --)\n");
                printSyntaxTree(root->node->if_else->if_statement);
                printf("(-- else stmt --)\n");
                printSyntaxTree(root->node->if_else->else_statement);
            break;
        case WHILE_NODE:
                printf("[While]----\n");
                printSyntaxTree(root->node->while_->condition);
                printf("(-- stmt --)\n");
                printSyntaxTree(root->node->while_->statement);
            break;
        case FOR_NODE:
                printf("[For]----\n");
                printSyntaxTree(root->node->for_->id);
                printf("(-- init at --)\n");
                printSyntaxTree(root->node->for_->id_value);
                printf("(-- to --)\n");
                printSyntaxTree(root->node->for_->to);
                printf("(-- step --)\n");
                printSyntaxTree(root->node->for_->step);
                printf("(-- do --)\n");
                printSyntaxTree(root->node->for_->do_);
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