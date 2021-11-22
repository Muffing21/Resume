#include "numtheory.h"
#include "randstate.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <unistd.h>

#define gmp_fprintf __gmp_fprintf
#define gmp_fscanf  __gmp_fscanf

//mpz_sizeinbase(const mpz_t op, int base)
//return the size of op measured in number of digits in the given base. base can vary from 2 to 62. The sign of op is ignored, just the abs is used. The result will either be exact or 1 too big. If base is a power of 2, the result is always exact. If op is zero the return is always 1.

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {

    mpz_t random_variable;
    mpz_t p_variable;
    mpz_t q_variable;
    mpz_t totient;
    mpz_t p_bits;
    mpz_t q_bits;
    mpz_t temp;
    mpz_t n_bits;
    mpz_t temp69;
    mpz_inits(random_variable, p_variable, q_variable, totient, temp, p_bits, q_bits, n_bits,
        temp69, NULL);
    mpz_set_ui(n_bits, nbits);

    mpz_fdiv_q_ui(temp, n_bits, 2);
    mpz_urandomm(p_bits, state, temp);
    mpz_fdiv_q_ui(temp, n_bits, 4);
    mpz_add(p_bits, p_bits, temp);

    mpz_sub(q_bits, n_bits, p_bits);
    //mpz_urandomm(q_bits, state, q_bits);
    mpz_add_ui(p_bits, p_bits, 1);
    mpz_add_ui(q_bits, q_bits, 1);

    make_prime(p, mpz_get_ui(p_bits), iters);
    make_prime(q, mpz_get_ui(q_bits), iters);

    mpz_mul(n, p, q);
    while (1) {
        mpz_sub_ui(p_variable, p, 1); //computing n=(p-1)(q-1)
        mpz_sub_ui(q_variable, q, 1);
        mpz_mul(totient, p_variable, q_variable);

        mpz_urandomb(e, state, nbits); //finding suitable public exponent e
        mpz_set(temp69, e);
        gcd(random_variable, temp69, totient);
        if (mpz_cmp_ui(random_variable, 1) == 0) {
            break;
        }
    }

    mpz_clears(random_variable, p_variable, q_variable, totient, temp, p_bits, q_bits, n_bits,
        temp69, NULL);
    return;
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile,
        "%Zx"
        "\n"
        "%Zx"
        "\n"
        "%Zx"
        "\n"
        "%s\n",
        n, e, s, username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile,
        "%Zx"
        "\n"
        "%Zx"
        "\n"
        "%Zx"
        "\n"
        "%s\n",
        n, e, s, username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t p_variable;
    mpz_t q_variable;
    mpz_t totient;
    mpz_inits(p_variable, q_variable, totient, NULL);

    mpz_sub_ui(p_variable, p, 1); //computing n=(p-1)(q-1)
    mpz_sub_ui(q_variable, q, 1);
    mpz_mul(totient, p_variable, q_variable);

    mod_inverse(d, e, totient);
    mpz_clears(p_variable, q_variable, totient, NULL);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile,
        "%Zx"
        "\n"
        "%Zx"
        "\n",
        n, d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile,
        "%Zx"
        "\n"
        "%Zx"
        "\n",
        n, d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    //	mpz_t temp;
    //	mpz_t block_k;
    //	mpz_t size_n;
    mpz_t m;
    mpz_t c;

    mpz_inits(m, c, NULL);
    ssize_t j = 0;

    //	mpz_set_ui(size_n, mpz_sizeinbase(n, 2));
    //	mpz_sub_ui(temp, size_n, 2);
    //	mpz_fdiv_q_ui(block_k, temp, 8);
    uint8_t block_k = (mpz_sizeinbase(n, 2) - 2) / 8;

    uint8_t *block = (uint8_t *) malloc(block_k);
    block[0] = 0xFF;
    while ((j = read(fileno(infile), block + 1, block_k - 1)) != 0) {
        mpz_import(m, j + 1, 1, sizeof(uint8_t), 1, 0, block);
        rsa_encrypt(c, m, e, n);
        gmp_fprintf(outfile,
            "%Zx"
            "\n",
            c);
    }
    mpz_clears(m, c, NULL);
    free(block);
    return;
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t c;
    mpz_t m;
    size_t j = 0;
    mpz_inits(c, m, NULL);

    uint8_t block_k = (mpz_sizeinbase(n, 2) - 2) / 8;

    uint8_t *block = (uint8_t *) malloc(block_k);
    while (gmp_fscanf(infile, "%Zx\n", c) > 0) {
    	rsa_decrypt(m, c, d, n);
        mpz_export(block, &j, 1, sizeof(uint8_t), 1, 0, m);
        write(fileno(outfile), block + 1, j - 1);
    }
    mpz_clears(c, m, NULL);
    free(block);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);
    if (mpz_cmp(t, m) == 0) {
        mpz_clear(t);
        return true;
    }
    mpz_clear(t);
    return false;
}
