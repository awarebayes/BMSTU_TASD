
// Created by dev on 11/25/21.
//

#ifndef LAB_06_B_NODE_H
#define LAB_06_B_NODE_H


// Warning: actually owns data
// Uses malloc, dont forget to call destructor!
struct b_node
{
	struct b_node *left;
	struct b_node *right;
	char *data;
};

struct b_node *b_node_new(char *data);
void b_node_delete(struct b_node *self);

#endif //LAB_06_B_NODE_H
