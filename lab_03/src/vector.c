#include "vector.h"
#include <stdlib.h>

vector_t vector_new(int capacity)
{
    vector_t self = {0};
    self.size = 0;
    self.capacity = capacity;
    self.arr = calloc(capacity, sizeof(int));
    return self;
}

vector_t vector_from_arr(int n, int *arr)
{
    vector_t self = vector_new(n);
    self.size = n;
    for (int i = 0; i < n; i++) 
        self.arr[i] = arr[i];
    return self;
}

void vector_delete(vector_t *self)
{
    if (self == NULL)
        return;
    free(self->arr);
}

vector_t vector_realloc(vector_t *self)
{
    vector_t new_vec = vector_new(self->capacity * 2);
    new_vec.size = self->size;
    for (int i = 0; i < self->capacity; i++)
        new_vec.arr[i] = self->arr[i];
    vector_delete(self);
    *self = new_vec;
    return new_vec;
}

void vector_add(vector_t *self, int el)
{
    if (self->size + 1 >= self->capacity)
        *self = vector_realloc(self);
    self->arr[self->size++] = el;
}

inline int vector_get(vector_t *self, int idx)
{
    return self->arr[idx];
}

size_t vector_size(vector_t *self)
{
  return sizeof(int) * self->capacity + 2 * sizeof(int);
}
