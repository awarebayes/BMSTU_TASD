#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>

/*
 * Это реализация стека с помощью массива
 */

typedef struct
{
	int *begin; // Начало массива
	int *end; // Конец массива
	int *ps; // Текущее положение
} stack_t;

stack_t stack_new(size_t capacity);

void stack_delete(stack_t *self);

stack_t stack_realloc(stack_t *self);

void stack_push(stack_t *self, int el);

int stack_pop(stack_t *self);

int stack_empty(stack_t *self);

size_t stack_size(stack_t *self);

size_t stack_memsize(stack_t *self);

void stack_print(stack_t *self);

size_t stack_memsize_theoretic(size_t size);

#endif // !__VECTOR_H__