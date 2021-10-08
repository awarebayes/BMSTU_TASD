#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "common.h"
#include <stdio.h>

typedef struct {
    int rows;
    int columns;
    int **data;
} matrix_t;

matrix_t matrix_new(int n, int m);
void matrix_delete(matrix_t *self);
int matrix_n_nonzero(matrix_t *self);
matrix_t matrix_from_array(int *arr, int n, int m);
matrix_t matrix_vector_product(matrix_t *self, matrix_t *vector);
void matrix_print(matrix_t *self);

#endif // !__MATRIX_H__