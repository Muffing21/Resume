#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
   uint32_t top; //index of the next empty slot
   uint32_t capacity; //number of items that can be pushed
   Node **items;  
};

Stack *stack_create(uint32_t capacity){
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(capacity, sizeof(Node));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}
bool stack_full(Stack *s) {
    if (s->capacity == s->top) {
        return true;
    }
    return false;
}

bool stack_push(Stack *s, Node *n) {
    if (s->capacity == s->top) {
        return false;
    }
    s->items[s->top] = n;
    s->top += 1;
    return true;
}
bool stack_pop(Stack *s, Node **n) {
    if (s->top == 0) {
        return false;
    }
    s->top -= 1;
    *n = s->items[s->top];
    return true;
}



//void stack_print(Stack *s) {
//
//}
