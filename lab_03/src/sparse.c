#include "sparse.h"
#include "cons.h"
#include <assert.h>
#include <stdio.h>

sparse_t sparse_from_matrix(matrix_t *m)
{
    sparse_t self = {0};
    self.rows = m->rows;
    self.columns = m->columns;
    self.n = matrix_n_nonzero(m);
    self.JA = NULL;
    self.A = vector_new(16);
    self.IA = vector_new(16);
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

void sparse_print(sparse_t *self)
{
    printf("Sparse matrix of %d elements:\n", self->n);
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
            printf("A[%d]\t[%d]\t=%d\n", i, j, vector_get(&self->A, nz_id));
        }
    }
}

// m x n * n x 1  = m x 1
sparse_t sparse_vector_product(sparse_t *self, sparse_t *vector)
{
    assert(vector->columns == 1);
    assert(vector->rows == self->columns);

    int temp_res[self->columns];
    for (int i = 0; i < self->columns; i++)
        temp_res[i] = 0;
    

    for (int j = 0; j < self->columns; j++)
    {
        int nz_start = cons_get(self->JA, j);
        int nz_end = cons_get(self->JA, j + 1);
        for (int mat_nz_idx = nz_start; mat_nz_idx < nz_end; mat_nz_idx++)
        {
            int i = vector_get(&self->IA, mat_nz_idx);
            for (int vector_nz_idx = 0; vector_nz_idx < vector->n; vector_nz_idx++)
            {
                int j_vector = vector_get(&vector->IA, vector_nz_idx);
                if (i == j_vector)
                {
                    // printf("Multiplying mat[%d][%d] with vec[1][%d]\n", i, j, j_vector);
                    int mul = vector_get(&vector->A, vector_nz_idx) * vector_get(&self->A, mat_nz_idx);
                    temp_res[j] += mul;
                    break;
                }
            }
        }
    }

    matrix_t res_mat = matrix_from_array(temp_res, self->columns, 1);
    sparse_t res = sparse_from_matrix(&res_mat);
    matrix_delete(&res_mat);
    return res;
}