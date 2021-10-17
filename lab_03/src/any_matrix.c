#include "../inc/any_matrix.h"
#include "../inc/profile.h"

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
    else if (self->type == any_matrix_dense)
    {
        matrix_t my_dense = self->kind.dense;
        self->kind.sparse = sparse_from_matrix(&my_dense);
        matrix_delete(&my_dense);
        self->type = any_matrix_sparse;
    }
}

void any_matrix_delete(any_matrix_t *self)
{
    if (self->type == any_matrix_dense)
        matrix_delete(&self->kind.dense);
    if (self->type == any_matrix_sparse)
        sparse_delete(&self->kind.sparse);
}

int any_matrix_rows(any_matrix_t *self)
{
    if (self->type == any_matrix_dense)
        return self->kind.dense.rows;
    if (self->type == any_matrix_sparse)
        return self->kind.sparse.rows;
    return -1;
}

int any_matrix_columns(any_matrix_t *self)
{
    if (self->type == any_matrix_dense)
        return self->kind.dense.columns;
    if (self->type == any_matrix_sparse)
        return self->kind.sparse.columns;
    return -1;
}

void any_matrix_print(any_matrix_t *self)
{
    if (self->type == any_matrix_dense)
        matrix_print_as_sparse(&self->kind.dense);
    if (self->type == any_matrix_sparse)
        sparse_print_pretty(&self->kind.sparse);
}

any_matrix_t any_matrix_from_file(int type, FILE *fin, FILE *fout, int *ec)
{
    any_matrix_t self = { 0 };
    if (type == any_matrix_dense)
    {
        self.kind.dense = matrix_from_file(fin, fout, ec);
		self.type = any_matrix_dense;
	}
    if (type == any_matrix_sparse)
    {
	    self.kind.dense = matrix_from_coord_file(fin, fout, ec);
	    self.type = any_matrix_dense;
		if (!*ec)
			any_matrix_as(&self, any_matrix_sparse);
    }
	return self;
}

any_matrix_t any_matrix_vector_product(int type, any_matrix_t *matrix, any_matrix_t *vector)
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

any_matrix_t any_matrix_random(int type, int rows, int cols, int percentage)
{
	any_matrix_t self = {.type = any_matrix_dense};
	int *vec_arr = gen_arr(cols * rows, percentage);
	self.kind.dense = matrix_from_array(vec_arr, rows, cols);
	any_matrix_as(&self, type);
	return self;
}
