#include "huffman.h"
#include "node.h"
#include "defines.h"
#include "pq.h"
#include <inttypes.h>
#include "code.h"
#include <stdlib.h>
#include "io.h"
#include "stack.h"

Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *create_pq = pq_create(ALPHABET);
    for (uint8_t i = 0; i < hist[ALPHABET]; i++) {
        if (hist[i] > 0) {
            Node *create_node = node_create(i, hist[i]);
            enqueue(create_pq, create_node);
        }
    }
    while (pq_size(create_pq) > 1) {
        Node *left;
        Node *right;
        Node *parent;
        dequeue(create_pq, &left);
        dequeue(create_pq, &right);
        parent = node_join(left, right);
        enqueue(create_pq, parent);
    }
    Node *root;
    dequeue(create_pq, &root);
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    if (root != NULL) {
        if (!(root->left) && !(root->right)) {
            table[root->symbol] = c;
        } else {
            uint8_t *trash_variable = 0;
            code_push_bit(&c, 0);
            build_codes(root->left, table);
            code_pop_bit(&c, trash_variable);

            code_push_bit(&c, 1);
            build_codes(root->right, table);
            code_pop_bit(&c, trash_variable);
        }
    }
}

void dump_tree(int outfile, Node *root) {
    uint8_t temp_buf[2];
    uint8_t temp_buf2[1];
    if (root) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        if (!(root->left) && !(root->right)) {
            temp_buf[0] = 'L';
            temp_buf[1] = root->symbol;
            write_bytes(outfile, temp_buf, 2);
        } else {
            temp_buf2[0] = 'I';
            write_bytes(outfile, temp_buf2, 1);
        }
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Stack *s = stack_create(ALPHABET);
    for (uint16_t i = 0; i < nbytes; i++) {
        if (tree[i] == 'L') {
            i += 1;
            Node *n = node_create(tree[i], 0);
            stack_push(s, n);
        }
        if (tree[i] == 'I') {
            Node *temp;
            Node *temp2;
            Node *join;
            stack_pop(s, &temp);
            stack_pop(s, &temp2);
            join = node_join(temp2, temp);
            stack_push(s, join);
        }
    }
    Node *root;
    stack_pop(s, &root);
    return root;
}

void delete_tree(Node **root) {
    if (root != NULL) {
        if (!((*root)->left) && !((*root)->right)) {
            node_delete(root);
            return;
        } else {
            delete_tree(&((*root)->left));
            delete_tree(&((*root)->right));
            node_delete(root);
        }
    }
    return;
}
