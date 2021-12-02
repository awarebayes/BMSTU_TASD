//
// Created by dev on 11/25/21.
//

#include "avl_node.h"
#include <string.h>
#include <stdlib.h>
#include <util.h>

struct avl_node *avl_node_new(char *data)
{
	void *self_memory = xmalloc(sizeof(struct avl_node));
	void *self_data = xmalloc(strlen(data) + 1);
	struct avl_node *self = (struct avl_node *) self_memory;
	self->data = self_data;
	strcpy(self->data, data);
	self->height = 1;
	return self;
}

void avl_node_delete(struct avl_node *self)
{
	if (self != NULL)
		free(self->data);
	free(self);
}

struct avl_node *avl_node_deep_copy(struct avl_node *self)
{
	struct avl_node *copy = avl_node_new(self->data);
	copy->left = self->left;
	copy->right = self->right;
	return copy;
}
