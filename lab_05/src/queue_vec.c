//
// Created by dev on 11/2/21.
//

#include "queue_vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "util.h"

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
	self->data = NULL;
}

// adds to back
void queue_vec_add(queue_vec_t *self, void *value)
{
	memcpy(self->pin, value, self->el_size);
	self->pin += self->el_size;
	if (self->pin == (char *) self->data + self->capacity * self->el_size)
		self->pin = self->data; // move to the beginning
	self->size++;
}


// adds to front
// can cause segfault, use just add, when queue is empty
void queue_vec_add_front(queue_vec_t *self, void *value)
{
	if (self->pout - self->el_size >= (char*)self->data)
		self->pout -= self->el_size;
	else
	{
		char *upper_bound =   (char *) self->data + self->capacity * self->el_size;
		self->pout = upper_bound - self->el_size;
	}
	memcpy(self->pout, value, self->el_size);
	self->size++;
}

void queue_vec_pop(queue_vec_t *self, void *result)
{
	memcpy(result, self->pout, self->el_size);
	self->pout += self->el_size;
	if (self->pout == (char *) self->data + self->capacity * self->el_size)
		self->pout = self->data; // move to the beginning
	self->size--;
}

// add element to queue
// swap it with index_from_front element
void queue_vec_insert_swap_front(queue_vec_t *self, void *value, size_t index_from_front)
{
	if (index_from_front >= self->size)
		queue_vec_add(self, value);
	else
	{
		queue_vec_add_front(self, value);
		char *added_address = self->pout;
		char *previous_address = (char *) self->pout + index_from_front * self->el_size;
		char *upper_bound =   (char *) self->data + self->capacity * self->el_size;
		if (previous_address >= upper_bound)
		{
			ptrdiff_t offset = previous_address - upper_bound;
			previous_address = (char *) self->data + offset;
			memswap(added_address, previous_address, self->el_size);
		}
		else
			memswap(added_address, previous_address, self->el_size);
	}
}

int queue_vec_full(queue_vec_t *self)
{
	return self->size == self->capacity;
}

int queue_vec_empty(queue_vec_t *self)
{
	if (self->pin == self->pout && !queue_vec_full(self))
		return 1;
	return 0;
}

size_t queue_vec_size(queue_vec_t *self)
{
	return self->size;
}

size_t queue_vec_memsize_theoretic(size_t capacity, size_t el_size)
{
	return sizeof(queue_vec_t) + capacity * el_size;
}