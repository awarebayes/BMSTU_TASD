#include "../inc/sparse.h"
#include "../inc/cons.h"
#include "../inc/util.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

sparse_t sparse_from_matrix(matrix_t *m)
{
    sparse_t self = {0};
    self.rows = m->rows;
    self.columns = m->columns;
    self.n = matrix_n_nonzero(m);
    self.JA = NULL;
    self.A = vector_new(self.n+1);
    self.IA = vector_new(self.n+1);
    int el_count = 0;
    for (int j = 0; j < self.columns; j++)
    {
        if (self.JA == NULL)
            self.JA = cons_new(el_count);
        else
            cons_add(self.JA, el_count);
        for (int i = 0; i < self.rows; i++)
        {
            if (m->data[i][j] != 0)
            {
                vector_add(&self.A, m->data[i][j]);
                vector_add(&self.IA, i);
                el_count++;
            }
        }
    }
    cons_add(self.JA, el_count);
    return self;
}

sparse_t sparse_from_file(FILE *fin, FILE *fout, int *ec)
{
    sparse_t self = {0};
    int n = 0, m = 0;
    int nz = 0;

    int *A = NULL;
    int *IA = NULL;
    cons_t *JA = NULL;

    if (fout)
        fprintf(fout, "Input n,m:\n");
    if (fscanf(fin, "%d %d", &n, &m) != 2)
        *ec = input_err;
    if (fout)
        fprintf(fout, "Input number nonzero:\n");
    if (fscanf(fin, "%d", &nz) != 1)
        *ec = input_err;
    if (m <= 0 || n <= 0 || nz < 0 || nz > m * n)
        *ec = input_err;
    
    if (!*ec)
        A = read_arr(fin, fout, "Input values(A): ", nz, ec);
    if (!*ec)
        IA = read_arr(fin, fout, "Input indices (IA): ", nz, ec);
    if (!*ec)
		JA = read_arr_cons(fin, fout, "Input indices (JA): ");
    if (!*ec)
    {
        self.rows = n;
        self.columns = m;
        self.n = nz;
        self.A = vector_from_arr(nz, A);
        self.IA = vector_from_arr(nz, IA);
        self.JA = JA;
    }
    free(A);
    free(IA);
    return self;
}

void sparse_delete(sparse_t *self)
{
    vector_delete(&self->A);
    vector_delete(&self->IA);
    cons_delete(self->JA);
}

void sparse_print(sparse_t *self)
{
	return;
    printf("Sparse matrix %dx%d of %d elements\n", self->rows, self->columns, self->n);
    if (self->n == 0)
        return;
    printf("VALUES:\n");
    for (int i = 0; i < self->n; i++)
        printf("%d ", vector_get(&self->A, i));
    printf("\nIA:\n");
    for (int i = 0; i < self->n; i++)
        printf("%d ", vector_get(&self->IA, i));
    printf("\nJA:\n");
    cons_t *c = self->JA;
    while (c != NULL)
    {
        printf("%d ", c->value);
        c = c->next;
    }
    printf("\n");
}

void sparse_print_pretty(sparse_t *self)
{
    printf("row\tcol\tval\n");
    for (int j = 0; j < self->columns; j++)
    {
        int nz_start = cons_get(self->JA, j);
        int nz_end = cons_get(self->JA, j + 1);
        for (int nz_id = nz_start; nz_id < nz_end; nz_id++)
        {
            int i = vector_get(&self->IA, nz_id);
            printf("A[%d]\t[%d]\t = %d\n", i, j, vector_get(&self->A, nz_id));
        }
    }
}

// m x n * n x 1  = m x 1
sparse_t sparse_vector_product(sparse_t *self, sparse_t *vector)
{
    assert(vector->columns == 1);
    assert(vector->rows == self->columns);

    matrix_t temp_res = matrix_new(self->rows, 1);
    // if (self->n == 0 || vector->n == 0)

    for (int j = 0; j < self->columns; j++)
    {
        int nz_start = cons_get(self->JA, j);
        int nz_end = cons_get(self->JA, j + 1);

        for (int mat_nz_idx = nz_start; mat_nz_idx < nz_end; mat_nz_idx++)
        {
            int i = vector_get(&self->IA, mat_nz_idx);
            //int i = self->IA.arr[mat_nz_idx];
            for (int vector_nz_idx = 0; vector_nz_idx < vector->n; vector_nz_idx++)
            {
                //int j_vector = vector_get(&vector->IA, vector_nz_idx);
                int j_vector = vector->IA.arr[vector_nz_idx];
                if (j == j_vector)
                {
                    int mul = vector_get(&vector->A, vector_nz_idx) * vector_get(&self->A, mat_nz_idx);
                    //int mul = vector->A.arr[vector_nz_idx] * self->A.arr[mat_nz_idx];
                    #ifdef DEBUG
                    printf("sparse: res[%d] += self[%d][%d] * vector[%d] = %d\n", i, i, j, j_vector, mul);
                    #endif // DEBUG
                    temp_res.data[0][i] += mul;
                    break;
                }
            }
        }
    }

    sparse_t res = sparse_from_matrix(&temp_res);
    matrix_delete(&temp_res);
    return res;
}

int sparse_equal_dense(sparse_t *self, matrix_t *dense)
{
    for (int j = 0; j < self->columns; j++)
    {
        int nz_start = cons_get(self->JA, j);
        int nz_end = cons_get(self->JA, j + 1);
        for (int nz_id = nz_start; nz_id < nz_end; nz_id++)
        {
            int i = vector_get(&self->IA, nz_id);
            if (dense->data[i][j] != vector_get(&self->A, nz_id))
            {
                printf("%d != %d\n", dense->data[i][j], vector_get(&self->A, nz_id));
                return 0;
            }
        }
    }
    return 1;
}

size_t sparse_size(sparse_t *self)
{
  return sizeof(*self) + vector_size(&self->A) + vector_size(&self->IA) + cons_size(self->JA);
}
