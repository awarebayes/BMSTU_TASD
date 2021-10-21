#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>

typedef struct
{
	int *arr;
	int *arr_end;
	int *ps;
} stack_t;

stack_t stack_new(size_t capacity);

void stack_delete(stack_t *self);

stack_t stack_realloc(stack_t *self);

void stack_push(stack_t *self, int el);

int stack_pop(stack_t *self);

int stack_empty(stack_t *self);

size_t stack_size(stack_t *self);

size_t stack_memsize(stack_t *self);

#endif // !__VECTOR_H__