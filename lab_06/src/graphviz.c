//
// Created by dev on 11/28/21.
//
#include <stdio.h>
#include "graphviz.h"
#include "b_node.h"

#define BUF_SIZE 512

static int graph_print_dot_null(char *key, int nullcount, FILE *stream)
{
	fprintf(stream, "null%d [shape=point];\n", nullcount);
	fprintf(stream, "%s -> null%d;\n", key, nullcount);
	return 1;
}

static void graph_print_dot_aux(struct b_node *node, FILE *stream, int show_dots)
{
	static int nullcount = 0;

	if (node->left)
	{
		fprintf(stream, "%s -> %s;\n", node->data, node->left->data);
		graph_print_dot_aux(node->left, stream, show_dots);
	}
	else
		show_dots && graph_print_dot_null(node->data, nullcount++, stream);

	if (node->right)
	{
		fprintf(stream, "%s -> %s;\n", node->data, node->right->data);
		graph_print_dot_aux(node->right, stream, show_dots);
	}
	else
		show_dots && graph_print_dot_null(node->data, nullcount++, stream);
}

void graph_tree_to_dot(char *cwd, char *tree_name, struct b_node *self, int show_dots)
{
	char buf[BUF_SIZE] = { 0 };
	snprintf(buf, BUF_SIZE, "%s%s.dot", cwd, tree_name);
	FILE *f = fopen(buf, "w");
	fprintf(f, "digraph %s {\n", tree_name);
	graph_print_dot_aux(self, f, show_dots);
	fprintf(f, "}\n");
	fclose(f);
}
