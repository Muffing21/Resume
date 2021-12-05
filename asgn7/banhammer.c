#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <regex.h>

#include "bv.h"
#include "ht.h"
#include "bf.h"
#include "bst.h"
#include "messages.h"
#include "node.h"
#include "parser.h"
#include "salts.h"
#include "speck.h"

#define OPTIONS "hst:f:"
#define WORD    "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]+)*"
//got this from resource folder and recommendations from discord

//-h prints out the program usage. Refer to the reference program in the resources repository for what to print
//-t size specifies that the hash table will have size entries (the default will be 2^16)
//-f size specifies that the Bloom filter will have size entries (default size: 2^20)
//-s will enable printing of stats to stdout
// avg binary BST, avg BST height, avg, branches traversed, hash table load, Bf load
int main(int argc, char **argv) {

    char buffer[100];
    char buffer2[100];

    int opt = 0;
    uint32_t hash_size = 65536;
    uint32_t bf_size = 1048576;
    FILE *badspeak = fopen("badspeak.txt", "r");
    FILE *newspeak = fopen("newspeak.txt", "r");

    bool get_h = false;
    bool get_t = false;
    bool get_f = false;
    bool get_s = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': get_h = true; break;

        case 't':
            get_t = true;
            hash_size = atoi(optarg);
            if (hash_size == 0) {
                printf("input something else please");
            }
            break;

        case 'f':
            get_f = true;
            bf_size = atoi(optarg);
            if (bf_size == 0) {
                printf("input something else please");
            }
            break;

        case 's': get_s = true; break;
        }
    }

    //initialize bloom filter and hash table
    BloomFilter *bf = bf_create(bf_size);
    HashTable *ht = ht_create(hash_size);
    Node *bst = bst_create();
    Node *bst2 = bst_create();

    while (feof(badspeak) == 0) {
        fscanf(badspeak, "%s\n", buffer);
        bf_insert(bf, buffer);
        ht_insert(ht, buffer, NULL);
    }

    while (feof(newspeak) == 0) {
        fscanf(newspeak, "%s %s\n", buffer, buffer2);
        bf_insert(bf, buffer);
        ht_insert(ht, buffer, buffer2);
    }

    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    char *word = NULL;
    while ((word = next_word(stdin, &re)) != NULL) {
        Node *ht_look = ht_lookup(ht, word);
        if (bf_probe(bf, word) == true) {
            if (ht_look != NULL) {
                if (ht_look->newspeak != NULL) {
                    bst = bst_insert(bst, word, ht_look->newspeak);
                } else {
                    bst2 = bst_insert(bst, word, NULL);
                }
            }
        }
        printf("Word: %s\n", word);
    }

    if (get_h) { //change later
        printf("SYPNOSIS\n   Generates an RSA public/private key pair.\n\nUSAGE\n   ./keygen [-hv] "
               "[-b bits] -n pbfile -d pvfile\n\nOPTIONS\n   -h              Display program help "
               "and usage.\n   -v              Display verbose program output.\n   -b bits         "
               "Minimum bits needed for public key n (default: 256).\n   -i confidence   "
               "Miller-Rabin iterations for testing primes (default:50).\n   -n pbfile       "
               "Public key file (default: rsa.pub).\n   -d pvfile       Private key file (default: "
               "rsa.priv).\n   -s seed         Random seed for testing.");
    }

    if (get_s) {
        printf("average branches traversed: %lf\n", ht_avg_bst_size(ht));
        printf("Hash table load: %lf\n", ht_avg_bst_height(ht));
        printf("Average branches traversed: %lf\n", (double) branches / lookups);
        printf("hash table count: %lf\n", (double) ht_count(ht) / ht_size(ht));
        printf("Bloom filter load: %lf\n", (double) ht_count(ht) / ht_size(ht));
    }
    bf_delete(&bf);
    ht_delete(&ht);
    bst_delete(&bst);
    bst_delete(&bst2);
    clear_words();
    regfree(&re);
    return 0;
}
