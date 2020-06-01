#ifndef _VALUE_HEADER_
#define _VALUE_HEADER_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define TYPE_INT            100
#define TYPE_FLOAT          200

#define ADDITION_OP         110
#define SUBSTRACTION_OP     120
#define MULTIPLICATION_OP   130
#define DIVISION_OP         140

#define LT_OP               150
#define GT_OP               160
#define LTE_OP              170
#define GTE_OP              180
#define EQUAL_OP            190


struct variableValue {
    int type;
    union {
        int int_val;
        float float_val;
    } value;
};

char * getTypeAsString(struct variableValue *);
void printValue(struct variableValue *);
struct variableValue * getInteger(int);
struct variableValue * getFloat(float);
struct variableValue * valueOperation(struct variableValue *, struct variableValue *, int);
bool typesMatch(struct variableValue *, struct variableValue *);
bool valueEvaluation(struct variableValue *, struct variableValue *, int);

#endif