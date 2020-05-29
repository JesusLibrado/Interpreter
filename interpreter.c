#include "interpreter.h"

variable_value * executeFactor(struct treeNode * root) {
    if(root->nodetype == IDENTIFIER_NODE)
        return root->node->id->symbol->value;
    if(root->nodetype == VALUE_NODE)
        return root->node->value->val;
    return executeExpr(root);
}

variable_value * executeTerm(struct treeNode * root){
    term_node * current = root->node->term;
    switch (current->operation){
        case MULTIPLICATION_OP:
                return valueOperation(executeTerm(current->term), executeFactor(current->factor),  MULTIPLICATION_OP);
            break;
        case DIVISION_OP:
                return valueOperation(executeTerm(current->term), executeFactor(current->factor),  DIVISION_OP);
            break;
        default:
            break;
    }
    return executeFactor(root);
}

variable_value * executeExpr(struct treeNode * root){
    expr_node * expr = root->node->expr;
    switch (expr->operation){
        case ADDITION_OP:
                return valueOperation(executeExpr(expr->expr), executeTerm(expr->term),  ADDITION_OP);
            break;
        case SUBSTRACTION_OP:
                return valueOperation(executeExpr(expr->expr), executeTerm(expr->term),  SUBSTRACTION_OP);
            break;
        default:
            break;
    }
    return executeTerm(root);
}   

bool executeExpression(struct treeNode * root){
    return valueEvaluation(
        executeExpr(root->node->expression->left), 
        executeExpr(root->node->expression->right), 
        root->node->expression->condition
    );
}

void executeIf(struct treeNode * root){
    if(executeExpression(root->node->if_->condition)){
        execute(root->node->if_->statement);
    }
}

void executeIfElse(struct treeNode * root){
    if(executeExpression(root->node->if_else->condition)){
        execute(root->node->if_else->if_statement);
    } else {
        execute(root->node->if_else->else_statement);
    }
}

void executeWhile(struct treeNode * root){
    while(executeExpression(root->node->while_->condition)){
        execute(root->node->while_->statement);
    }
}

void executeFor(struct treeNode * root){
    tree_node * set = getSetNode(root->node->for_->id, root->node->for_->id_value);
    for(
        executeSet(set); 
        executeExpression(root->node->for_->to);
        setVariableValue(root->node->for_->id->node->id->symbol, executeExpr(root->node->for_->step))
    ){
        execute(root->node->for_->do_);
    }
}

void executePrint(struct treeNode * root){
    printValue(executeExpr(root));
    printf("\n");
}

void executeRead(struct treeNode * root){
    variable * var = root->node->id->symbol;
    variable_value * val = var->value;
    printf("%s: ", var->identifier);
    if(val->type == TYPE_INT){
        int newValue;
        scanf(" %d", &newValue);
        val->value.int_val = newValue;
        if(!setVariableValue(var, val)){
            printf("Error: variable type mismatch\n");
        }
    }
    if(val->type == TYPE_FLOAT){
        float newValue;
        scanf(" %f", &newValue);
        val->value.float_val = newValue;
        if(!setVariableValue(var, val)){
            printf("Error: variable type mismatch\n");
        }
    }
}

void executeSet(struct treeNode * root){
    id_node * id = root->node->set->id->node->id;
    tree_node * expr = root->node->set->expr;
    variable * var = id->symbol;
    if(!setVariableValue(var, executeExpr(expr))){
        printf("Error: variable type mismatch\n");
    }
}

void execute(struct treeNode *root){
    if(root==NULL) {return;}
    switch(root->nodetype) {
        case READ_NODE:
                executeRead(root->node->read->id);
            break;
        case SET_NODE:
                executeSet(root);
            break;
        case PRINT_NODE:
                executePrint(root->node->print->expr);
            break;
        case IF_NODE:
                executeIf(root);
            break;
        case IFELSE_NODE:
                executeIfElse(root);
            break;
        case WHILE_NODE:
                executeWhile(root);
            break;
        case FOR_NODE:
                executeFor(root);
            break;
        default: printf("ERROR: unknown root type \n"); break;
    }
    execute(root->next);
}