#include "operators.h"

#include "messages.h"
#include "stack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

double operator_add(double lhs, double rhs) {
    return lhs + rhs;
}

double operator_sub(double lhs, double rhs) {
    return lhs - rhs;
}

double operator_mul(double lhs, double rhs) {
    return lhs * rhs;
}

double operator_div(double lhs, double rhs) {
    return lhs / rhs;
}

bool apply_unary_operator(unary_operator_fn op) {
    if (stack_size < 1) {
        // fprintf(stderr, ERROR_UNARY_OPERATOR);
        return false;
    }
    double x;
    assert(stack_pop(&x));
    // Calculate the value we should push to the stack
    double result = op(x);
    // printf("result: %.16f\n", result);
    assert(stack_push(result));
    return true;
}

bool apply_binary_operator(binary_operator_fn op) {
    // pops first two elements on the stack and calls op function with those two

    if (stack_size < 2) {
        // fprintf(stderr, ERROR_BINARY_OPERATOR);
        return false;
        // error handling should be done in calc
    }
    double rhs;
    assert(stack_pop(&rhs));
    double lhs;
    assert(stack_pop(&lhs));

    // assert(stack_pop(&x));

    double result = op(lhs, rhs);
    assert(stack_push(result));
    return true;
}

bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);
    if (endptr != s) {
        *d = result;
        return true;
    } else {
        return false;
    }
}
