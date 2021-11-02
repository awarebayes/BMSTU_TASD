#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue_list.h"
#include "memory.h"

/*
 * Это динамический связный список
 * Тут он реализует стек.
 */

cons_t *cons_new(size_t size)
{
	cons_t *self = (cons_t *) calloc(1, sizeof(cons_t) + size);
	self->value = (char *)self + sizeof(cons_t);
	return self;
}

queue_list_t queue_list_new(size_t el_size)
{
	queue_list_t self = { .el_size = el_size };
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
}

size_t cons_memsize(cons_t *self)
{
	size_t res = 0;
	if (self != NULL)
	{
		res = sizeof(int *) + sizeof(int);
		if (self->next != NULL)
			res += cons_memsize(self->next);
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
