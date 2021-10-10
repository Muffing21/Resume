#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "aebmrvn"

int main(int argc, char **argv) {
    int opt = 0;
    bool got_a = false;
    bool got_e = false;
    bool got_b = false;
    bool got_m = false;
    bool got_r = false;
    bool got_v = false;
    bool got_n = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': got_a = true; break;
        case 'e': got_e = true; break;
        case 'b': got_b = true; break;
        case 'm': got_m = true; break;
        case 'r': got_r = true; break;
        case 'v': got_v = true; break;
        case 'n': got_n = true; break;
        }
    }
    if (got_a) {
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, M_E - e());
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI, absolute(pi_bbp() - M_PI));  
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI, absolute(pi_madhava() - M_PI));
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI, absolute(pi_euler() - M_PI));
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI, absolute(pi_viete() - M_PI));
        for(double b = 0; b < 10; b += 0.1){
    		printf("sqrt_newton(%2.6lf) = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", b, sqrt_newton(b), sqrt(b), absolute(sqrt(b) - sqrt_newton(b)));
        return 0;
        }
    }

    if (got_e) {
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, M_E - e());
        return 0;
    }
    if (got_b) {
    	printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI, pi_bbp() - M_PI);
        return 0;
    }
    if (got_m) {
    	printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI, absolute(pi_madhava() - M_PI));
    }
    if (got_r) {
    	printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI, absolute(pi_euler() - M_PI));
    }
    if (got_v) {
    	printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI, absolute(pi_viete() - M_PI));
    }
    if (got_n) {
        for(double z = 0; z < 10; z += 0.1){
    		printf("sqrt_newton(%2.6lf) = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", z, sqrt_newton(z), sqrt(z), absolute(sqrt(z) - sqrt_newton(z)));
    	}
    }
    return 0;
}
