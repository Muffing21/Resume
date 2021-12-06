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

    char buffer[500];  //create some buffer for fscanf
    char buffer2[500];
    bool bad_speak = false;   //these 2 bool variables are for checking which message from messages.h to print out
    bool right_speak = false;
    int opt = 0;
    uint32_t hash_size = 65536;
    uint32_t bloom_size = 1048576;
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
            bloom_size = atoi(optarg);
            if (bloom_size == 0) {
                printf("input something else please");
            }
            break;

        case 's': get_s = true; break;
        }
    }

    //initialize bloom filter and hash table
    //follow instructions of asgn doc
    BloomFilter *bf = bf_create(bloom_size);
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

    regex_t re;  //the following about 15 lines are from assignment doc
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
                    right_speak = true;                   //99 and 101 checks and sees if which kinda case we're dealing with, badspeak or newspeak
                } else {
                    bst2 = bst_insert(bst2, word, NULL);
                    bad_speak = true;
                }
            }
        }
    }

    if (!get_s) {    //I did this because in the case where -s is given by the user, only print the stats and nothing else, but since !s, prints out the messages
        if (bad_speak == true && right_speak == true) {
            printf("%s", mixspeak_message);
            bst_print(bst2);
            bst_print(bst);
        } else if (bad_speak == true) {
            printf("%s", badspeak_message);
            bst_print(bst2);
        } else if (right_speak == true) {
            printf("%s", goodspeak_message);
            bst_print(bst);
        }
    }

    if (get_h) { //change later
        printf("SYPNOSIS\n  A word filtering program for the GPRSC.\n  Filters out and reports bad words parsed from stdin.\n\nUSAGE\n  ./banhammer [-hs] [-t size] [-f size]\n\nOPTIONS\n  -h           Program usage and help.\n  -s           Print program statistics.\n  -t size size      Specify hash table size (default: 2^16).\n  -f size      Specify Bloom filter size (default: 2^20).\n");
    }
	//typecast so it does not round down
    if (get_s) {
        printf("Average BST size: %lf\n", ht_avg_bst_size(ht));
        printf("Average BST height: %lf\n", ht_avg_bst_height(ht));
        printf("Average branches traversed: %lf\n", (double) branches / lookups);
        printf("Hash table load: %lf%%\n", (double) 100 * ht_count(ht) / ht_size(ht));
        printf("Bloom filter load: %lf%%\n", (double) 100 * bf_count(bf) / bf_size(bf));
    }
    bf_delete(&bf);
    ht_delete(&ht);

    bst_delete(&bst);
    bst_delete(&bst2);
    clear_words();
    regfree(&re);
    return 0;
}
