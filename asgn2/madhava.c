#include "mathlib.h"

#include <limits.h>
#include <math.h>
#include <stdlib.h>

int madhava_term_tracker[1];

double pi_madhava(void) {
    double madhava_pow = 0;
    double madhava_total = 0;
    double madhava_formula = 0;

    int k = 0;
    while (1) {
        if (k == 0) {
            madhava_pow += 1;
            madhava_formula = madhava_pow / (2 * k + 1);
            madhava_total += madhava_formula;
            k += 1;
            madhava_term_tracker[0] += 1;
        }
        madhava_pow *= 1.0 / (-3);
        madhava_formula = madhava_pow / (2 * k + 1);

        if (absolute(madhava_formula)
            < EPSILON) { //absolute because the formula goes positive and negative
            break;
        }
        madhava_total += madhava_formula;
        k += 1;
        madhava_term_tracker[0] += 1;
    }
    return sqrt_newton(12) * madhava_total;
}

int pi_madhava_terms(void) {
    return madhava_term_tracker[0];
}
