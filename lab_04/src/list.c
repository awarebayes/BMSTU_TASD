#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "memory.h"

/*
 * Это динамический связный список
 * Тут он реализует стек.
 */

cons_t *cons_new(int value)
{
	cons_t *self = (cons_t *) malloc(sizeof(cons_t));
	self->value = value;
	self->next = NULL;
	return self;
}

cons_t *cons_traverse(cons_t *self)
{
	while (self->next != NULL)
		self = self->next;
	return self;
}

list_t list_new()
{
	list_t self = { 0 };
	return self;
}

void list_delete(list_t *self)
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

void list_add(list_t *self, int value)
{
	cons_t *new_last = cons_new(value);
	if (self->first == NULL) // size = 0
	{
		self->first = new_last;
		self->last = self->first;
	}
	else
	{
		cons_t *prev_last = self->last;
		self->last = new_last;
		prev_last->next = new_last;
	}
}

int list_pop(list_t *self)
{
	if (self->last == NULL) // size = 0
		return 0;

	int val = self->last->value;

	if (LOG_DELETED)
		log_delete(self->last);

	if (self->first == self->last)
	{
		free(self->last);
		self->first = NULL;
		self->last = NULL;
	}
	else
	{
		cons_t *current_node = self->first;
		cons_t *prev = self->first;
		while (current_node->next != NULL)
		{
			prev = current_node;
			current_node = current_node->next;
			free(prev);
		}
		free(self->last);
		self->last = prev;
		if (self->last != 0)
			self->last->next = NULL;
	}
	return val;
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

size_t list_memsize_theoretic(size_t size)
{
	return sizeof(list_t) + sizeof(cons_t) * size;
}


int list_empty(list_t *self)
{
	return self->first == NULL;
}

void list_print(list_t *self)
{
	cons_t *node = self->first;
	if (self->first == NULL)
	{
		printf("List is empty\n");
		return;
	}
	while (node != NULL)
	{
		printf("%d ", node->value);
		node = node->next;
	}
	printf("\n");
}

