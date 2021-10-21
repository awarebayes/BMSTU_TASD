#include "stack.h"
#include <stdlib.h>
#include <stddef.h>

stack_t stack_new(size_t capacity)
{
	stack_t self = { 0 };
	self.arr = calloc(capacity, sizeof(int));
	self.arr_end = self.arr + capacity;
	self.ps = self.arr - 1;
	return self;
}

size_t stack_size(stack_t *self)
{
	return self->arr_end - self->arr;
}

void stack_delete(stack_t *self)
{
	if (self == NULL)
		return;
	free(self->arr);
	self->arr = NULL;
}

stack_t stack_realloc(stack_t *self)
{
	stack_t new_stack = stack_new(stack_size(self) * 2);
	ptrdiff_t old_pos = self->ps - self->arr;
	new_stack.ps = new_stack.arr + old_pos;

	for (size_t i = 0; i < stack_size(self); i++)
		new_stack.arr[i] = self->arr[i];

	stack_delete(self);

	*self = new_stack;
	return new_stack;
}

void stack_push(stack_t *self, int el)
{
	if (self->ps + 1 >= self->arr_end)
		*self = stack_realloc(self);
	self->ps += 1;
	*(self->ps) = el;
}

int stack_empty(stack_t *self)
{
	return self->ps < self->arr;
}

int stack_pop(stack_t *self)
{
	return *(self->ps--);
}

void stack_print(stack_t *self)
{
	printf("Stack is: \n");
	for (int *a = self->arr; a < self->ps; a++)
		printf("%d ", *a);
	printf("\n");
}

size_t stack_memsize(stack_t *self)
{
	return sizeof(stack_t) + sizeof(int) * stack_size(self);
}
