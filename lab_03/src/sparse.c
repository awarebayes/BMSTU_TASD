#include "sparse.h"
#include "cons.h"

sparse_t sparse_from_matrix(matrix_t *m)
{
    spars_t self = {0};
    self.rows = m->rows;
    self.columns = m->columns;
    self.n = matrix_n_nonzero(m);
    int el_count = 0;
    for (int i = 0; i < self.rows; i++)
    {
        int first_el = 1;
        for (int j = 0; j < self.columns; j++)
         {
            if (m->data[i][j] != 0)
            {
                self.values[el_count] = m->data[i][j];
                self.columns[el_count] = j;
                if (first_el)
                {
                    cons_add(self.row_ptr, el_count);
                    first_el = 0;
                }
                el_count++;
            }
        }
    }
}

void sparse_print(matrix_t *self)
{
    for (int i = 0; i < self->n; i)
    {
        
    }
}