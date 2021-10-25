#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Path {
    Stack *vertices; // the vertices comprising the path
    uint32_t length; // the total length of the path
};

Path *path_create(void) {

    Path *p = (Path *) malloc(sizeof(Path));
    if(p){
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    
    if (!p->vertices) {
            free(p);
            p = NULL;
        }
    }
    return p;
}

void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        free(*p);
        *p = NULL;
    }
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (stack_full(p->vertices) == true) {
        return false;
    }
    uint32_t z;
    uint32_t *i = &z;
    stack_peek(p->vertices, i);
    p->length += graph_edge_weight(G, *i, v);
    stack_push(p->vertices, v);
    return true;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices)) {
        return false;
    }
    uint32_t z;
    uint32_t *i = &z;
    stack_peek(p->vertices, i);
    p->length -= graph_edge_weight(G, *i, *v);
    stack_pop(p->vertices, v);
    return true;
}

uint32_t path_vertices(Path *p) { //returns num of vertices inside the stack?
    return sizeof(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) { //edit this later
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
}
