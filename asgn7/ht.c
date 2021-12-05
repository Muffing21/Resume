#include "ht.h"
#include <stdlib.h>
#include "salts.h"
#include "speck.h"
#include "bst.h"
#include <stdio.h>
#include <inttypes.h>

uint64_t lookups = 0;

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->size = size;
        ht->salt[0] = SALT_HASHTABLE_LO;
        ht->salt[1] = SALT_HASHTABLE_HI;
        ht->trees = (Node **) malloc(size * sizeof(Node *));
        for (uint32_t i = 0; i < ht->size; i++) {
            ht->trees[i] = bst_create();
        }
        if (!ht->trees) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    if (*ht && (*ht)->trees) {
        free((*ht)->trees);
        free(*ht);
        *ht = NULL;
    }
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    lookups += 1;
    return bst_find(ht->trees[hash(ht->salt, oldspeak) % ht->size], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    lookups += 1;
    ht->trees[hash(ht->salt, oldspeak) % ht->size]
        = bst_insert(ht->trees[hash(ht->salt, oldspeak) % ht->size], oldspeak, newspeak);
}

uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i] != NULL) {
            count += 1;
        }
    }
    return count;
}

double ht_avg_bst_size(HashTable *
        ht) { //computed as sum of the sizes binary search tree/num of non null BST in the hash table
	uint32_t total = 0;
	for (uint32_t i = 0; i < ht->size; i++){
		total += bst_size(ht->trees[i]);
	}
    return (double) total / ht_count(ht);
}

double ht_avg_bst_height(
    HashTable *ht) { //sum of the heights over all BST/num of non null BST in the hash table
    	uint32_t total = 0;
    	for (uint32_t i = 0; i < ht->size; i++){
    		total += bst_height(ht->trees[i]);
    	}
    return (double) total / ht_count(ht);
}

//void ht_print(HashTable *ht){
//	printf("%" PRIu64 "\n", ht->salt);
//	printf("%" PRIu32 "\n", ht->size);
//}
