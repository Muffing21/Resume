#include "mathlib.h"

#include <assert.h>
#include <stdlib.h>

int viete_term_tracker[1];
double pi_viete(void) {

    int k = 1;

    double viete_total = 1;
    double viete_top_part = 0;
    double viete_formula = 0;

    while (1) {

        viete_top_part = sqrt_newton(2 + viete_top_part);

        viete_formula = viete_top_part / 2;

        if ((absolute(viete_formula - 1))
            < EPSILON) { //exit condition if term value and difference of 1 is less than epsilon
            break;
        }
        viete_total *= viete_formula;
        viete_term_tracker[0] += 1;
        k += 1;
    }
    return 2 / viete_total;
}

int pi_viete_factors(void) {
    return viete_term_tracker[0];
}
