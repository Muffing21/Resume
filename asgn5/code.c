#include "code.h"
#include <inttypes.h>
#include "defines.h"
#include <stdbool.h>

//typedef struct {
//    uint32_t top;
//    uint8_t bits[MAX_CODE_SIZE];
//} Code;

//I watched christian's video
Code code_init(void) {
    Code c = { .top = 0, .bits = { 0 } };
    return c;
}

uint32_t code_size(Code *c) {
    //returns the size of the code, which is exactly the number of bits pushed into Code
    return c->top;
}

bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    }
    return false;
}

bool code_full(Code *c) {
    if (c->top == ALPHABET) {
        return true;
    }
    return false;
}

bool code_set_bit(Code *c, uint32_t i) {
    // check range of i against ALPHABET from defines.h
    if (i > ALPHABET) {
        return false;
    }
    uint8_t shift_left = 00000001 << i % 8;
    uint8_t bit_masking = shift_left | c->bits[i / 8];
    c->bits[i / 8] = bit_masking;
    return true;
}

bool code_clr_bit(Code *c, uint32_t i) {
    //similar to set
    if (i > ALPHABET) {
        return false;
    }
    uint8_t shift_left = ~(00000001 << i % 8);
    uint8_t bit_masking = shift_left & c->bits[i / 8];
    c->bits[i / 8] = bit_masking;
    return true;
}

bool code_get_bit(Code *c, uint32_t i) {
    // similar to set
    if (i > ALPHABET) {
        return false;
    }
    uint8_t shift_left = 00000001 << i % 8;
    uint8_t bit_masking = shift_left & c->bits[i / 8];
    uint8_t shift_right = bit_masking >> i % 8;
    return shift_right;
}

bool code_push_bit(Code *c, uint8_t bit) {
    //return false if the Code is full prior to pushing a bit and true otherwise to indicate successful push
    //check 0th bit to clear it else set it

    if (code_full(c) == true) {
        return false;
    }
    if (bit == 1) {
        code_set_bit(c, c->top);
    }
    if (bit == 0) {
        code_clr_bit(c, c->top);
    }
    c->top += 1;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    //return false if Code is empty prior to popping a bit and true to indicate successful pop
    if (code_empty(c) == true) {
        return false;
    }
    c->top -= 1;
    *bit = code_get_bit(c, c->top);
    return true;
}
