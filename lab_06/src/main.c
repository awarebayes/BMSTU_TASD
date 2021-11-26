
// Created by dev on 11/25/21.
//

#include "b_tree.h"
#include "avl_tree.h"
#include "cli.h"
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 512

int main()
{
	char *cwd = "./res/";

	struct b_node *btree = b_tree_read(cwd, "btree");
	b_tree_remove(btree, "dollar");
	b_tree_assert_valid(btree);
	b_tree_to_dot(cwd, "btree", btree);
	b_tree_delete(btree);
	run_dot(cwd, "btree");

	struct avl_node *avl = avl_tree_read(cwd, "avl");
	avl_tree_remove(avl, "issue");
	avl_tree_assert_valid(avl);
	avl_tree_to_dot(cwd, "avl", avl);
	avl_tree_delete(avl);
	run_dot(cwd, "avl");
}