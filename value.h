#ifndef _VALUE_HEADER_
#define _VALUE_HEADER_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define TYPE_INT 100
#define TYPE_FLOAT 200

#define ADDITION_OP 110
#define SUBSTRACTION_OP 120
#define MULTIPLICATION_OP 130
#define DIVISION_OP 140

#define LT_OP 150
#define GT_OP 160
#define LTE_OP 170
#define GTE_OP 180
#define EQUAL_OP 190


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
variable_value * valueOperation(variable_value *, variable_value *, int);
bool typesMatch(variable_value *, variable_value *);
bool valueEvaluation(variable_value *, variable_value *, int);

char * getTypeAsString(variable_value *);
void printValue(variable_value *);

#endif