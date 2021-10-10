#include "mathlib.h"

#include <stdlib.h>

double Pow(double n, double m) { //n raised by power of m
    double storeResult = 1;
    for (double term = 0; term < m; term++) {
        storeResult = storeResult * n;
    }
    return storeResult;
}


    int track_term[1];
    

    double pi_bbp(void) {
        int k = 0;
	double bbp_formula = 0;
	double bbp_total = 0;
        while (1) {
             bbp_formula = Pow(16, -k)
                                 * ((4 / (8 * k + 1)) - (2 / (8 * k + 4)) - (1 / (8 * k + 5))
                                     - (1 / (8 * k + 6))); if (bbp_formula < EPSILON) {
                break;
            }
            bbp_total += bbp_formula;
            k += 1;
            track_term[0] += 1;
        }
        return bbp_total;
    }

    double pi_bbp_term(void) {
        return track_term[0];
    }

