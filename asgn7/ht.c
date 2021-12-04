#include "ht.h"
#include <stdlib.h>
#include "salts.h"
#include "speck.h"
#include "bst.h"
#include <stdio.h>
#include <inttypes.h>

struct HashTable{
	uint64_t salt[2];
	uint32_t size;
	Node **trees;
};

HashTable *ht_create(uint32_t size){
	HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
	if(ht){
		ht->size = size;
		ht->trees = (Node **) malloc(size);
		if(!ht->trees){
			free(ht);
			ht = NULL;
		}
	}
	return ht;
}

void ht_delete(HashTable **ht){
	if(*ht && (*ht)-> trees){
		free((*ht)->trees);
		free(*ht);
		*ht = NULL;
	}
}

uint32_t ht_size(HashTable *ht){
	return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak){
	return bst_find(*ht->trees, oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak){
	ht->trees[hash(ht->salt, oldspeak)] = bst_insert(ht->trees[hash(ht->salt, oldspeak)], oldspeak, newspeak);
}

uint32_t ht_count(HashTable *ht){
	uint32_t count = 0;
	uint32_t tree_counter = 0;
	for(uint32_t i = 0; i < ht->size; i++){
		if(ht->trees[tree_counter] != NULL){
			count += 1;
		}
		tree_counter += 1;
	}
	return count;
}

double ht_avg_bst_size(HashTable *ht){   //computed as sum of the sizes binary search tree/num of non null BST in the hash table
	return bst_size(*ht->trees) / ht_count(ht);
}

double ht_avg_bst_height(HashTable *ht){   //sum of the heights over all BST/num of non null BST in the hash table
	return bst_height(*ht->trees) / ht_count(ht);
}

//void ht_print(HashTable *ht){
//	printf("%" PRIu64 "\n", ht->salt);
//	printf("%" PRIu32 "\n", ht->size);
//}
