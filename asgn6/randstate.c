#include <stdlib.h>
#include "randstate.h"
#include <gmp.h>

gmp_randstate_t state;

void randstate_init(uint64_t seed) {
    gmp_randseed_ui(state, seed);
    gmp_randinit_mt(state);
}

void randstate_clear(void) {
    gmp_randclear(state);
}
