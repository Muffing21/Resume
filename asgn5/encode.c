
#include <inttypes.h>
#include "pq.h"
#include "code.h"
#include "stack.h"
#include "node.h"
#include "defines.h"
#include "io.h"
#include "huffman.h"
#include "header.h"

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
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC); //this way we can write into a file but if no file then create then write so use OR operation
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
    
	uint64_t histogram[ALPHABET];
	histogram[0] = 1;
	histogram[255] =1;
	uint8_t temp_buf[ALPHABET];
	Code table[ALPHABET];

	struct stat temp;
	int unique_symbol = 0;
        
	int check_read = 0;
	while((check_read = read_bytes(infile, temp_buf, BLOCK)) != 0){
	   for (int i = 0; i < check_read; i++){
	   	if (histogram[temp_buf[i]] == 0){
	   		unique_symbol += 1;
	   	}
	   	histogram[temp_buf[i]] += 1;
	   }
	}
	Node *root = build_tree(histogram);
	build_codes(root, table); 
	fstat(infile, &temp);
	Header header;
	header.magic = MAGIC;
	header.permissions = temp.st_mode;
	header.tree_size = (3 * unique_symbol) - 1;
	header.file_size = temp.st_size;
	
	write_bytes(outfile, (uint8_t *) &header, sizeof(Header));
	dump_tree(outfile, root);
	Code c = code_init();
	while(read_bytes(infile, temp_buf, BLOCK) > 0){
		write_code(outfile, &c);
	
	}
	flush_codes(outfile);
	close(infile);
	close(outfile);
	delete_tree(&root);
	return 0;
}

//fchmod()
// This over here is a debugging function. Had big problem with dequeue and this prints out random characters and random frequencies and see if the ordering of things dequeued is correct by running ./encode

//    PriorityQueue *q = pq_create(10);
//    for (int i = 0; i < 10; i++) {
//        Node *n = node_create(random() % 26 + 65, random() % 15);
//        enqueue(q, n);
//    }
//    for (int i = 0; i < 10; i++) {
//        Node *temp2;
//        dequeue(q, &temp2);
//        fprintf(stderr, "Symbol: %c, Frequency: %" PRIu64 "\n", temp2->symbol, temp2->frequency);
//    }
