//
// Created by dev on 11/3/21.
//

#include "queue.h"

queue_t queue_new(int type, size_t el_size, size_t capacity)
{
	queue_t self = { .type=type };
	if (type == queue_list_kind)
		self.kind.list = queue_list_new(el_size, capacity);
	else
		self.kind.vec = queue_vec_new(el_size, capacity);
	return self;
}

void queue_add(queue_t *self, void *value)
{
	if (self->type == queue_list_kind)
		queue_list_add(&self->kind.list, value);
	else
		queue_vec_add(&self->kind.vec, value);
}

void queue_insert_front(queue_t *self, void *value, int index_from_front)
{
	if (self->type == queue_list_kind)
		queue_list_insert_front(&self->kind.list, value, index_from_front);
	else
		queue_vec_insert_swap_front(&self->kind.vec, value, index_from_front);
}

void queue_delete(queue_t *self)
{
	if (self->type == queue_list_kind)
		queue_list_delete(&self->kind.list);
	else
		queue_vec_delete(&self->kind.vec);
}


void queue_pop(queue_t *self, void *result)
{
	if (self->type == queue_list_kind)
		queue_list_pop(&self->kind.list, result);
	else
		queue_vec_pop(&self->kind.vec, result);
}

int queue_empty(queue_t *self)
{
	if (self->type == queue_list_kind)
		return queue_list_empty(&self->kind.list);
	else
		return queue_vec_empty(&self->kind.vec);
}

int queue_full(queue_t *self)
{
	if (self->type == queue_list_kind)
		return queue_list_full(&self->kind.list);
	else
		return queue_vec_full(&self->kind.vec);
}


size_t queue_size(queue_t *self)
{
	if (self->type == queue_list_kind)
		return queue_list_size(&self->kind.list);
	else
		return queue_vec_size(&self->kind.vec);
}
