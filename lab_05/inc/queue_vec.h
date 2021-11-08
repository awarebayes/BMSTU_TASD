//
// Created by dev on 11/2/21.
//

#ifndef LAB_05_QUEUE_VEC_H
#define LAB_05_QUEUE_VEC_H

#include <stdio.h>

typedef struct
{
	size_t el_size;
	size_t capacity;
	size_t size;
	void *data; // used for malloc and free
	char *pin;
	char *pout;
} queue_vec_t;


queue_vec_t queue_vec_new(size_t el_size, size_t capacity);

void queue_vec_add(queue_vec_t *self, void *value);

void queue_vec_delete(queue_vec_t *self);

void queue_vec_pop(queue_vec_t *self, void *result);

int queue_vec_empty(queue_vec_t *self);

void queue_vec_insert_swap_front(queue_vec_t *self, void *value, size_t index_from_front);

int queue_vec_full(queue_vec_t *self);

void int_queue_vec_print(queue_vec_t *self);

size_t queue_vec_memsize_theoretic(size_t capacity, size_t el_size);

size_t queue_vec_size(queue_vec_t *self);

#endif //LAB_05_QUEUE_VEC_H
