#include "numtheory.h"
#include "randstate.h"
#include <gmp.h>
#define mpz_inits __gmpz_inits
//mpz_sub_ui(mpz_t rop, const mpz_t op1, unsigned long int op2)
//mpz_mul_ui(mpz_t rop, const mpz_t op1, unsigned long int op2)

void gcd(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t t;
    mpz_init(t);
    while (mpz_sgn(b)) {
        mpz_set(t, b);
        mpz_mod(b, a, b);
        mpz_set(a, t);
    }
    mpz_set(d, a);
}

void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    mpz_t r;
    mpz_t r_prime;
    mpz_t t;
    mpz_t t_prime;
    mpz_t q;
    mpz_t temp;
    mpz_t temp2;

    mpz_inits(r, r_prime, t, t_prime, q, temp, temp2, NULL);
    mpz_set(r, n);
    mpz_set(r_prime, a);
    mpz_set_ui(t, 0);
    mpz_set_ui(t_prime, 1);
    while (mpz_sgn(r_prime)) {
        mpz_fdiv_q(q, r, r_prime);

        mpz_set(temp2, r);
        mpz_set(r, r_prime);

        mpz_mul(temp, q, r_prime);
        mpz_sub(r_prime, temp2, temp);

        mpz_set(temp2, t);
        mpz_set(t, t_prime);
        mpz_mul(temp, q, t_prime);
        mpz_sub(t_prime, temp2, temp);
    }
    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set_ui(i, 0);
        return;
    }
    if (mpz_cmp_ui(t, 0) < 0) {
        mpz_add(t, t, n);
    }
    mpz_set(i, t);
    mpz_clears(r, r_prime, t, t_prime, q, temp, temp2, NULL);
}

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t v;
    mpz_t p;
    mpz_t temp;
    mpz_t temp69;
    mpz_t store_value_one;

    mpz_inits(v, p, temp, store_value_one, temp69, NULL);
    mpz_set_ui(v, 1);
    mpz_set(p, base);
    mpz_set(temp69, exponent);
    while (mpz_cmp_ui(temp69, 0) > 0) {
        if (mpz_odd_p(temp69) != 0) {
            mpz_mul(temp, v, p);
            mpz_mod(v, temp, modulus);
        }
        mpz_mul(temp, p, p);
        mpz_mod(p, temp, modulus);
        mpz_fdiv_q_ui(temp69, temp69, 2);
    }
    mpz_set(out, v);
    mpz_clears(v, p, temp, store_value_one, temp69, NULL);
}

bool is_prime(mpz_t n, uint64_t iters) {
    if (mpz_cmp_ui(n, 1) <= 0) {
        return false;
    }
    mpz_t r;
    mpz_t j;
    mpz_t s;
    mpz_t temp;
    mpz_t temp2;
    mpz_t y;
    mpz_t store_value_two;

    mpz_inits(r, j, temp, s, y, temp2, store_value_two, NULL);

    mpz_add_ui(store_value_two, store_value_two, 2);
    //TAKE N-1 AS THE STARTING POINT FOR R
    mpz_sub_ui(r, n, 1);
    mpz_set(temp2, r);

    //keep setting r to r/2 until r is odd
    while (mpz_even_p(r) != 0) {
        mpz_fdiv_q_ui(temp, r, 2);
        mpz_set(r, temp);
        mpz_add_ui(s, s, 1);
    }

    for (uint64_t i = 1; i < iters; i++) {

        mpz_urandomm(temp, state, n);
        pow_mod(y, temp, r, n);
        if (mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, temp2) != 0) {
            mpz_set_ui(j, 1);
            while (mpz_cmp(j, s) < 0 && mpz_cmp(y, temp2) != 0) {
                pow_mod(y, y, store_value_two, n);
                if (mpz_cmp_ui(y, 1) == 0) {
                    return false;
                }
                mpz_add_ui(j, j, 1);
            }
            if (mpz_cmp(y, temp2) != 0) {
                return false;
            }
        }
    }
    mpz_clears(r, j, temp, s, y, temp2, store_value_two, NULL);
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    while (!is_prime(p, iters) || mpz_sizeinbase(p, 2) < bits) {
        mpz_urandomb(p, state, bits);
    }
}
