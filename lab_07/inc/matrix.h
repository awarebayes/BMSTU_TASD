//
// Created by dev on 12/13/21.
//

#ifndef LAB_07_MATRIX_H
#define LAB_07_MATRIX_H
#include "semiring.h"
#include <stdio.h>

// square matrix of nth order
typedef struct
{
	int n;
	int **values;
} matrix;


matrix matrix_new(int n);
void matrix_delete(matrix *self);
matrix floyd_warshall_step(matrix *previous, semiring *alg, int k);
matrix matrix_copy(matrix *self);
matrix matrix_read(FILE *fin);
void matrix_print(matrix *self, FILE *fout);
matrix matrix_random(int n, float sparsity);

#endif //LAB_07_MATRIX_H
