#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>

typedef struct
{
    int size;
    int capacity;
    int *arr;
} vector_t;

vector_t vector_new(int capacity);
void vector_delete(vector_t *self);
vector_t vector_realloc(vector_t *self);
vector_t vector_from_arr(int n, int *arr);
void vector_add(vector_t *self, int el);
int vector_get(vector_t *self, int idx);
size_t vector_size(vector_t *self);

#endif // !__VECTOR_H__