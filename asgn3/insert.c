#include "insert.h"

void insertion_sorts(Stats *stats, uint32_t *A, uint32_t n){
	for(i = 1; i < A; i++){
		int element_index = i;
		uint32_t element_num = A[i];
		while(element_index > 0 && element_num < A[element_index-1]){
			A[element_index] = A[element_index-1]; //if current element is lower than the previous
			element_index -= 1;
		}
		A[element_index] = element_num
	}

}
