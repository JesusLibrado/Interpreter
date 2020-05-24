#include "value.h"

variable_value* getInteger(int newInt) {
    variable_value *newValue = (variable_value *)malloc(sizeof(variable_value));
    newValue->type = TYPE_INT;
    newValue->value.int_val = newInt;
    return newValue;
}

variable_value* getFloat(float newFloat) {
    variable_value *newValue = (variable_value *)malloc(sizeof(variable_value));
    newValue->type = TYPE_FLOAT;
    newValue->value.float_val = newFloat;
    return newValue;
}

bool typesMatch(variable_value *v1, variable_value *v2){

}