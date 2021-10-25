#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "hvui:o:"
//strdup to copy the city names, allocate sufficient memory then free

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile,
    uint32_t max_v) {
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);
    for (uint32_t z = 0; z < max_v; z++) {
        if (graph_has_edge(G, v, z) == true) {

            if (graph_visited(G, z) == false) {
                dfs(G, z, curr, shortest, cities, outfile, max_v);
            }
            if (z == START_VERTEX && path_vertices(curr) == max_v) {
                path_push_vertex(curr, z, G);
                if (path_vertices(shortest) > path_vertices(curr)) {
                    path_copy(shortest, curr);
                    path_pop_vertex(curr, &z, G);
                }
            }
        }
    }
    graph_mark_unvisited(G, v);
    path_pop_vertex(curr, &v, G);
}

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int opt = 0;
    bool undirected = false;

    bool get_h = false;
    //    bool get_v = false;
    bool get_u = false;
    bool get_i = false;
    bool get_o = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            get_h = true;
            break;
            //        case 'v': get_v = true; break;
        case 'u':
            get_u = true;
            undirected = true;
            break;
        case 'i':
            get_i = true;
            infile = fopen(optarg, "r");
            break;
        case 'o':
            get_o = true;
            outfile = fopen(optarg, "w");
            break;
        }
    }
    uint32_t store_parse;
    uint32_t maxline = 1000;
    char city_num[1000];
    char city_names[1000];
    char *store_names[1000];
    char city_xyz[1000];
    uint32_t city_x;
    uint32_t city_y;
    uint32_t city_z;
    //uint32_t store_num[1000];

    fgets(city_num, maxline, infile);
    sscanf(city_num, "%" SCNu32, &store_parse);

    for (uint32_t i = 0; i < store_parse; i++) {
        fgets(city_names, maxline, infile);
        sscanf(city_names, "%s", city_names);
        store_names[i] = city_names;
    }
    Graph *graph = graph_create(store_parse, undirected);
    while (fgets(city_xyz, maxline, infile) != NULL) {
        sscanf(city_xyz, "%" SCNu32 " %" SCNu32 " %" SCNu32, &city_x, &city_y, &city_z);
        graph_add_edge(graph, city_x, city_y, city_z);
    }

    Path *curr = path_create();
    Path *shortest = path_create();
    dfs(graph, START_VERTEX, curr, shortest, store_names, outfile, store_parse);
    path_print(shortest, outfile, store_names);

    if (get_h) {
        printf("SYNOPSIS\n Traveling Salesman Problem using DFS.\n\nUSAGE\n ./tsp [-u] [-v] "
               "[-h] [-i infile] [-o outfile]\n\nOPTIONS\n -u             Use undirected "
               "graph.\n -v             Enable verbose printing.\n -h             Program "
               "usage and help.\n -i infile      Input containing graph (default: stdin)\n -o "
               "outfile     Output of computed path (default: stdout)");
    }
}
