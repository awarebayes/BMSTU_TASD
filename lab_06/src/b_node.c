//
// Created by dev on 11/25/21.
//

#include "b_node.h"
#include <string.h>
#include <stdlib.h>
#include <util.h>

struct b_node *b_node_new(char *data)
{
	void *self_memory = xmalloc(sizeof(struct b_node));
	void *data_ptr = xmalloc(strlen(data) + 1);
	struct b_node *self = (struct b_node *)self_memory;
	self->data = data_ptr;
	strcpy(self->data, data);
	return self;
}

void b_node_delete(struct b_node *self)
{
	free(self->data);
	free(self);
}