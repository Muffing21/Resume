
#include "mathlib.h"

#include <stdlib.h>

#include <assert.h>

    int iteration_track[1];

    double sqrt_newton(double x) { //function made by professor
        double y = 1.0;
        assert(x >= 0);
        for (double guess = 0.0; absolute(y - guess) > EPSILON; y = (y + x / y) / 2.0) {
            guess = y;
            iteration_track[0] += 1;
        }
        return y;
    }
    int sqrt_newton_iters(void) {
        return iteration_track[0];
    }


