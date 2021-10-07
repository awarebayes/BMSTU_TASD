#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "common.h"

typedef struct {
    int rows;
    int columns;
    int data[N_ROWS][N_COLS];
} matrix_t;

int matrix_n_nonzero(matrix_t *self);

#endif // !__MATRIX_H__