#include "ht.h"
#include <stdlib.h>
#include "salts.h"
#include "speck.h"

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
	bst_insert(ht->trees, hash(oldspeak), newspeak);
}

//uint32_t ht_count(HashTable *ht);

//double ht_avg_bst_size(HashTable *ht);

//double ht_avg_bst_height(HashTable *ht);

//void ht_print(HashTable *ht);
