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

#define OPTIONS           "i:o:n:vh"
#define default_iteration 50

//-i: specifies the number of Miller-Rabin iterations for testing primes (default: 50)
//-o: specifies the output file to encrypt (default: stdout)
//-n: pbfile: specifies the public key file (default: rsa.pub)
//-v: enables verbose output
//-h: displays program synopsis and usage

int main(int argc, char **argv) {

    FILE *infile = stdin;
    FILE *outfile = stdout;
    char *public_file = "rsa.pub";
    char username[1000];
    mpz_t n;
    mpz_t e;
    mpz_t s;
    mpz_t m;

    mpz_inits(n, e, s, m, NULL); //dont forget to clear

    int opt = 0;

    bool get_h = false;
    bool get_n = false;
    bool get_i = false;
    bool get_v = false;
    bool get_o = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': get_h = true; break;
        case 'v': get_v = true; break;
        case 'i':
            get_i = true;
            infile = fopen(optarg, "r");
            break;

        case 'o':
            get_o = true;
            outfile = fopen(optarg, "r");
            break;
        case 'n':
            get_n = true;
            strcpy(public_file, optarg);
            break;
        }
    }
    FILE *pb_file = fopen(public_file, "w+");
    if (pb_file == NULL) {
        printf("failed to read the file\n");
        return 0;
    }

    rsa_read_pub(n, e, s, username, pb_file);
    if (rsa_verify(m, s, e, n) == false) {
        printf("failed to verify");
    }
    rsa_encrypt_file(infile, outfile, n, e);

    if (get_h) {
        printf(
            "SYPNOSIS\n   Encrypts data using RSA encryption.\n   Encrypted data is decrypted by "
            "the decrypt program.\n\nUSAGE\n   ./encrypt [-hv] [-i infile] [-i infile] [-o "
            "outfile] -n pubkey\n\nOPTIONS\n   -h              Display program help and usage.\n   "
            "-v              Display verbose program output.\n   -i infile       Input file of "
            "data to encrypt (default: stdin).\n   -o outfile      Output file for encrypted data "
            "(default: stdout).\n   -n pbfile       Public key file (default: rsa.pub).\n");
    }

    if (get_v) {
        fprintf(stderr, "username: %s\n", username);
        gmp_fprintf(stderr,
            "the signature s: %Zd"
            "\n",
            s);
        gmp_fprintf(stderr,
            "the public modulus n: %Zd"
            "\n",
            n);
        gmp_fprintf(stderr,
            "the public exponent e: %Zd"
            "\n",
            e);
    }

    fclose(pb_file);
    fclose(infile);
    fclose(outfile);
    mpz_clears(n, e, s, m, NULL);
    return 0;
}
