//
// Created by dev on 11/3/21.
//

#ifndef LAB_05_QUEUE_H
#define LAB_05_QUEUE_H

#include "queue_list.h"
#include "queue_vec.h"

// Tagged union
// Просто вызывает соответствующий метод

typedef union
{
	queue_list_t list;
	queue_vec_t vec;
} queue_u;

typedef struct
{
	queue_u kind;
	int type;
} queue_t;

enum
{
	queue_list_kind,
	queue_vec_kind
};

queue_t queue_new(int type, size_t el_size, size_t capacity);

void queue_add(queue_t *self, void *value);

void queue_insert_front(queue_t *self, void *value, int index_from_front);

void queue_delete(queue_t *self);

void queue_pop(queue_t *self, void *result);

int queue_empty(queue_t *self);

int queue_full(queue_t *self);

size_t queue_size(queue_t *self);

#endif //LAB_05_QUEUE_H
