//
// Created by dev on 12/13/21.
//
// graph - using incidence matrix
#include <stdlib.h>
#include "graph.h"

graph graph_new(int n)
{
	graph self = { 0 };
	self.adj_mat = matrix_new(n);
	return self;
}

void graph_delete(graph *self)
{
	matrix_delete(&self->adj_mat);
}

matrix floyd_warshall(graph *self, semiring *rig)
{
	matrix c_next = { 0 };
	matrix c_current = matrix_copy(&self->adj_mat);

	for (int i = 0; i < self->adj_mat.n; i++)
		c_current.values[i][i] = rig->add(rig->one, c_current.values[i][i]);

	// printf("C(0):\n");
	// matrix_print(&c_current, stdout);
	for (int k = 1; k < self->adj_mat.n; k++)
	{
		c_next = floyd_warshall_step(&c_current, rig, k);
		matrix_delete(&c_current);
		c_current = c_next;
		// printf("After step:\n");
		// printf("C(%d):\n", k);
		// matrix_print(&c_current, stdout);
	}
	return c_current;
}

void graph_show(graph *self, char *fpath)
{
	FILE *f_out = fopen("./res/out.dot", "w");

	fprintf(f_out, "digraph MY_LAB_07 {\n");

	matrix adj_mat = self->adj_mat;

	for (int i = 0; i < adj_mat.n; ++i)
	{
		for (int j = 0; j < adj_mat.n; ++j)
		{
			int v = adj_mat.values[i][j];
			if (v < INT_MAX && v != 0 && v != INT_MIN)
			{
				fprintf(f_out, "%d -> %d [label=\"%d\"];\n", i, j, adj_mat.values[i][j]);
			}
		}
	}
	fprintf(f_out, "}\n");
	fclose(f_out);
	char command[256];
	snprintf(command,256, "dot -Tpng ./res/out.dot > %s", fpath);
	system(command);
}
