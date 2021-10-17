#include "insert.h"

#include "stats.h"

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = 1; i < n; i++) {
        int element_index = i;
        uint32_t element_num = move(stats, A[i]);
        while ((element_index > 0) && (cmp(stats, element_num, A[element_index - 1]) == -1)) {
            A[element_index]
                = move(stats, A[element_index - 1]); //if current element is lower than the previous
            element_index -= 1;
        }
        A[element_index] = move(stats, element_num);
    }
}
