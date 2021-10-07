#include "matrix.h"

int matrix_n_nonzero(matrix_t *self)
{
    int cnt = 0;
    for (int i = 0; i < self->rows; i++)
        for (int j = 0; j < self->col; j++)
            if (self->data[i][j] != 0)
                cnt++;
    return cnt;
}

matrix_t *matrix_from_array(int **arr, int n, int m)
{
    matrix_t self = {0};
    self->rows = n;
    self->columns = m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            self->data[i][j] = arr[i][j];
    return self;
}