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

list_t list_new()
{
	list_t self = { 0 };
	return self;
}

void list_delete(list_t *self)
{
	cons_t *current_node = self->top;
	cons_t *prev = NULL;
	while (current_node != NULL)
	{
		prev = current_node;
		current_node = current_node->next;
		free(prev);
	}
	self->top = NULL;
}

void list_add(list_t *self, int value)
{
	cons_t *new_last = cons_new(value);
	if (self->top == NULL) // size = 0
		self->top = new_last;
	else
	{
		cons_t *prev_top = self->top;
		self->top = new_last;
		self->top->next = prev_top;
	}
}

int list_pop(list_t *self)
{
	if (self->top == NULL) // size = 0
		return 0;

	int val = self->top->value;

	if (LOG_DELETED)
		log_delete(self->top);

	cons_t *next = self->top->next;
	free(self->top);
	self->top = next;

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
	return self->top == NULL;
}

void list_print(list_t *self)
{
	cons_t *node = self->top;
	if (self->top == NULL)
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
