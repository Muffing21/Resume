#include "mathlib.h"

#include <stdlib.h>

int track_term[1];

double pi_bbp(void) {
    int k = 0;
    double bbp_formula = 0;
    double bbp_total = 0;
    double bbp_pow = 0;
    while (1) {
        if (k == 0) {
            bbp_formula = (4.0 / (8 * k + 1)) - (2.0 / (8 * k + 4)) - (1.0 / (8 * k + 5))
                          - (1.0 / (8 * k + 6));
            bbp_total += bbp_formula;
            bbp_pow += 1;
            k += 1;
            track_term[0] += 1;
        }
        bbp_formula = (1.0 / (16 * bbp_pow))
                      * ((4.0 / (8 * k + 1)) - (2.0 / (8 * k + 4)) - (1.0 / (8 * k + 5))
                          - (1.0 / (8 * k + 6)));
        if (absolute(bbp_formula) < EPSILON) {
            break;
        }
        bbp_total += bbp_formula;
        bbp_pow *= 16;
        k += 1;
        track_term[0] += 1;
    }
    return bbp_total;
}

int pi_bbp_terms(void) {
    return track_term[0];
}
