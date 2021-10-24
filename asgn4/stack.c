#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top; //index of the next empty slot
    uint32_t capacity; //number of items that can be pushed
    uint32_t *items; // Array of items, each with type uint32_t
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
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

bool stack_push(Stack *s, uint32_t x) {
    if (s->capacity == s->top) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}
bool stack_pop(Stack *s, uint32_t *x) {
    if (s->top == 0) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}
bool stack_peek(Stack *s, uint32_t *x) {
    if (s->top == 0) {
        return false;
    }
    *x = s->items[s->top];
    return true;
}
void stack_copy(Stack *dst, Stack *src) {
    dst->capacity = src->capacity;
    dst->top = src->top;
    for (uint32_t z = 0; z < dst->top; z++) {
        dst->items[z] = src->items[z];
    }
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
