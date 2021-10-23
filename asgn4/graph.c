#include <stdint.h>
#include "graph.h"
#include "vertices.h"
#include <stdbool.h>

struct Graph {
   uint32_t vertices;
   bool undirected;
   bool visited[VERTICES];
   uint32_t matrix[VERTICES][VERTICES];
};


Graph *graph_create(uint32_t vertices, bool undirected){
   Graph *G = (Graph *)calloc(1, sizeof(Graph));
   G->vertices = vertices;
   G->undirected = undirected;
   return G;
}

void graph_delete(Graph **G){
   free(*G);
   *G = NULL;
   return;
}

uint32_t graph_vertices(Graph *G){
   return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k){
   if (G->undirected = true){
      matrix[j][i] = k
   }
   if (i >= 1 && j >= i && j <= G->vertices){ 
      return true;
   }
   return false;   
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j){
   if (i >= 1 && j >= i && j <= G->vertices && matrix[i][j] > 0){
      return true
   }
   return false
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j){
   if (i >= 1 && j >= i && j <= G->vertices && matrix[i][j] > 0){
      return matrix[i][j];
   }
   return 0;
}

bool graph_visited(Graph *G, uint32_t v){
   if(visited[v] = true;){
      return true;
   }
   return false;
}

void graph_mark_visited(Graph *G, uint32_t v){
   if (i >= 1 && j >= i && j <= G->vertices){
      visited[v] = true;
      
}

void graph_mark_unvisited(Graph *G, uint32_t v){
   if (i >= 1 && j >= i && j <= G->vertices){
      visited[v] = false;
   }
}

void graph_print(Graph *G){
printf("%d %d", graph_edge_weight, graph_edge_weight)
}
