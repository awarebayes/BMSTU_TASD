#ifndef __CONS_H__
#define __CONS_H__

#include <stdio.h>

struct cons_t;
typedef struct cons_t cons_t;

struct cons_t
{
	int value;
	struct cons_t *next;
	struct cons_t *prev;
};

typedef struct
{
	cons_t *first;
	cons_t *last;
} list_t;

cons_t *cons_new(int value);

size_t cons_size(cons_t *self);

list_t list_new();

void list_add(list_t *self, int value);

void list_delete(list_t *self);

int list_pop(list_t *self);

int list_empty(list_t *self);

#endif // !__CONS_H__