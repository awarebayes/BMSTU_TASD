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
        int nz_end = cons_get(self->JA, j+1);
        for (int nz_id = nz_start; nz_id < nz_end; nz_id++)
        {
            int i = vector_get(&self->IA, nz_id);
            printf("A[%d]\t[%d]\t=%d\n", i, j, vector_get(&self->A, nz_id));
        }
    }
}

sparse_t sparse_vector_product_init(sparse_t *self, sparse_t *vector)
{
    int temp[self->columns];
    for (int i = 0; i < self->rows; i++)
    {

    }
    sparse_t res = {0};
    res.rows = self->columns;
    res.columns = 1;
}

// m x n * n x 1  = m x 1
sparse_t sparse_vector_product(sparse_t *self, sparse_t *vector)
{
    assert(vector->columns == 1);
    printf("row\tcol\tval\n");
    for (int j = 0; j < self->columns; j++)
    {
        int nz_start = cons_get(self->JA, j);
        int nz_end = cons_get(self->JA, j+1);
        for (int nz_id = nz_start; nz_id < nz_end; nz_id++)
        {
            int i = vector_get(&self->IA, nz_id);
            int value = vector_get(&self->A, nz_id);

        }
    }
}