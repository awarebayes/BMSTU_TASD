#include "../inc/any_matrix.h"


void any_matrix_as(any_matrix_t *self, int type)
{
    if (type == self->type)
        return;
    if (self->type == any_matrix_sparse)
    {
        sparse_t my_sparse = self->kind.sparse;
        self->kind.dense = matrix_from_sparse(&my_sparse);
        sparse_delete(&my_sparse);
        self->type = any_matrix_dense;
    }
    if (self->type == any_matrix_dense)
    {
        matrix_t my_dense = self->kind.dense;
        self->kind.sparse = sparse_from_matrix(&my_dense);
        matrix_delete(&my_dense);
        self->type = any_matrix_sparse;
    }
}

void any_matrix_print(any_matrix_t *self)
{
    if (self->type == any_matrix_dense)
        matrix_print(&self->kind.dense);
    if (self->type == any_matrix_sparse)
        sparse_print_pretty(&self->kind.sparse);
}

any_matrix_t any_matrix_from_file(int type, FILE *fin, FILE *fout, int *ec)
{
    any_matrix_t self = { .type = type };
    if (type == any_matrix_dense)
        self.kind.dense = matrix_from_file(fin, fout, ec);
    if (type == any_matrix_sparse)
        self.kind.sparse = sparse_from_file(fin, fout, ec);
    return self;
}

any_matrix_t any_matrix_vector_product(any_matrix_t *matrix, any_matrix_t *vector, int type)
{
    any_matrix_as(matrix, type);
    any_matrix_as(vector, type);
    any_matrix_t res = { .type = type };

    if (type == any_matrix_dense)
        res.kind.dense = matrix_vector_product(&matrix->kind.dense, &vector->kind.dense);
    if (type == any_matrix_sparse)
        res.kind.sparse = sparse_vector_product(&matrix->kind.sparse, &vector->kind.sparse);
    return res;
}