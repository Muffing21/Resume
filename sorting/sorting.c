
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "aeisqhr:n:p:"
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
uint32_t limit_print = default_size;

int main(int argc, char **argv) {
    Set s = 0;
    int opt = 0;
    enum sorts { get_a, get_e, get_i, get_s, get_q };
    bool get_r = false;
    bool get_n = false;
    bool get_p = false;
    bool get_h = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': s = insert_set(get_a, s); break;
        case 'e': s = insert_set(get_e, s); break;
        case 'i': s = insert_set(get_i, s); break;
        case 's': s = insert_set(get_s, s); break;
        case 'q': s = insert_set(get_q, s); break;
        case 'r':
            get_r = true;
            the_seed = atoi(optarg);
            break;
        case 'n':
            get_n = true;
            element_size = atoi(optarg);
            break;
        case 'p':
            get_p = true;
            limit_print = atoi(optarg);
            if (element_size < limit_print) {
                limit_print = element_size;
            }
            break;
        case 'h': get_h = true; break;
        }
    }

    uint32_t *A = (uint32_t *) calloc(element_size, sizeof(uint32_t));
    if (member_set(get_i, s)) {

        srandom(the_seed);
        for (uint32_t i = 0; i < element_size; i++) {
            A[i] = random() & 0x3FFFFFFF;
        }
        Stats x;
        reset(&x);
        insertion_sort(&x, A, element_size);

        printf("Insertion Sort, %d elements, %1" PRIu64 " moves, %1" PRIu64 " compares\n",
            element_size, x.moves, x.compares);
        for (uint32_t i = 0; i < limit_print; i++) {
            printf("%13" PRIu32, A[i]);
            insert_counter += 1;
            if (insert_counter == 5) {
                printf("\n");
                insert_counter = 0;
            }
        }
    }
    if (member_set(get_s, s)) {

        srandom(the_seed);
        for (uint32_t i = 0; i < default_size; i++) {
            A[i] = random() & 0x3FFFFFFF;
        }
        Stats x;
        reset(&x);
        shell_sort(&x, A, element_size);

        printf("Shell Sort, %d elements, %1" PRIu64 " moves, %1" PRIu64 " compares\n", element_size,
            x.moves, x.compares);
        for (uint32_t i = 0; i < limit_print; i++) {
            printf("%13" PRIu32, A[i]);
            insert_counter += 1;
            if (insert_counter == 5) {
                printf("\n");
                insert_counter = 0;
            }
        }
    }
    if (member_set(get_e, s)) {

        srandom(the_seed);
        for (uint32_t i = 0; i < element_size; i++) {
            A[i] = random() & 0x3FFFFFFF;
        }
        Stats x;
        reset(&x);
        heap_sort(&x, A, element_size);
        printf("Heap Sort, %d elements, %1" PRIu64 " moves, %1" PRIu64 " compares\n", element_size,
            x.moves, x.compares);
        for (uint32_t i = 0; i < limit_print; i++) {
            printf("%13" PRIu32, A[i]);
            insert_counter += 1;
            if (insert_counter == 5) {
                printf("\n");
                insert_counter = 0;
            }
        }
    }
    if (member_set(get_q, s)) {

        srandom(the_seed);
        for (uint32_t i = 0; i < element_size; i++) {
            A[i] = random() & 0x3FFFFFFF;
        }
        Stats x;
        reset(&x);
        quick_sort(&x, A, element_size);
        printf("quick Sort, %d elements, %1" PRIu64 " moves, %1" PRIu64 " compares\n", element_size,
            x.moves, x.compares);
        for (uint32_t i = 0; i < limit_print; i++) {
            printf("%13" PRIu32, A[i]);
            insert_counter += 1;
            if (insert_counter == 5) {
                printf("\n");
                insert_counter = 0;
            }
        }
    }
    if (member_set(get_a, s)) {

        for (uint32_t r = 0; r < 4; r++) {
            srandom(the_seed);
            for (uint32_t i = 0; i < element_size; i++) {
                A[i] = random() & 0x3FFFFFFF;
            }
            Stats x;
            reset(&x);
            if (r == 0) {
                heap_sort(&x, A, element_size);
                printf("Heap Sort, %d elements, %1" PRIu64 " moves, %1" PRIu64 " compares\n",
                    element_size, x.moves, x.compares);
            }
            if (r == 1) {
                shell_sort(&x, A, element_size);
                printf("Shell Sort, %d elements, %1" PRIu64 " moves, %1" PRIu64 " compares\n",
                    element_size, x.moves, x.compares);
            }
            if (r == 2) {
                insertion_sort(&x, A, element_size);
                printf("Insertion Sort, %d elements, %1" PRIu64 " moves, %1" PRIu64 " compares\n",
                    element_size, x.moves, x.compares);
            }
            if (r == 3) {
                quick_sort(&x, A, element_size);
                printf("quick Sort, %d elements, %1" PRIu64 " moves, %1" PRIu64 " compares\n",
                    element_size, x.moves, x.compares);
            }
            for (uint32_t i = 0; i < limit_print; i++) {
                printf("%13" PRIu32, A[i]);
                insert_counter += 1;
                if (insert_counter == 5) {
                    printf("\n");
                    insert_counter = 0;
                }
            }
        }
    }
    if (get_h) {
        printf("SYNOPSIS\n   A collection of comparison-based sorting algorithms.\n\nUSAGE\n   "
               "./sorting [-haeisqn:p:r:] [-n length] [-p elements] [-r seed]\n\nOPTIONS\n");
        printf("   -h             display program help and usage.\n");
        printf("   -a             enable all sorts.\n");
        printf("   -e             enable Heap Sort.\n");
        printf("   -i             enable insertion Sort.\n");
        printf("   -s             enable Shell sort.\n");
        printf("   -q             enable Quick Sorts.\n");
        printf("   -n length      specify number of array elements (default: 100).\n");
        printf("   -p elements    specify number of elements to print (default: 100).\n");
        printf("   -r seed        specify random seed (default: 13371453).\n");
    }
    free(A);
    return 0;
}
