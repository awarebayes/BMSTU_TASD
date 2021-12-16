//
// Created by dev on 12/13/21.
//

#ifndef LAB_07_GRAPH_H
#define LAB_07_GRAPH_H
#include "matrix.h"
#include "semiring.h"

typedef struct
{
	matrix adj_mat;
} graph;

graph graph_new(int n);
void graph_delete(graph *self);
matrix floyd_warshall(graph *graph, semiring *rig);
void graph_show(graph *self, char *fpath);

#endif //LAB_07_GRAPH_H
