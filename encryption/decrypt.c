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
    char *private_file = "rsa.pub";

    mpz_t n;
    mpz_t e;
    mpz_t d;

    mpz_inits(n, e, d, NULL); //dont forget to clear

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
            if (infile == NULL) {
                fprintf(stderr, "invalid file name");
            }
            break;

        case 'o':
            get_o = true;
            outfile = fopen(optarg, "w+");
            break;
        case 'n':
            get_n = true;
            private_file = strdup(optarg);
            break;
        }
    }

    FILE *pv_file = fopen(private_file, "r");
    if (get_n) {
        free(private_file);
    }
    if (pv_file == NULL) {
        printf("failed to read the file\n");
        exit(EXIT_FAILURE);
    }

    rsa_read_priv(n, d, pv_file); //read priv key from the opened file

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
        gmp_fprintf(stderr,
            "the public modulus n: %Zd"
            "\n"
            "%d"
            "\n",
            n, mpz_sizeinbase(n, 2));
        gmp_fprintf(stderr,
            "the private key e: %Zd"
            "\n"
            "%d"
            "\n",
            e, mpz_sizeinbase(e, 2));
    }
    rsa_decrypt_file(infile, outfile, n, d); //dont forget to close any opened files
    fclose(pv_file);
    fclose(infile);
    fclose(outfile);
    mpz_clears(n, e, d, NULL);
    return 0;
}
