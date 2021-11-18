#include "numtheory.h"
#include "randstate.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

#define gmp_fprintf __gmp_fprintf
#define gmp_fscanf  __gmp_fscanf

//mpz_sizeinbase(const mpz_t op, int base)
//return the size of op measured in number of digits in the given base. base can vary from 2 to 62. The sign of op is ignored, just the abs is used. The result will either be exact or 1 too big. If base is a power of 2, the result is always exact. If op is zero the return is always 1.

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {

    mpz_t random_variable;
    mpz_t p_variable;
    mpz_t q_variable;
    mpz_t totient;
    mpz_inits(random_variable, p_variable, q_variable, totient);

    if (mpz_sizeinbase(p, 2) >= nbits / 4
        && mpz_sizeinbase(p, 2)
               <= (3 * nbits) / 4) { //check if bits for p is in range, remaining goes to q
        mpz_sub_ui(q, n, mpz_sizeinbase(p, 2));
        uint64_t q_bits = nbits - mpz_sizeinbase(p, 2);
        make_prime(p, nbits, iters);
        make_prime(q, q_bits, iters);

        mpz_mul(n, p, q);

        while (1) {
            mpz_sub_ui(p_variable, p, 1); //computing n=(p-1)(q-1)
            mpz_sub_ui(q_variable, q, 1);
            mpz_mul(totient, p_variable, q_variable);

            mpz_urandomb(e, state, nbits); //finding suitable public exponent e
            gcd(random_variable, e, totient);
            if (mpz_cmp_ui(random_variable, 1) == 0) {
                break;
            }
        }
    }
    mpz_clears(random_variable, p_variable, q_variable, totient);
    return;
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile,
        "n: %Zx"
        "\n"
        "e: %Zx"
        "\n"
        "s: %Zx"
        "\n"
        "username: %c\n",
        n, e, s, username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "n: %Zx" "\n" "e: %Zx" "\n" "s: %Zx" "\n" "username: %c\n", n, e, s, username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t p_variable;
    mpz_t q_variable;
    mpz_t totient;
    mpz_inits(p_variable, q_variable, totient);

    mpz_sub_ui(p_variable, p, 1); //computing n=(p-1)(q-1)
    mpz_sub_ui(q_variable, q, 1);
    mpz_mul(totient, p_variable, q_variable);

    mod_inverse(d, e, totient);
    mpz_clears(p_variable, q_variable, totient);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile,
        "n: "
        "%Zx"
        "\nd: "
        "%#40Zx"
        "\n",
        n, d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile){
	gmp_fscanf(pvfile, "n: %Zx" "\n" "d: %Zx" "\n", n, d);
}

//void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n);

//void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e);

//void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n);

//void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d);

//void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n);

//bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n);
