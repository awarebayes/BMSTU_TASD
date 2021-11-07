#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_list.h"
#include "memory.h"

/*
 * Это динамический связный список
 * Тут он реализует очередь.
 */

cons_t *cons_new(size_t size)
{
	cons_t *self = (cons_t *) calloc(1, sizeof(cons_t) + size);
	self->value = (char *)self + sizeof(cons_t);
	return self;
}

queue_list_t queue_list_new(size_t el_size, size_t capacity)
{
	queue_list_t self = { .el_size = el_size, .capacity = capacity };
	return self;
}

void queue_list_delete(queue_list_t *self)
{
	cons_t *current_node = self->first;
	cons_t *prev = NULL;
	while (current_node != NULL)
	{
		prev = current_node;
		current_node = current_node->next;
		free(prev);
	}
	self->first = NULL;
	self->last = NULL;
}

void queue_list_add(queue_list_t *self, void *value)
{
	cons_t *new_last = cons_new(self->el_size);
	memcpy(new_last->value, value, self->el_size);
	if (self->last == NULL) // el_size = 0
	{
		self->first = new_last;
		self->last = new_last;
	}
	else
	{
		cons_t *prev_last = self->last;
		prev_last->next = new_last;
		self->last = new_last;
	}
	self->size++;
}

void queue_list_insert_front(queue_list_t *self, void *value, size_t index_from_front)
{
	cons_t *new_node = cons_new(self->el_size);
	memcpy(new_node->value, value, self->el_size);
	self->size++;
	cons_t *prev_node = NULL;
	cons_t *next_node = self->first;
	if (next_node == NULL)
		self->first = self->last = new_node;
	else
	{
		for (size_t i = 0; i < index_from_front && next_node; i++)
		{
			prev_node = next_node;
			next_node = next_node->next;
		}
		if (prev_node != NULL) // el_size = 0
			prev_node->next = new_node;
		else
			self->first = new_node;
		new_node->next = next_node;
	}
}

void queue_list_pop(queue_list_t *self, void *result)
{
	if (self->first == NULL) // el_size = 0
		return;

	memcpy(result, self->first->value, self->el_size);

	if (LOG_DELETED)
		log_delete(self->first);

	cons_t *after_first = self->first->next;
	free(self->first);
	self->first = after_first;

	if (self->first == NULL)
		self->last = NULL;
	self->size--;
}

int queue_list_full(queue_list_t *self)
{
	return self->size == self->capacity;
}

size_t cons_memsize(cons_t *self, size_t el_size)
{
	size_t res = 0;
	if (self != NULL)
	{
		res = sizeof(cons_t) + el_size;
		if (self->next != NULL)
			res += cons_memsize(self->next, el_size);
	}
	return res;
}

size_t queue_list_memsize_theoretic(size_t size)
{
	return sizeof(queue_list_t) + sizeof(cons_t) * size;
}


int queue_list_empty(queue_list_t *self)
{
	return self->last == NULL;
}

size_t queue_list_size(queue_list_t *self)
{
	return self->size;
}

void int_queue_list_print(queue_list_t *self)
{
	cons_t *node = self->first;
	if (self->last == NULL)
	{
		printf("List is empty\n");
		return;
	}
	while (node != NULL)
	{
		printf("%d ", *((int*)node->value));
		node = node->next;
	}
	printf("\n");
}
