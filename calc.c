#include "mathlib.h"
#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char **argv) {
    int opt;
    int mflag = 0;
    opt = getopt(argc, argv, "hm");
    if (opt == 'h') {
        fprintf(stdout, USAGE, argv[0]);
        return 0;
    } else if (opt == '?') {
        fprintf(stdout, USAGE, argv[0]);
        return 1;
    } else {
        mflag = 1;
    }

    char buff[1024];
    stack_clear();
    fprintf(stderr, "> ");
    char *expr = fgets(buff, 1024, stdin);

    // while not EOF, expr pointer is not null
    while (expr != NULL) {
        expr[strlen(expr) - 1] = '\0';
        char *saveptr;
        bool error = false;
        const char *token = strtok_r(expr, " ", &saveptr);
        // int o1 = 0;
        // int o2 = 0;
        // int o3 = 0;
        while (token != NULL && !error) {
            double *res = calloc(sizeof(double), 1);

            if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                // if (isdigit(token[0])) {
                if (parse_double(token, res)) {
                    // o1 ++;
                    if (!stack_push(*res)) {
                        error = true;
                        fprintf(stderr, ERROR_NO_SPACE, *res);
                    }
                    free(res);
                } else {
                    fprintf(stderr, ERROR_BAD_CHAR, *token);
                }
            } else if (strlen(token) == 1) {
                if (*token == 's' || *token == 'c' || *token == 't' || *token == 'a'
                    || *token == 'r') {
                    // o3 ++;
                    if (mflag == 1) {
                        if (!apply_unary_operator(libm_unary_operators[(int) *token])) {
                            error = true;
                            fprintf(stderr, ERROR_UNARY_OPERATOR);
                        }
                    } else {
                        if (!apply_unary_operator(my_unary_operators[(int) *token])) {
                            error = true;
                            fprintf(stderr, ERROR_UNARY_OPERATOR);
                        }
                    }

                } else if (*token == '+' || *token == '-' || *token == '*' || *token == '/'
                           || *token == '%') {
                    // o2 ++;
                    if (!apply_binary_operator(binary_operators[(int) *token])) {
                        error = true;
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                    }
                } else {
                    fprintf(stderr, ERROR_BAD_CHAR, *token);
                    error = true;
                }
            } else {
                if (strlen(token) > 2) {
                    fprintf(stderr, ERROR_BAD_CHAR, *token);

                } else {
                    fprintf(stderr, ERROR_BAD_CHAR, *token);
                }
                error = true;
            }
            token = strtok_r(NULL, " ", &saveptr);
        } // first while
        if (!error) {
            // if (o1 > o2) {
            //     // printf("%d", o2);
            stack_print();
            fprintf(stdout, "\n");
            // }
        } //if
        stack_clear();
        fprintf(stderr, "> ");
        expr = fgets(buff, 1024, stdin);
    } //exp
    return 0;
}
