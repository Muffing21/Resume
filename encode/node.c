#include "node.h"
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

//    Node *left; is a pointer to left child
//    Node *right;   is a pointer to right child
//    uint8_t symbol;   Node's symbol
//    uint64_t frequency;   frequency of symbol

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->symbol = symbol;
        n->frequency = frequency;
        n->left = NULL;
        n->right = NULL;
        if (!n) {
            n = NULL;
        }
    }
    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free(*n);
        *n = NULL;
    }
    return;
}

Node *node_join(Node *left, Node *right) {
    uint64_t new_node_freq = left->frequency + right->frequency;
    Node *parent_node = node_create('$', new_node_freq);
    parent_node->left = left;
    parent_node->right = right;
    return parent_node;
}

void node_print(Node *n) {
    printf("%" PRIx8 "\n", n->symbol);
    printf("%" PRIx8 " %" PRIx8 "\n", n->left->symbol, n->right->symbol);
    printf("%" PRIu64 "\n", n->frequency);
}
