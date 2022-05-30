#include "bv.h"
#include <stdlib.h>
#include <stdio.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv) {
        bv->length = length;
        bv->vector = (uint8_t *) malloc((length / 8) + 1);
        if (!bv->vector) {
            free(bv);
            bv = NULL;
        }
    }
    return bv;
}

//remember to set the pointer to NULL after memory associated with bit vector is freed
void bv_delete(BitVector **bv) {
    if (*bv && (*bv)->vector) {
        free((*bv)->vector);
        free(*bv);
        (*bv)->vector = NULL;
        *bv = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

//from asignment 5 code.c
bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i > bv->length) {
        return false;
    }
    uint8_t shift_left = 00000001 << i % 8;
    uint8_t bit_masking = shift_left | bv->vector[i / 8];
    bv->vector[i / 8] = bit_masking;
    return true;
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i > bv->length) {
        return false;
    }
    uint8_t shift_left = ~(00000001 << i % 8);
    uint8_t bit_masking = shift_left & bv->vector[i / 8];
    bv->vector[i / 8] = bit_masking;
    return true;
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i > bv->length) {
        return false;
    }
    uint8_t shift_left = 00000001 << (i % 8);
    uint8_t bit_masking = shift_left & bv->vector[i / 8];
    uint8_t shift_right = bit_masking >> (i % 8);
    return shift_right;
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i++) {
        if (bv_get_bit(bv, i) == true) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }
}
