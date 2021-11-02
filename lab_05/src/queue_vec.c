//
// Created by dev on 11/2/21.
//

#include "queue_vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

queue_vec_t queue_vec_new(size_t el_size, size_t capacity)
{
	queue_vec_t self = { 0 };
	self.data = calloc(capacity, el_size);
	self.pin = self.data;
	self.pout = self.data;
	self.capacity = capacity;
	self.el_size = el_size;
	return self;
}

void queue_vec_delete(queue_vec_t *self)
{
	free(self->data);
}

void queue_vec_add(queue_vec_t *self, void *value)
{
	memcpy(self->pin, value, self->el_size);
	self->pin += self->el_size;
	if (self->pin == (char *)self->data + self->capacity * self->el_size)
		self->pin = self->data; // move to the beginning

	if (self->pin == self->pout)
		self->is_full = 1;
}

void queue_vec_pop(queue_vec_t *self, void *result)
{
	memcpy(result, self->pout, self->el_size);
	self->pout += self->el_size;
	if (self->pout == (char *)self->data + self->capacity * self->el_size)
		self->pout = self->data; // move to the beginning

	if (self->is_full)
		self->is_full = 0;
}

int queue_vec_empty(queue_vec_t *self)
{
	if (self->pin == self->pout && !self->is_full)
		return 1;
	return 0;
}
