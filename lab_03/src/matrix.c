#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

matrix_t matrix_new(int n, int m)
{
    matrix_t self = {0};
    self.rows = n;
    self.columns = m;
    void *ptr = calloc(sizeof(int *) * n + sizeof(int) * m * n, sizeof(char));
    char *cptr = (char *)ptr;
    int **pa = (int **)cptr;
    int *data_ptr = (int *)(cptr + sizeof(int *) * n);
    for (int i = 0; i < n; i++)
        pa[i] = data_ptr + m * i;
    self.data = pa;
    return self;
}

void matrix_delete(matrix_t *self)
{
    free(self->data);
}

int matrix_n_nonzero(matrix_t *self)
{
    int cnt = 0;
    for (int i = 0; i < self->rows; i++)
        for (int j = 0; j < self->columns; j++)
            if (self->data[i][j] != 0)
                cnt++;
    return cnt;
}

matrix_t matrix_from_array(int *arr, int n, int m)
{
    matrix_t self = matrix_new(n, m);
    self.rows = n;
    self.columns = m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            self.data[i][j] = arr[j + i * m];
    return self;
}

matrix_t matrix_vector_product(matrix_t *self, matrix_t *vector)
{
    assert(vector->rows == self->columns);
    assert(vector->columns == 1);
    matrix_t res = matrix_new(self->rows, 1);

    for (int i = 0; i < self->rows; i++)
    {
        for (int j = 0; j < self->columns; j++)
        {
            printf("usual : res[%d] += self[%d][%d] * vector[%d]\n", i, i, j, j);
            res.data[0][i] += self->data[i][j] * vector->data[0][j];
        }
    }
    return res;
}

void matrix_print(matrix_t *self)
{
    printf("Matrix %dx%d\n", self->rows, self->columns);
    for (int i = 0; i < self->rows; i++)
    {
        for (int j = 0; j < self->columns; j++)
        {
            printf("%d ", self->data[i][j]);
        }
        printf("\n");
    }
}