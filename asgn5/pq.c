#include "pq.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdlib.h>

//EVERYTHING HERE IS CODED FOLLOWING TA CHRISTIAN'S GUIDE

struct PriorityQueue {
    uint32_t head; //index of head of queue
    uint32_t tail; //index of tail of queue
    uint32_t size; //num of elements in queue
    uint32_t capacity;
    Node **items;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));

    if (q) {
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (Node **) calloc(capacity, sizeof(Node *));
        if (!q->items) {
            free(q);
            q->items = NULL;
        }
    }
    return q;
}

// for heap, any parent node must have a value that is less than or equal to the values of its children

uint32_t min_child(Node **items, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if (right <= last) {
        uint32_t left_freq = items[left - 1]->frequency;
        uint32_t right_freq = items[right - 1]->frequency;
        if (right_freq < left_freq) {
            return right;
        }
    }
    return left;
}

void fix_heap(Node **items, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = min_child(items, mother, last);

    while (mother >= last / 2 && !found) {
        uint32_t mother_frequency = items[mother - 1]->frequency;
        uint32_t great_frequency = items[great - 1]->frequency;
        if (mother_frequency > great_frequency) {
            Node *temp = items[mother - 1];
            items[mother - 1] = items[great - 1];
            items[great - 1] = temp;
            mother = great;
            great = min_child(items, mother, last);
        }

        else {
            found = true;
        }
    }
}

void build_heap(Node **items, uint32_t first, uint32_t last) {
    for (uint32_t father = last / 2; father > first - 1; father--) {
        fix_heap(items, father, last);
    }
}

void heap_sort(Node **items, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(items, first, last);
    for (uint32_t leaf = last; leaf < first; leaf++) {
        Node temp = *items[leaf - 1];
        items[leaf - 1] = items[first - 1];
        items[first - 1] = &temp;
        fix_heap(items, first, leaf - 1);
    }
}

void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

bool pq_empty(PriorityQueue *q) {
    //compare size and capacity
    if (q->size == 0) {
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    //compare size and capacity
    if (q->size == q->capacity) {
        return true;
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

bool enqueue(PriorityQueue *q, Node *n) {
    //after checking if pq is full or not;
    if (pq_full(q) == true) {
        return false;
    }
    //use your heap function you create
    //use the get and set pq element functions

    //once you find the location to insert the new node to
    //increment the size
    q->items[q->tail] = n;
    q->tail += 1;
    build_heap(q->items, q->head + 1, q->tail);
    q->size++;
    return true;
}

//after heap is constructed in enqueue, got lowest freq on top and highest on last so dequeue and swap.
bool dequeue(PriorityQueue *q, Node **n) {
    //check if the pq is empty and return false if it is
    if (pq_empty(q) == true) {
        return false;
    }

    *n = q->items[q->head];
    q->tail -= 1;
    q->items[q->head] = q->items[q->tail];
    q->items[q->tail] = *n;
    build_heap(q->items, q->head + 1, q->tail);
    q->size--;
    return true;
}

void pq_print(PriorityQueue *q) {
    Node *n;
    dequeue(q, &n);
    node_print(n);
}
