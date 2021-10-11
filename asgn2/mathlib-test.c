#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "aebmrvnsh?"

int main(int argc, char **argv) {
    double call_e = e();
    double call_madhava = pi_madhava();
    double call_viete = pi_viete();
    double call_bbp = pi_bbp();
    double call_euler = pi_euler();
    int opt = 0;
    bool got_a = false;
    bool got_e = false;
    bool got_b = false;
    bool got_m = false;
    bool got_r = false;
    bool got_v = false;
    bool got_n = false;
    bool got_s = false;
    bool got_h = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) { //get input from command prompt
        switch (opt) {
        case 'a': got_a = true; break;
        case 'e': got_e = true; break;
        case 'b': got_b = true; break;
        case 'm': got_m = true; break;
        case 'r': got_r = true; break;
        case 'v': got_v = true; break;
        case 'n': got_n = true; break;
        case 's': got_s = true; break;
        case 'h': got_h = true; break;
        case '?':
            printf("SYNOPSIS\n\tA test harness for the small numerical "
                   "library.\n\nUSAGE\n\t./mathlib-test [-aebmrvnsh]\n\nOPTIONS\n");
            printf("  -a   Runs all tests.\n");
            printf("  -e   Runs e test.\n");
            printf("  -b   Runs BBP pi test.\n");
            printf("  -m   Runs Madhava pi test.\n");
            printf("  -r   Runs Euler pi test.\n");
            printf("  -v   Runs Viete pi test.\n");
            printf("  -n   Runs Newton square root tests.\n");
            printf("  -s   Print verbose statistics.\n");
            printf("  -h   Display program synopsis and usage.\n");
            return 0;
        }
    }
    if (got_a) {
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", call_e, M_E, M_E - call_e);
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", call_euler, M_PI,
            absolute(call_euler - M_PI));
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", call_bbp, M_PI,
            absolute(call_bbp - M_PI));
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", call_madhava, M_PI,
            absolute(call_madhava - M_PI));
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", call_viete, M_PI,
            absolute(call_viete - M_PI));
        for (double b = 0; b < 10; b += 0.1) {
            printf("sqrt_newton(%2.6lf) = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", b,
                sqrt_newton(b), sqrt(b), absolute(sqrt(b) - sqrt_newton(b)));
        }
    }

    if (got_e) {
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", call_e, M_E,
            absolute(M_E - call_e));
        if (got_s) {
            printf("e() terms = %d\n", e_terms());
        }
    }
    if (got_b) {
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", call_bbp, M_PI,
            absolute(call_bbp - M_PI));
        if (got_s) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }
    if (got_m) {
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", call_madhava, M_PI,
            absolute(call_madhava - M_PI));
        if (got_s) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }
    if (got_r) {
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", call_euler, M_PI,
            absolute(call_euler - M_PI));
        if (got_s) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }
    if (got_v) {
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", call_viete, M_PI,
            absolute(call_viete - M_PI));
        if (got_s) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }
    if (got_n) {
        for (double z = 0; z < 10; z += 0.1) {
            printf("sqrt_newton(%2.6lf) = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", z,
                sqrt_newton(z), sqrt(z), absolute(sqrt(z) - sqrt_newton(z)));
        }
    }

    if (got_h) {
        printf("SYNOPSIS\n\tA test harness for the small numerical "
               "library.\n\nUSAGE\n\t./mathlib-test [-aebmrvnsh]\n\nOPTIONS\n");
        printf("  -a   Runs all tests.\n");
        printf("  -e   Runs e test.\n");
        printf("  -b   Runs BBP pi test.\n");
        printf("  -m   Runs Madhava pi test.\n");
        printf("  -r   Runs Euler pi test.\n");
        printf("  -v   Runs Viete pi test.\n");
        printf("  -n   Runs Newton square root tests.\n");
        printf("  -s   Print verbose statistics.\n");
        printf("  -h   Display program synopsis and usage.\n");
    }

    return 0;
}
