//
// Created by dev on 12/1/21.
//


#include <assert.h>
#include "avl_node.h"
#include "avl_tree.h"
#include "graphviz.h"
#include "cli.h"

void run_tests()
{
	struct avl_node *tree = NULL;
	tree = avl_tree_add(tree, "1");
	tree = avl_tree_add(tree, "2");
	tree = avl_tree_add(tree, "3");
	tree = avl_tree_add(tree, "4");
	tree = avl_tree_add(tree, "5");
	tree = avl_tree_add(tree, "6");
	tree = avl_tree_add(tree, "7");
	tree = avl_tree_add(tree, "8");
	tree = avl_tree_add(tree, "9");
	tree = avl_tree_add(tree, "10");

	tree = avl_tree_remove(tree, "4");

	graph_tree_to_dot("./res/", "test", (struct b_node *)tree, 1);
	run_dot("./res/", "test");
	avl_tree_delete(tree);
}
