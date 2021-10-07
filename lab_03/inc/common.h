#ifndef __COMMON_H__
#define __COMMON_H__

#define N_COLS 1000
#define N_ROWS 1000
#define MAX_MATRIX_ELEMS N_ROWS * N_COLS

void transform(int **out, int *arr, int rows, int cols);

#endif // !__COMMON_H__