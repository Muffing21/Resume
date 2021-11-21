#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <sys/stat.h>

#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#define OPTIONS           "b:i:n:d:s:vh"
#define default_iteration 50

//-b: specifies the minimum bits needed for the public modulus n
//-i: specifies the number of Miller-Rabin iterations for testing primes (default: 50)
//-n: pbfile: specifies the public key file (default: rsa.pub)
//-d: pvfile: specifies the private key file (default: rsa.priv)
//-s: specifies the random seed for the random state initialization (default: the seconds since the unix epoch, given time(NULL))
//-v: enables verbose output
//-h: displays program synopsis and usage

int main(int argc, char **argv) {

    char *private_file = "rsa.priv";
    char *public_file = "rsa.pub";
    uint64_t seed = time(NULL);
    uint64_t iters = 50;
    uint64_t nbits = 256;
    mpz_t p;
    mpz_t q;
    mpz_t n;
    mpz_t e;
    mpz_t d;
    mpz_t s;
    mpz_t m;

    mpz_inits(p, q, n, e, d, s, m, NULL); //dont forget to clear

    int opt = 0;

    bool get_h = false;
    bool get_n = false;
    bool get_d = false;
    bool get_s = false;
    bool get_b = false;
    bool get_i = false;
    bool get_v = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': get_h = true; break;

        case 'n':
            get_n = true;
            strcpy(public_file,
                optarg); //this way we can write into a file but if no file then create and write in it
            break;

        case 'd':
            get_d = true;
            strcpy(private_file, optarg);
            break;

        case 's':
            get_s = true;
            seed = atoi(optarg);
            if ((seed = atoi(optarg)) == 0) {
                printf("invalid seed. Try again.");
            }
        case 'b':
            get_b = true;
            nbits = atol(optarg);
            break;
        case 'i':
            get_i = true;
            iters = atoi(optarg);
            break;
        case 'v': get_v = true; break;
        }
    }
    FILE *pv_file = fopen(private_file, "w+");
    FILE *pb_file = fopen(public_file, "w+");

    fchmod(fileno(pv_file), 0600);
    randstate_init(seed);

    rsa_make_pub(p, q, n, e, nbits, iters);
    rsa_make_priv(d, e, p, q);

    mpz_set_str(m, getenv("USER"), 62);
    rsa_sign(s, m, d, n);
    rsa_write_pub(n, e, s, getenv("USER"), pb_file); //check back on this
    rsa_write_priv(n, d, pv_file); //check back on this

    if (get_h) {
        printf("SYPNOSIS\n\tA Huffman encoder.\n\tCompresses a file using the Huffman coding "
               "algorith.\n\nUSAGE\n\t./encode [-h] [-i infile] [-o outfile]\n\nOPTIONS\n\t-h\t\t  "
               "           Program usage and help.\n\t -v             Print compression "
               "statistics.\n\t-i infile      Input file to compress.\n\t -o             Output of "
               "compressed data.\n");
    }

    if (get_v) {
        fprintf(stderr, "username: %s\n", getenv("USER"));
        gmp_fprintf(stderr,
            "the signature s: %Zd"
            "\n",
            s);
        gmp_fprintf(stderr,
            "the large prime p: %Zd"
            "\n",
            p);
        gmp_fprintf(stderr,
            "the second large prime q: %Zd"
            "\n",
            q);
        gmp_fprintf(stderr,
            "the public modulus n: %Zd"
            "\n",
            n);
        gmp_fprintf(stderr,
            "the public exponent e: %Zd"
            "\n",
            e);
        gmp_fprintf(stderr,
            "the private key d: %Zd"
            "\n",
            d);
    }

    randstate_clear();
    fclose(pv_file);
    fclose(pb_file);
    mpz_clears(p, q, n, e, d, s, m, NULL);
    return 0;
}
