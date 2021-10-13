#include "../inc/profile.h"
#include "../inc/matrix.h"
#include "../inc/any_matrix.h"
#include <time.h>
#include <stdlib.h>
#include <assert.h>

int *gen_arr(int size, int percentage)
{
    int *arr = (int *)malloc(size * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        if (rand() % 100 <= percentage)
        {
            int num = rand() % 1000;
            arr[i] = num;
        }
    }
    return arr;
}

time_measurement_t measure_time(int n_rows, int n_cols, int percentage)
{
    clock_t start, end;
    time_measurement_t measure = { 0 };
    int *mat_arr = gen_arr(n_rows * n_cols, percentage);
    matrix_t matrix = matrix_from_array(mat_arr, n_rows, n_cols);
    free(mat_arr);

    int *vec_arr = gen_arr(n_cols, percentage);
    matrix_t vector = matrix_from_array(vec_arr, n_cols, 1);
    free(vec_arr);

    start = clock();
    matrix_t res_dense = matrix_vector_product(&matrix, &vector);
    end = clock();

    measure.dense = (end - start) * 1000000 / CLOCKS_PER_SEC;

    sparse_t smatrix = sparse_from_matrix(&matrix);
    // assert(sparse_equal_dense(&smatrix, &matrix));
    matrix_delete(&matrix);
    sparse_t svector = sparse_from_matrix(&vector);
    // assert(sparse_equal_dense(&svector, &vector));
    matrix_delete(&vector);

    start = clock();
    sparse_t res_sparse = sparse_vector_product(&smatrix, &svector);
    end = clock();
    sparse_delete(&smatrix);    
    sparse_delete(&svector);
    measure.sparse = (end - start) * 1000000 / CLOCKS_PER_SEC;

    // assert(sparse_equal_dense(&res_sparse, &res_dense));

    sparse_delete(&res_sparse);
    matrix_delete(&res_dense);

    return measure;
}

mem_measurement_t measure_memory(int n_rows, int n_cols, int percentage)
{
  mem_measurement_t measure = { 0 };
  int *mat_arr = gen_arr(n_rows * n_cols, percentage);

  matrix_t matrix = matrix_from_array(mat_arr, n_rows, n_cols);
  free(mat_arr);
  measure.dense = matrix_size(&matrix);

  sparse_t smatrix = sparse_from_matrix(&matrix);
  matrix_delete(&matrix);
  measure.sparse = sparse_size(&smatrix);
  sparse_delete(&smatrix);

  return measure;
}
