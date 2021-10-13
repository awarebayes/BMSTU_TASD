#ifndef __ANY_MATRIX__
#define __ANY_MATRIX__

#include "sparse.h"
#include "matrix.h"

enum any_matrix_type_enum
{
    any_matrix_dense,
    any_matrix_sparse,
};

union any_matrix_u
{
    sparse_t sparse;
    matrix_t dense;
};

typedef struct
{
    union any_matrix_u kind;
    int type;
} any_matrix_t;

matrix_t matrix_from_sparse(sparse_t *sparse);
sparse_t sparse_from_matrix(matrix_t *m);
int sparse_equal_dense(sparse_t *self, matrix_t *dense);
void any_matrix_as(any_matrix_t *self, int type);
any_matrix_t any_matrix_from_file(int type, FILE *fin, FILE *fout, int *ec);
any_matrix_t any_matrix_vector_product(int type, any_matrix_t *matrix, any_matrix_t *vector);
void any_matrix_delete(any_matrix_t *self);
void any_matrix_print(any_matrix_t *self);
int any_matrix_rows(any_matrix_t *self);
int any_matrix_columns(any_matrix_t *self);

#endif // !__ANY_MATRIX__