#include "stack.h"
#include <stdlib.h>
#include <stddef.h>

/*
 * Это реализация стека с помощью массива
 */

stack_t stack_new(size_t capacity)
{
	stack_t self = { 0 };
	self.begin = calloc(capacity, sizeof(int));
	self.end = self.begin + capacity;
	self.ps = self.begin - 1;
	return self;
}

size_t stack_size(stack_t *self)
{
	return self->end - self->begin;
}

void stack_delete(stack_t *self)
{
	if (self == NULL)
		return;
	free(self->begin);
	self->begin = NULL;
}

stack_t stack_realloc(stack_t *self)
{
	stack_t new_stack = stack_new(stack_size(self) * 2);
	ptrdiff_t old_pos = self->ps - self->begin;
	new_stack.ps = new_stack.begin + old_pos;

	for (size_t i = 0; i < stack_size(self); i++)
		new_stack.begin[i] = self->begin[i];

	stack_delete(self);

	*self = new_stack;
	return new_stack;
}

void stack_push(stack_t *self, int el)
{
	if (self->ps + 1 >= self->end)
		*self = stack_realloc(self);
	self->ps += 1;
	*(self->ps) = el;
}

int stack_empty(stack_t *self)
{
	return self->ps < self->begin;
}

int stack_pop(stack_t *self)
{
	return *(self->ps--);
}

void stack_print(stack_t *self)
{
	if (self->ps < self->begin)
	{
		printf("Stack is empty\n");
		return;
	}
	printf("Stack is: \n");
	for (int *a = self->ps; a >= self->begin; a--)
		printf("%d ", *a);
	printf("\n");
}

size_t stack_memsize(stack_t *self)
{
	return sizeof(stack_t) + sizeof(int) * stack_size(self);
}

size_t stack_memsize_theoretic(size_t size)
{
	return sizeof(stack_t) + sizeof(int) * size;
}
