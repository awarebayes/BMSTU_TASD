#include "common.h"

void transform(int **out, int *arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
        out[i] = (arr + i * cols);
}