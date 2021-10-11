#include "mathlib.h"

#include <limits.h>
#include <stdlib.h>

int e_term_tracker[1];

double e() {
    int k = 0;
    double factorial_total = 0;
    double e_total = 0;
    double e_formula = 0;

    while (1) {
        if (k == 0) { //first factorial 0! = 1
            factorial_total += 1;
            e_total += 1;

            k += 1;
            e_term_tracker[0] += 1;
        }

        factorial_total = factorial_total * k; //1 * 1
        e_formula = 1 / factorial_total;

        if (e_formula < EPSILON) {
            break;
        }
        e_total += e_formula;
        e_term_tracker[0] += 1;
        k += 1;
    }
    return e_total;
}
int e_terms() {
    return e_term_tracker[0];
}
