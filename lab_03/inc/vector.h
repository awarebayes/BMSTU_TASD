#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct
{
    int size;
    int capacity;
    int *arr;
} vector_t;

vector_t vector_new(int capacity);
void vector_delete(vector_t *self);
vector_t vector_realloc(vector_t *self);
void vector_add(vector_t *self, int el);
int vector_get(vector_t *self, int idx);

#endif // !__VECTOR_H__