#ifndef GRAPH_H
#define GRAPH_H

#include "type.h"

#include <stdbool.h>

graph* createEmptyGraph(int vertices);
bool addEdge(graph* g, int src, int dest);

bool naiveGenerate(display* d, graph* g);

#endif