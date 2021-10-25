#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void DFS(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile);
