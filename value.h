#include <stdlib.h>
#include <stdbool.h>

#define TYPE_INT 1
#define TYPE_FLOAT 2

union valueOptions {
    int int_val;
    float float_val;
};

struct variableValue {
    int type;
    union valueOptions value;
}typedef variable_value;

variable_value * getInteger(int);
variable_value * getFloat(float);
bool typesMatch(variable_value *, variable_value *);