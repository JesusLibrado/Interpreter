#include "interpreter.h"


/**
 * It traverses through the tree nodes as a normal linked list (moving on to the next node)
 * It makes a preorder traversal in its branches
 * It treats each nodetype differently calling their own function
 * @param root: struct treeNode *        A pointer to any tree node
 */
struct value * execute(struct treeNode *root){
    if(root==NULL) {return getInteger(0);}
    switch(root->nodetype) {
        case READ_NODE:
                executeRead(root);
            break;
        case SET_NODE:
                executeSet(root);
            break;
        case PRINT_NODE:
                executePrint(root);
            break;
        case IF_NODE:
                return executeIf(root);
            break;
        case IFELSE_NODE:
                return executeIfElse(root);
            break;
        case WHILE_NODE:
                return executeWhile(root);
            break;
        case FOR_NODE:
                return executeFor(root);
            break;
        case RETURN_NODE:
                return executeReturn(root);
            break;
        default: printf("ERROR: unknown root type \n"); break;
    }
    return execute(root->next);
}


/**
 * Returns a value
 * @see struct value {} at value.h
 * If its a terminal (identifier, integer or float) it returns the value
 * If its an expr type, it returns the value of the node
 * @param root: struct treeNode *        A pointer to a tree node
 */
struct value * executeFactor(struct treeNode * root) {
    if(root->nodetype == FUNCTION_NODE)
        return executeFunction(root);
    if(root->nodetype == IDENTIFIER_NODE)
        return root->node->id->symbol->value;
    if(root->nodetype == VALUE_NODE)
        return root->node->value->val;
    return executeExpr(root);
}


/**
 * Returns a value
 * @see valueOperation() at value.h
 * If it finds an operation type specification, 
 *      it returns the result of the operation between the left term and the factor on the right
 * If it doesn't, it executes the third option (expr) and returns its value
 * @param root: struct treeNode *        A pointer to a tree node
 */
struct value * executeTerm(struct treeNode * root){
    term_node * current = root->node->term;
    switch (current->operation){
        case MULTIPLICATION_OP:
                return valueOperation(
                    executeTerm(current->term), 
                    executeFactor(current->factor),  
                    MULTIPLICATION_OP
                );
            break;
        case DIVISION_OP:
                return valueOperation(
                    executeTerm(current->term), 
                    executeFactor(current->factor),  
                    DIVISION_OP
                );
            break;
        default:
            break;
    }
    return executeFactor(root);
}


/**
 * Returns a value
 * @see valueOperation() at value.h
 * If it finds an operation type specification, 
 *      it returns the result of the operation between the left expr and the term on the left
 * If it doesn't, it executes the third option (term) and returns its value
 * @param root: struct treeNode *        A pointer to a tree node
 */
struct value * executeExpr(struct treeNode * root){
    expr_node * expr = root->node->expr;
    switch (expr->operation){
        case ADDITION_OP:
                return valueOperation(
                    executeExpr(expr->expr), 
                    executeTerm(expr->term),  
                    ADDITION_OP
                );
            break;
        case SUBSTRACTION_OP:
                return valueOperation(
                    executeExpr(expr->expr), 
                    executeTerm(expr->term),  
                    SUBSTRACTION_OP
                );
            break;
        default:
            break;
    }
    return executeTerm(root);
}   


/**
 * Returns a boolean
 * @see valueEvaluation() at value.h
 * It returns the result of the operation between the expr on the left and the expr on the right
 * @param root: struct treeNode *        A pointer to a tree node
 */
bool executeExpression(struct treeNode * root){
    return valueEvaluation(
        executeExpr(root->node->expression->left), 
        executeExpr(root->node->expression->right), 
        root->node->expression->condition
    );
}

struct value * executeFunction(struct treeNode * root){
    struct funNode * _fun = root->node->fun; 
    struct tableNode * params = _fun->function_->params;
    struct treeNode * _attr = _fun->attributes;
    while(params != NULL){
        if(!setVariableValue(params, executeExpr(_attr)))
            printf("Error: params type mismatch. Setting to default value.\n");
        _attr = _attr->next;
        params = params->next;
    }
    struct value * toReturn = execute(_fun->function_->body);
    if(typesMatch(_fun->function_->returnValue, toReturn)){
        return toReturn;
    }
    if(_fun->function_->returnValue->type == TYPE_INT)
        return getInteger(0);
    if(_fun->function_->returnValue->type == TYPE_FLOAT)
        return getFloat(0.0);
}

struct value * executeReturn(struct treeNode * root){
    return executeExpr(root->node->return_->expr);
}


/**
 * It uses C if statement, 
 * The evaluation of the condition is performed by executeExpression(),
 * Then, if true, its branch is executed as normal tree node
 * @param root: struct treeNode *        A pointer to a tree node
 */
struct value * executeIf(struct treeNode * root){
    if(executeExpression(root->node->if_->condition)){
        return execute(root->node->if_->statement);
    }
    return getInteger(0);
}


/**
 * It uses C if else statement, 
 * The evaluation of the condition is performed by executeExpression(),
 * Then, if true, its branch is executed as normal tree node,
 * if false, just execute the else branch as a normal tree node
 * @param root: struct treeNode *        A pointer to a tree node
 */
struct value * executeIfElse(struct treeNode * root){
    if(executeExpression(root->node->if_else->condition)){
        return execute(root->node->if_else->if_statement);
    } else {
        return execute(root->node->if_else->else_statement);
    }
}


/**
 * It uses C while statement, 
 * The evaluation of the condition is performed by executeExpression(),
 * Then, if true, its branch is executed as normal tree node
 * @param root: struct treeNode *        A pointer to a tree node
 */
struct value * executeWhile(struct treeNode * root){
    while(executeExpression(root->node->while_->condition)){
        return execute(root->node->while_->statement);
    }
    return getInteger(0);
}


/**
 * It uses C for statement, 
 * @see getSetNode() at syntax_tree.h
 * @see setVariableValue() at symbol_tree.h
 * Create an executable setNode from the for_ node: id and id_value. Pass a Set execution as first parameter.
 * Then, evaluate the condition executing for_ node: to as a normal Expression statement
 * Increment its variable by setting the variables value directly into the symbol table
 * Finally, execute the for_'s branch as a normal tree node 
 * @param root: struct treeNode *        A pointer to a tree node
 */
struct value * executeFor(struct treeNode * root){
    struct treeNode * set = getSetNode(
        root->node->for_->id, 
        root->node->for_->id_value
    );
    struct tableNode * var = root->node->for_->id->node->id->symbol;
    for(
        executeSet(set); 
        executeExpression(root->node->for_->to);
        setVariableValue(
            var, 
            executeExpr(root->node->for_->step)
        )
    ){
        return execute(root->node->for_->do_);
    }
    return getInteger(0);
}


/**
 * @see printValue() at value.h 
 * Executes a normal Expr node and send its value to a special method which will print the value
 * Depeding on the variable type, the printing format changes
 * @param root: struct treeNode *        A pointer to a tree node
 */
void executePrint(struct treeNode * root){
    printValue(executeExpr(root->node->print->expr));
    printf("\n");
}


/**
 * @see setVariableValue() at symbol_tree.h
 * @note If the input doesn't match the variable type, default value will be 0
 * @param root: struct treeNode *        A pointer to a tree node
 */
void executeRead(struct treeNode * root){
    struct treeNode * readId = root->node->read->id;
    struct tableNode * var = readId->node->id->symbol;
    struct value * val = var->value;
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


/**
 * @see setVariableValue() at symbol_tree.h
 * @note If the input doesn't match the variable type, default value will be 0
 * @param root: struct treeNode *        A pointer to a tree node
 */
void executeSet(struct treeNode * root){
    id_node * id = root->node->set->id->node->id;
    struct treeNode * expr = root->node->set->expr;
    struct tableNode * var = id->symbol;
    if(!setVariableValue(var, executeExpr(expr))){
        printf("Error: variable type mismatch\n");
    }
}