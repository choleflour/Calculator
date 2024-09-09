#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

double Abs(double x) {
    if (x < 0)
        x = -x;
    return x;
}

double Sqrt(double x) {
    // Check domain
    if (x < 0) {
        return nan("nan");
    }
    double old = 0.0;
    double new = 1.0;

    while (Abs(old - new) > EPSILON) {
        // Babylonian method
        old = new;
        new = 0.5 * (old + (x / old));
    }
    return new;
}
// x is the angle in randians, normalize inputs
double Sin(double x) {
    double sum = 0.0;
    double a = x;
    double b = 1.0;
    int count = 1;
    double term = 0.0;
    while (1) {
        if (count == 1)
            term = x;
        else {
            a *= x * x * -1;
            b *= (count) * (count - 1);
            term = a / b;
        }
        if (Abs(term) < EPSILON) {
            break;
        }
        sum += term;
        count += 2;
    }
    return sum;

    // // bool flag = false;
    // if (x == 0.0) {
    //     return 0.0;
    // }
    // while (x < 0) {
    //     // flag = true;
    //     x += 2 * M_PI;
    // }
    // while (x > 2 * M_PI) {
    //     x -= 2 * M_PI;
    // }
    // double sum = 0.0;
    // double d = 1.0;
    // double count = 1.0;
    // int sign = 0;
    // double n = x;
    // double term = 0;

    // while (1) {
    //     if (count == 1.0) {
    //         term = x;
    //     } else {
    //         d = (count) * (count - 1) * d;
    //         n = x * x * n;
    //         term = n / d;
    //         if (sign % 2 == 1) {
    //             term = -1 * term;
    //         }
    //     }
    //     if (Abs(term) < EPSILON)
    //         break;
    //     sum += term;
    //     count += 2;
    // }
    // // if (flag)
    // // return -1 * sum;
    // return sum;
}

double Cos(double x) {
    while (x < 0) {
        x += 2 * M_PI;
    }
    while (x > 2 * M_PI) {
        x -= 2 * M_PI;
    }

    // return 1 - Sin(x) * Sin(x);
    // double sum = 0.0;
    // double d = 1.0;
    // double count = 0.0;
    // int sign = 0;
    // double n = 1;
    // double term = 1.0;

    // while (1) {
    //     if (count == 1.0) {
    //         term = 1.0;
    //     } else {
    //         d = (count + 2) * (count + 1) * d;
    //         n = x * x * n;
    //         term =  n / d;
    //         if (sign % 2 == 1) {
    //         term = -1 * term;
    //         }

    //     }
    //     if (Abs(term) < EPSILON) break;
    //     sum += term;
    //     count += 2;
    // }
    // return sum;
    double sum = 0.0;
    double a = 1.0;
    double b = 1.0;
    int count = 0;
    double term = 0.0;
    while (1) {
        if (count == 0)
            term = 1.0;
        else {
            a *= x * x * -1;
            b *= (count) * (count - 1);
            term = a / b;
        }
        if (Abs(term) < EPSILON) {
            break;
        }
        sum += term;
        count += 2;
    }
    return sum;
}

double Tan(double x) {
    return Sin(x) / Cos(x);
}
