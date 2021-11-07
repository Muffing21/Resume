#include "io.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h> //read() and write()
#include <fcntl.h> //open() and close()
#include <sys/types.h>
#include "defines.h"
#include "code.h"

static uint16_t index_counter = 0;
static uint8_t buf[BLOCK];
static uint32_t read_bit_buffer_size = 0;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    //read attempts to read up to count bytes from from file descriptor fd into the buffer starting at buf
    //ssize_t read(int fd, void *buf, size_t count)
    ssize_t read_file = 0;
    for (int i = 0; i < nbytes; i++) {
        read_file += read(infile, buf, nbytes);
        if (read_file == 0) {
            return read_file;
        }
    }
    return read_file;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    //writes up to count bytes from the buffer starting at buf to the file referred to by the file descriptor fd
    // ssize_t write(int fd, const void *buf, size_t count);
    ssize_t write_file = 0;
    for (int8_t i = 0; i < nbytes; i++) {
        write_file += write(outfile, buf, nbytes);
        if (write_file == 0) {
            return write_file;
        }
    }
    return write_file;
}
bool read_bit(int infile, uint8_t *bit) {
    uint8_t *bit_now = &buf[index_counter];
    if (index_counter / 8 == 0) {
        read_bit_buffer_size = read_bytes(infile, buf, BLOCK);
        if (read_bit_buffer_size == 0) {
            return false;
        }
    }

    uint8_t shift_left = 00000001 << index_counter % 8;
    uint8_t bit_mask = shift_left & *bit_now;
    uint8_t shift_right = bit_mask >> index_counter % 8;
    *bit = shift_right;
    index_counter += 1;

    if (index_counter == 8 * read_bit_buffer_size) {
        index_counter = 0;
    }
    return true;
}

void write_code(int outfile, Code *c) {
    uint8_t *current_bit = &buf[index_counter];

    index_counter += 1;
    if (*current_bit == 1) {
        uint8_t left_shift = 00000001 << index_counter % 8;
        *current_bit = left_shift | *current_bit;
    }
    if (*current_bit == 0) {
        uint8_t shift_clear = ~(00000001 << index_counter % 8);
        *current_bit = shift_clear & *current_bit;
    }
    for (uint32_t i = 0; i < c->top; i++) {
        *current_bit = c->bits[i];
    }
    if (index_counter == 8 * BLOCK) {
        write_bytes(outfile, buf, BLOCK);
    }
}

void flush_codes(int outfile) {
    //flush bits out of buffer if not empty
    if (index_counter > 0) {
        //convert index into bytes
        write_bytes(outfile, buf, index_counter);
    }
}
