#include "dfs.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void DFS(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    uint32_t store_parse;
    char city_names;
    uint32_t maxline = 1000;
    FILE *open_file;
    open_file = fopen(get_file_name, r);
          char *fgets(city_names, maxline, FILE open_file)
          int sscanf(city_names, "%" SCNu32, &store_parse));
          //uint32_t getc(FILE open_file);
          //uint32_t ungetc(FILE open_file);
          //graph_visited(G, v);
}
