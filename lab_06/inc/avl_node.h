//
// Created by dev on 11/25/21.
//

#ifndef LAB_06_AVL_NODE_H
#define LAB_06_AVL_NODE_H

// Warning: actually owns data
// Uses malloc, dont forget to call destructor!
struct avl_node
{
	struct avl_node *left;
	struct avl_node *right;
	char *data;
	int height;
};

struct avl_node *avl_node_new(char *data);
void avl_node_delete(struct avl_node *self);
struct avl_node *avl_node_deep_copy(struct avl_node *self);

#endif //LAB_06_AVL_NODE_H
