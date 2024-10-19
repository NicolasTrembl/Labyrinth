#include "graph.h"
#include "type.h"
#include "display.h"

#include <stdlib.h>
#include <stdio.h>



graph* createEmptyGraph(int vertices) {
    graph* g = (graph*) malloc(sizeof(graph));
    g->vertices = vertices;
    g->edges = (int**) malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        g->edges[i] = (int*) malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            g->edges[i][j] = 0;
        }
    }
    return g;
}

bool addEdge(graph* g, int src, int dest) {
    if (g == NULL) {
        return false;
    }
    if (src < 0 || src >= g->vertices || dest < 0 || dest >= g->vertices) {
        return false;
    }
    g->edges[src][dest] = 1;
    g->edges[dest][src] = 1;
    return true;
}

bool naiveGenerate(display* d, graph* g) {
    if (g == NULL) {
        return false;
    }
    for (int i = 0; i < g->vertices; i++) {
        for (int j = i + 1; j < g->vertices; j++) {
            if (rand() % 2 == 0) {
                addEdge(g, i, j);
            }
        }
        showVertex(d, i, g);
    }
    return true;
}