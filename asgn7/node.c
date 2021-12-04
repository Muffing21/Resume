#include "node.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//struct Node {
//    char *oldspeak;
//    char *newspeak;
//    Node *left;
//    Node *right;
//};

Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->oldspeak = strdup(oldspeak);
        n->newspeak = strdup(newspeak);
        n->left = NULL;
        n->right = NULL;
    }
    return n;
}

void node_delete(Node **n) {
    //only the n node is freed. the previous and next nodes that n points to are not deleted. Since we have allocated memory for oldspeak and newspeak, free those. The pointer to the node should be set to NULL
    if (*n) {
        free(*n);
        free((*n)->oldspeak);
        free((*n)->newspeak);
        *n = NULL;
    }
}

void node_print(Node *n) {
    if (n->oldspeak != NULL && n->newspeak != NULL) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
    if (n->oldspeak != NULL && n->newspeak == NULL) {
        printf("%s\n", n->oldspeak);
    }
    return;
}
