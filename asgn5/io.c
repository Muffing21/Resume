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
uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

//help from christian

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    //read attempts to read up to count bytes from from file descriptor fd into the buffer starting at buf
    //ssize_t read(int fd, void *buf, size_t count)
    ssize_t read_file = 0;
    while (read_file < nbytes) {
        ssize_t byte_reads = read(infile, buf, nbytes);

        read_file += byte_reads;
        if (byte_reads == 0) {
            return read_file;
        }
    }
    bytes_read += read_file;
    return read_file;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    //writes up to count bytes from the buffer starting at buf to the file referred to by the file descriptor fd
    // ssize_t write(int fd, const void *buf, size_t count);
    ssize_t write_file = 0;
    while (write_file < nbytes) {
        ssize_t byte_writtens = write(outfile, buf, nbytes);
        write_file += byte_writtens;
        if (byte_writtens == 0) {
            return write_file;
        }
    }
    bytes_written += write_file;
    return write_file;
}
bool read_bit(int infile, uint8_t *bit) {
    uint8_t *bit_now = &buf[index_counter / 8];
    if (index_counter == 0) {
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
    uint8_t *current_bit = &buf[index_counter / 8];

    uint8_t get_bit = code_get_bit(c, index_counter);

    if (get_bit == 1) {
        uint8_t left_shift = 00000001 << index_counter % 8;
        *current_bit = left_shift | *current_bit;
    }
    if (get_bit == 0) {
        uint8_t shift_clear = ~(00000001 << index_counter % 8);
        *current_bit = shift_clear & *current_bit;
    }
    index_counter += 1;
    for (uint32_t i = 0; i < c->top; i++) {
        *current_bit = c->bits[i];
    }
    if (index_counter == 8 * BLOCK) {
        write_bytes(outfile, buf, BLOCK);
        index_counter = 0;
    }
}

void flush_codes(int outfile) {
    //flush bits out of buffer if not empty
    if (index_counter > 0) {
        //convert index into bytes
        write_bytes(outfile, buf, index_counter / 8);
        if (index_counter % 8 != 0) {
            write_bytes(outfile, &(buf[index_counter / 8]), 1);
        }
    }
}
