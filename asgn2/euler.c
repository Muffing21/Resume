#include "mathlib.h"

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>


    int num_terms[1];

    double pi_euler(void) {
    	int k = 1;
    	double euler_sum = 0;
    	double euler_pow = 1;
    	double euler_formula = 0;
        while(1){
            euler_pow = (double) k * k;
            euler_formula = 1 / euler_pow;
            if (euler_formula < EPSILON) {

                break;
            }
            euler_sum += euler_formula; 
            num_terms[0] += 1;
            k += 1;
        }
        
        return sqrt_newton(6 * euler_sum);
    }

    int pi_euler_terms(void) {
        return num_terms[0];
    }

