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
any_matrix_t any_matrix_from_file(int type, FILE *fin, FILE *fout, int *ec);
void any_matrix_print(any_matrix_t *self);

#endif // !__ANY_MATRIX__