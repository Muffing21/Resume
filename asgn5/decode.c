#include <inttypes.h>
#include "pq.h"
#include "code.h"
#include "stack.h"
#include "node.h"
#include "defines.h"
#include "io.h"
#include "header.h"
#include "huffman.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define OPTIONS "hvi:o:"

int main(int argc, char **argv) {

    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    int opt = 0;

    bool get_h = false;
    bool get_v = false;
    bool get_i = false;
    bool get_o = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': get_h = true; break;
        case 'i':
            get_i = true;
            infile = open(optarg, O_RDONLY);
            if (infile == -1) {
                exit(EXIT_FAILURE);
            }
            break;
        case 'o':
            get_o = true;
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
            break;
        case 'v': get_v = true; break;
        }
    }
    if (get_h) {
        printf("SYPNOSIS\n\tA Huffman encoder.\n\tCompresses a file using the Huffman coding "
               "algorith.\n\nUSAGE\n\t./encode [-h] [-i infile] [-o outfile]\n\nOPTIONS\n\t-h\t\t  "
               "           Program usage and help.\n\t -v             Print compression "
               "statistics.\n\t-i infile      Input file to compress.\n\t -o             Output of "
               "compressed data.\n");
    }

    uint8_t buffer[ALPHABET];
    uint8_t buffer2[ALPHABET];
    uint8_t temp = 0;
    uint64_t write_byte_counter = 0;
    read_bytes(infile, buffer, sizeof(Header));
    Header header = *((Header *) buffer);
    if (header.magic != MAGIC) {
        fprintf(stderr, "Invalid file");
        exit(EXIT_FAILURE);
    }
    fchmod(outfile, header.permissions);
    read_bytes(infile, buffer2, header.tree_size);
    Node *t = rebuild_tree(header.tree_size, buffer2);
    Node *t2 = t;
    while (read_bit(infile, &temp) == true && write_byte_counter < header.file_size) {
        if (temp == 1) {
            t2 = t2->right;
        }
        if (temp == 0) {
            t2 = t2->left;
        }
        //leaf
        if (t2->left == NULL && t2->right == NULL) {
            write_bytes(outfile, &(t2->symbol), 1);
            write_byte_counter += 1;
            t2 = t;
        }
    }
    if (get_v) {
        printf("Uncompressed file size: %" PRIu64 "\n"
               "Compressed file size: %" PRIu64 "Space saving: %.2f",
            bytes_read, bytes_written, 100 * (1 - ((float) bytes_written / bytes_read)));
    }
    delete_tree(&t);
    close(infile);
    close(outfile);
    return 0;
}
