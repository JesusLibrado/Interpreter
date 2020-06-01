#include "value.h"

char * getTypeAsString(struct value *value){
    return (value->type == TYPE_INT)?"int":"float";
}

struct value* getInteger(int newInt) {
    struct value *newValue = (struct value *)malloc(sizeof(struct value));
    newValue->type = TYPE_INT;
    newValue->value.int_val = newInt;
    return newValue;
}

struct value* getFloat(float newFloat) {
    struct value *newValue = (struct value *)malloc(sizeof(struct value));
    newValue->type = TYPE_FLOAT;
    newValue->value.float_val = newFloat;
    return newValue;
}

bool typesMatch(struct value *v1, struct value *v2){
    return (v1->type == v2->type);
}

bool valueEvaluation(struct value *v1, struct value *v2, int condition){
    if(!typesMatch(v1, v2)) return false;

    if(v1->type == TYPE_INT){
        int v1_val = v1->value.int_val;
        int v2_val = v2->value.int_val;
        switch(condition){
            case LT_OP: return v1_val < v2_val;
                break;
            case GT_OP: return v1_val > v2_val;
                break;
            case LTE_OP: return v1_val <= v2_val;
                break;
            case GTE_OP: return v1_val >= v2_val;
                break;
            case EQUAL_OP: return v1_val == v2_val;
                break;
            default: return false; break;
        }
    }
    if(v1->type == TYPE_FLOAT){
        float v1_val = v1->value.float_val;
        float v2_val = v2->value.float_val;
        switch(condition){
            case LT_OP: return v1_val < v2_val;
                break;
            case GT_OP: return v1_val > v2_val;
                break;
            case LTE_OP: return v1_val <= v2_val;
                break;
            case GTE_OP: return v1_val >= v2_val;
                break;
            case EQUAL_OP: return v1_val == v2_val;
                break;
            default: return false; break;
        }
    }
}

struct value * valueOperation(struct value *v1, struct value *v2, int operation){
    if(!typesMatch(v1, v2)) return getInteger(0);

    if(v1->type == TYPE_INT){
        int v1_val = v1->value.int_val;
        int v2_val = v2->value.int_val;
        int result;
        switch(operation){
            case ADDITION_OP: result = v1_val + v2_val;
                break;
            case SUBSTRACTION_OP: result = v1_val - v2_val;
                break;
            case MULTIPLICATION_OP: result = v1_val * v2_val;
                break;
            case DIVISION_OP: result = v1_val / v2_val;
                break;
            default: result = 0; break;
        }
        return getInteger(result);
    }
    if(v1->type == TYPE_FLOAT){
        float v1_val = v1->value.float_val;
        float v2_val = v2->value.float_val;
        float result;
        switch(operation){
            case ADDITION_OP: result = v1_val + v2_val;
                break;
            case SUBSTRACTION_OP: result = v1_val - v2_val;
                break;
            case MULTIPLICATION_OP: result = v1_val * v2_val;
                break;
            case DIVISION_OP: result = v1_val / v2_val;
                break;
            default: result = 0; break;
        }
        return getFloat(result);
    }
}

void printValue(struct value * v){
    if(v->type ==TYPE_INT){
        int value = v->value.int_val;
        printf("%d", value);
    }
    if(v->type ==TYPE_FLOAT){
        float value = v->value.float_val;
        printf("%.2f", value);
    }
}