#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "sparse.h"
#include <stdio.h>

typedef struct {
    int rows;
    int columns;
    int **data;
} matrix_t;

matrix_t matrix_new(int n, int m);
matrix_t matrix_from_array(int *arr, int n, int m);
matrix_t matrix_from_file(FILE *fin, FILE *fout, int *ec);
void matrix_delete(matrix_t *self);
int matrix_n_nonzero(matrix_t *self);
matrix_t matrix_vector_product(matrix_t *self, matrix_t *vector);
void matrix_print(matrix_t *self);
void matrix_print_as_sparse(matrix_t *self);
size_t matrix_size(matrix_t *self);
matrix_t matrix_from_coord_file(FILE *fin, FILE *fout, int *ec);

#endif // !__MATRIX_H__