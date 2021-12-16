//
// Created by dev on 12/13/21.
//

#include "matrix.h"
#include <stdlib.h>
#include <string.h>

matrix matrix_new(int n)
{
	matrix self = { 0 };
	self.n = n;
	void *ptr = calloc(sizeof(int *) * n + sizeof(int) * n * n, sizeof(char));
	char *cptr = (char *) ptr;
	int **pa = (int **) cptr;
	int *data_ptr = (int *) (cptr + sizeof(int *) * n);
	for (int i = 0; i < n; i++)
		*(pa + i) = data_ptr + n * i;
	self.values = pa;
	return self;
}

void matrix_delete(matrix *self)
{
	free(self->values);
}

matrix matrix_copy(matrix *self)
{
	matrix copy = matrix_new(self->n);
	for (int i = 0; i < self->n; i++)
		for (int j = 0; j < self->n; j++)
			copy.values[i][j] = self->values[i][j];
	return copy;
}

void matrix_print(matrix *self, FILE *fout)
{
	fprintf(fout, "%d\n", self->n);
	for (int i = 0; i < self->n; i++)
	{
		for (int j = 0; j < self->n; j++)
		{
			int val = self->values[i][j];
			if (val == INT_MAX)
				fprintf(fout, "%-4s", "oo");
			else if (val == INT_MIN)
				fprintf(fout, "%-4s", "-oo");
			else
				fprintf(fout, "%-4d", val);
		}
		fprintf(fout, "\n");
	}

}

matrix matrix_read(FILE *fin)
{
	char buf[16];
	int n = 0;
	fscanf(fin, "%d", &n);
	matrix self = matrix_new(n);
	int temp;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			fscanf(fin, "%s", buf);
			if (strstr(buf, "-oo"))
				temp = INT_MIN;
			else if (strstr(buf, "oo"))
				temp = INT_MAX;
			else
				sscanf(buf, "%d", &temp);
			self.values[i][j] = temp;
		}
	return self;
}

matrix matrix_random(int n, float sparsity)
{
	matrix self = matrix_new(n);
	for(int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{

			float prob = ((float)rand()/(float)(RAND_MAX));
			if (prob > sparsity)
				self.values[i][j] = rand();
			else
				self.values[i][j] = INT_MAX;
		}
	}
	return self;
}


matrix floyd_warshall_step(matrix *previous, semiring *alg, int k)
{
	matrix c_k = matrix_new(previous->n);
	for (int i = 0; i < previous->n; i++)
	{
		for (int j = 0; j < previous->n; j++)
		{
			int prev_ik = previous->values[i][k];
			int prev_kj = previous->values[k][j];
			int prev_ij = previous->values[i][j];
			int d_ij = alg->multiply(prev_ik, prev_kj);
			int res = alg->add(prev_ij, d_ij);
			c_k.values[i][j] = res;
		}
	}

	return c_k;
}
