#include "bf.h"
#include "bv.h"
#include <stdlib.h>
#include "salts.h"
#include "speck.h"
#include <stdio.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = SALT_PRIMARY_LO;
        bf->primary[1] = SALT_PRIMARY_HI;
        bf->secondary[0] = SALT_SECONDARY_LO;
        bf->secondary[1] = SALT_SECONDARY_HI;
        bf->tertiary[0] = SALT_TERTIARY_LO;
        bf->tertiary[1] = SALT_TERTIARY_HI;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
        free(*bf);
        free((*bf)->filter);
        *bf = NULL;
    }
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {

    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));

    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));

    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {

    if (bv_get_bit(bf->filter, hash(bf->primary, oldspeak)) && bv_get_bit(bf->filter, hash(bf->secondary, oldspeak)) && bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak)) == true) {
        return true;
    }
    return false;
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i) == true) {
            count += 1;
        }
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
