#include "graph.h"

#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct Graph {
    uint32_t vertices; //number of verticesd
    bool undirected; // undirected graph
    bool visited[VERTICES]; //where have we gone?
    uint32_t matrix[VERTICES][VERTICES]; //adjency matrixd
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (G->undirected == true) {
        G->matrix[j][i] = k;
    }
    if (i >= 1 && j >= i && j <= G->vertices) {
        return true;
    }
    return false;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i >= 1 && j >= i && j <= G->vertices && G->matrix[i][j] > 0) {
        return true;
    }
    return false;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i >= 1 && j >= i && j <= G->vertices && G->matrix[i][j] > 0) {
        return G->matrix[i][j];
    }
    return 0;
}

bool graph_visited(Graph *G, uint32_t v) {
    if (G->visited[v] == true) {
        return true;
    }
    return false;
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v > 0) {
        G->visited[v] = true;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v > 0) {
        G->visited[v] = false;
    }
}
