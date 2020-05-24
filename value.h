#ifndef _VALUE_HEADER_
#define _VALUE_HEADER_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define TYPE_INT 1
#define TYPE_FLOAT 2

#define ADDITION_OP 10
#define SUBSTRACTION_OP 11
#define MULTIPLICATION_OP 12
#define DIVISION_OP 13

#define LT_OP 14
#define GT_OP 15
#define LTE_OP 16
#define GTE_OP 17
#define EQUAL_OP 18


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

bool valueEvaluation(variable_value *, variable_value *, int);
variable_value * valueOperation(variable_value *, variable_value *, int);

void printValue(variable_value *);

#endif