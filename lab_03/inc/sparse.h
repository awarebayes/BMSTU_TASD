#ifndef __SPARSE_H__
#define __SPARSE_H__

#include "matrix.h"
#include "common.h"
#include "cons.h"
#include "vector.h"

typedef struct
{
    int rows;
    int columns;
    int n;
    vector_t A; // A
    vector_t IA; // rows with non zero elements
    cons_t *JA;
} sparse_t;

sparse_t sparse_from_matrix(matrix_t *m);
void sparse_print(sparse_t *self);
void sparse_print_pretty(sparse_t *self);
sparse_t sparse_vector_product(sparse_t *self, sparse_t *vector);

#endif // !__SPARSE_H__