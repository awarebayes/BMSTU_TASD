#ifndef __SPARSE_H__
#define __SPARSE_H__

#include "matrix.h"
#include "common.h"
#include "cons.h"


typedef struct
{
    int rows;
    int columns;
    int n;
    int values[MAX_MATRIX_ELEMS]; // values
    int cols[MAX_MATRIX_ELEMS]; // rows with non zero elements
    cons_t row_ptr;
} sparse_t;

sparse_t sparse_from_matrix(matrix_t *m);

#endif // !__SPARSE_H__