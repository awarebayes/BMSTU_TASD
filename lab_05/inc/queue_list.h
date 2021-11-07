#ifndef __CONS_H__
#define __CONS_H__

/*
 * Это динамический связный список
 * Тут он реализует очередь.
 */

#include <stdio.h>

struct cons_t;
typedef struct cons_t cons_t;

struct cons_t
{
	// those are stored together
	// preserving cache locality
	// | *next | *value |       value        |
	struct cons_t *next;
	void *value;
};

typedef struct
{
	size_t el_size; // size of an element
	size_t size;
	size_t capacity;
	cons_t *last;
	cons_t *first;
} queue_list_t;

cons_t *cons_new(size_t size);

size_t cons_memsize(cons_t *self, size_t el_size);

queue_list_t queue_list_new(size_t el_size, size_t capacity);

void queue_list_add(queue_list_t *self, void *value);

void queue_list_insert_front(queue_list_t *self, void *value, size_t index_from_front);

void queue_list_delete(queue_list_t *self);

void queue_list_pop(queue_list_t *self, void *result);

int queue_list_empty(queue_list_t *self);

int queue_list_full(queue_list_t *self);

size_t queue_list_size(queue_list_t *self);

void int_queue_list_print(queue_list_t *self);

size_t queue_list_memsize_theoretic(size_t size);

#endif // !__CONS_H__
