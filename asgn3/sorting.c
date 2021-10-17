
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "aeisqrnp"
//style and format came from TA eugene
//-a enables all sorting algorithms
//-e enables heap sort
//-i enables insertion sort
//-s enables shell sort
//-q enables quicksort
//-r set the random seed to seed.
//-n set the array size. The default size should be 100
//-p print out number of elements from the array. The default number of elements to print out should be 100
//if the size of the array is less than the specified number of elements to print, print out the entire array and nothing more
//-h for display help message

#define DEFAULT_SEED 13371453
#define default_size 100

int insert_counter = 0;

uint32_t element_size = default_size;
uint32_t the_seed = DEFAULT_SEED;

int main(int argc, char **argv) {
    int opt = 0;
    //	bool get_a = false;
    bool get_e = false;
    bool get_i = false;
    bool get_s = false;
    bool get_q = false;
    bool get_r = false;
    bool get_n = false;
    //	bool get_p = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            //		case 'a': get_a = true; break;
        case 'e': get_e = true; break;
        case 'i': get_i = true; break;
        case 's': get_s = true; break;
        case 'q': get_q = true; break;
        case 'r':
            get_r = true;
            the_seed = atoi(optarg);
            break;
        case 'n':
            get_n = true;
            element_size = atoi(optarg);
            break;
            //		case 'p': get_p = true; uint32_t limit_element = atoi(optarg); break;
        }
    }
    if (get_i) {

        uint32_t A[element_size];
        srandom(the_seed);
        for (uint32_t i = 0; i < element_size; i++) {
            A[i] = random() & 0x3FFFFFFF;
        }
        Stats x;
        reset(&x);
        insertion_sort(&x, A, element_size);
        printf("Insertion Sort, %d elements, %13" PRIu64 " moves, %13" PRIu64 " compares\n",
            element_size, x.moves, x.compares);
        for (uint32_t i = 0; i < element_size; i++) {
            printf("%13" PRIu32, A[i]);
            insert_counter += 1;
            if (insert_counter == 5) {
                printf("\n");
                insert_counter = 0;
            }
        }
    }
    if (get_s) {
        uint32_t A[element_size];
        srandom(the_seed);
        for (uint32_t i = 0; i < default_size; i++) {
            A[i] = random() & 0x3FFFFFFF;
        }
        Stats x;
        reset(&x);
        shell_sort(&x, A, element_size);
        printf("Shell Sort, %d elements, %13" PRIu64 " moves, %13" PRIu64 " compares\n",
            element_size, x.moves, x.compares);
        for (uint32_t i = 0; i < element_size; i++) {
            printf("%13" PRIu32, A[i]);
            insert_counter += 1;
            if (insert_counter == 5) {
                printf("\n");
                insert_counter = 0;
            }
        }
    }
    if (get_e) {
        uint32_t A[element_size];
        srandom(the_seed);
        for (uint32_t i = 0; i < element_size; i++) {
            A[i] = random() & 0x3FFFFFFF;
        }
        Stats x;
        reset(&x);
        heap_sort(&x, A, element_size);
        printf("Heap Sort, %d elements, %13" PRIu64 " moves, %13" PRIu64 " compares\n",
            element_size, x.moves, x.compares);
        for (uint32_t i = 0; i < element_size; i++) {
            printf("%13" PRIu32, A[i]);
            insert_counter += 1;
            if (insert_counter == 5) {
                printf("\n");
                insert_counter = 0;
            }
        }
    }
    if (get_q) {
        uint32_t A[element_size];
        srandom(the_seed);
        for (uint32_t i = 0; i < element_size; i++) {
            A[i] = random() & 0x3FFFFFFF;
        }
        Stats x;
        reset(&x);
        quick_sort(&x, A, element_size);
        printf("quick Sort, %d elements, %13" PRIu64 " moves, %13" PRIu64 " compares\n",
            element_size, x.moves, x.compares);
        for (uint32_t i = 0; i < element_size; i++) {
            printf("%13" PRIu32, A[i]);
            insert_counter += 1;
            if (insert_counter == 5) {
                printf("\n");
                insert_counter = 0;
            }
        }
    }
}
