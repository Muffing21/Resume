#include "stats.h"

#include <inttypes.h>
#include <math.h>

uint32_t gaps(uint32_t n) {
    return (pow(3, n) - 1) / 2;
}

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {

    for (uint64_t max_gap = log(3 + 2 * n) / log(3); max_gap >= 1; max_gap--) {
        uint64_t gap = gaps(max_gap);
        for (uint64_t i = gap; i < n; i++) {
            uint64_t j = i;
            uint64_t temp = move(stats, A[j]);
            while (j >= gap && (cmp(stats, temp, A[j - gap]) == -1)) {
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = move(stats, temp);
        }
    }
}

//max_gap = log(3+2*n) / log(3)
//for gap from max_gap down to 1
//
