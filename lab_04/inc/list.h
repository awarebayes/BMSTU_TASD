#ifndef __CONS_H__
#define __CONS_H__

/*
 * Это динамический связный список
 * Тут он реализует стек.
 */

#include <stdio.h>

struct cons_t;
typedef struct cons_t cons_t;

struct cons_t
{
	int value;
	struct cons_t *next;
};

typedef struct
{
	cons_t *first;
	cons_t *last;
} list_t;

cons_t *cons_new(int value);

size_t cons_memsize(cons_t *self);

list_t list_new();

void list_add(list_t *self, int value);

void list_delete(list_t *self);

int list_pop(list_t *self);

int list_empty(list_t *self);

void list_print(list_t *self);

size_t list_memsize_theoretic(size_t size);

#endif // !__CONS_H__