#include "../inc/matrix.h"
#include "../inc/sparse.h"
#include "../inc/util.h"
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

matrix_t matrix_from_sparse(sparse_t *sparse)
{
    matrix_t self = matrix_new(sparse->rows, sparse->columns);
    for (int j = 0; j < sparse->columns; j++)
    {
        int nz_start = cons_get(sparse->JA, j);
        int nz_end = cons_get(sparse->JA, j + 1);
        for (int nz_id = nz_start; nz_id < nz_end; nz_id++)
        {
            int i = vector_get(&sparse->IA, nz_id);
            self.data[i][j] = vector_get(&sparse->A, nz_id);
        }
    }
    return self;
}

matrix_t matrix_from_file(FILE *fin, FILE *fout, int *ec)
{
    matrix_t self = {0};
    int n = 0, m = 0;
    if (fout)
        fprintf(fout, "Input n,m:\n");
    if (fscanf(fin, "%d %d", &n, &m) != 2)
        *ec = input_err;
    if (m <= 0 || n <= 0)
        *ec = input_err;
    if (!*ec)
    {
        int *arr = read_arr(fin, fout, "Input values:", m*n, ec);
        if (!*ec)
            self = matrix_from_array(arr, n, m);
        free(arr);
    }
    return self;
}


matrix_t matrix_from_coord_file(FILE *fin, FILE *fout, int *ec)
{
	int n = 0, m = 0, nz = 0;
	read_three_ints(fin, fout, "Input n, m, number nonzero: ", &n, &m, &nz, ec);
	if (nz < 0)
		*ec = input_err;
	matrix_t self = matrix_new(n, m);
	if (!*ec)
	{
		for (int k = 0; k < nz && !*ec; ++k)
		{
			int i, j, el;
			read_three_ints(fin, fout, "Input i, j, element: ", &i, &j, &el, ec);
			if (i < n && j < m)
				self.data[i][j] = el;
			else
				*ec = input_err;
		}
	}
	if (*ec)
		matrix_delete(&self);
	return self;
}

void matrix_delete(matrix_t *self)
{
	free(self->data);
	self->data = NULL;
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

    for (int j = 0; j < self->columns; j++)
    {
        for (int i = 0; i < self->rows; i++)
        {
            int mul = self->data[i][j] * vector->data[0][j];
            #ifdef DEBUG
            if (mul > 0)
                printf("usual : res[%d] += self[%d][%d] * vector[%d]\n", i, i, j, j);
            #endif
            res.data[0][i] += mul;
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

void matrix_print_as_sparse(matrix_t *self)
{
    printf("Matrix %dx%d\n", self->rows, self->columns);
    printf("row\tcol\tval\n");
    int printed = 0;
    for (int j = 0; j < self->columns; j++)
    {
        for (int i = 0; i < self->rows; i++)
        {
            if (self->data[i][j] != 0)
            {
                printf("A[%d]\t[%d]\t = %d\n", j, i, self->data[i][j]);
                printed = 1;
            }
        }
        printf("\n");
    }
    if (!printed)
        printf("Matrix is empty\n");
}

size_t matrix_size(matrix_t *self)
{
  return sizeof(*self) + sizeof(int) * self->rows * self->columns + self-> columns + sizeof(int*) * self->rows;
}
