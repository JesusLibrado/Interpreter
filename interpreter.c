#include "interpreter.h"

void executeRead(struct treeNode * root){
    variable * var = root->node->id->symbol;
    variable_value * val = var->value;
    if(val->type == TYPE_INT){
        int newValue;
        scanf("%d", &newValue);
        val->value.int_val = newValue;
        if(!newValue){
            printf("Error: variable type mismatch\n");
        }
    }
    if(val->type == TYPE_FLOAT){
        float newValue;
        scanf("%f", &newValue);
        val->value.float_val = newValue;
        if(!newValue){
            printf("Error: variable type mismatch\n");
        }
    }
}

void executePrint(struct treeNode * root){

}

void execute(struct treeNode *root){
    if(root==NULL) {return;}
    switch(root->nodetype) {
        case READ_NODE:
                printf("[Read]----\n");
                executeRead(root->node->read->id);
            break;
        case SET_NODE:
                printf("[Set]----\n");
                // printSyntaxTree(root->node->set->id);
                // printSyntaxTree(root->node->set->expr);
            break;
        case PRINT_NODE:
                printf("[Print]----\n");
                // printSyntaxTree(root->node->print->expr);
            break;
        case EXPR_NODE:
                printf("[Expr]----\n");
                // printSyntaxTree(root->node->expr->expr);
                // printf("(-- op --)\n");
                // printSyntaxTree(root->node->expr->term);
            break;
        case TERM_NODE:
                printf("[Term]----\n");
                // printSyntaxTree(root->node->term->term);
                // printf("(-- op --)\n");
                // printSyntaxTree(root->node->term->factor);
            break;
        case EXPRESSION_NODE:
                printf("[Expression]----\n");
                // printSyntaxTree(root->node->expression->left);
                // printf("(-- cond --)\n");
                // printSyntaxTree(root->node->expression->right);
            break;
        case IF_NODE:
                printf("[If]----\n");
                // printSyntaxTree(root->node->if_->condition);
                // printf("(-- stmt --)\n");
                // printSyntaxTree(root->node->if_->statement);
            break;
        case IFELSE_NODE:
                printf("[If Else]----\n");
                // printSyntaxTree(root->node->if_else->condition);
                // printf("(-- if stmt --)\n");
                // printSyntaxTree(root->node->if_else->if_statement);
                // printf("(-- else stmt --)\n");
                // printSyntaxTree(root->node->if_else->else_statement);
            break;
        case WHILE_NODE:
                printf("[While]----\n");
                // printSyntaxTree(root->node->while_->condition);
                // printf("(-- stmt --)\n");
                // printSyntaxTree(root->node->while_->statement);
            break;
        case FOR_NODE:
                printf("[For]----\n");
                // printSyntaxTree(root->node->for_->id);
                // printf("(-- init at --)\n");
                // printSyntaxTree(root->node->for_->id_value);
                // printf("(-- to --)\n");
                // printSyntaxTree(root->node->for_->to);
                // printf("(-- step --)\n");
                // printSyntaxTree(root->node->for_->step);
                // printf("(-- do --)\n");
                // printSyntaxTree(root->node->for_->do_);
            break;
        default: printf("ERROR: unknown root type \n"); break;
    }
    execute(root->next);
}