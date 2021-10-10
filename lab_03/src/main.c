#include <stdio.h>

/* 
 * Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов: 
 *      - вектор A содержит значения ненулевых элементов; 
 *      - вектор IA содержит номера строк для элементов вектора A; 
 *      - связный список JA, в элементе Nk которого находится номер компонент 
 * в A и IA, с которых начинается описание столбца Nk матрицы A. 
 *  
 * 1. Смоделировать операцию умножения матрицы и вектора-столбца, 
 * хранящихся в этой форме, с получением результата в той же форме. 
 * 2. Произвести операцию умножения, применяя стандартный алгоритм работы с 
 * матрицами. 
 * 3. Сравнить время выполнения операций и объем памяти при использовании 
 */

#include "matrix.h"
#include "sparse.h"

int main()
{
    int mat[5 * 4] = {
        1, 2, 0, 3,
        1, 4, 3, 6,
        0, 2, 8, 1,
        0, 5, 3, 0, 
        0, 0, 0, 4,
    };

    int vec[4 * 1] = {1, 3, 0, 5};

    matrix_t matrix = matrix_from_array(mat, 5, 4);
    matrix_print(&matrix);
    matrix_t vector = matrix_from_array(vec, 4, 1);
    sparse_t smatrix = sparse_from_matrix(&matrix);
    sparse_t svector = sparse_from_matrix(&vector);
    sparse_t sres = sparse_vector_product(&smatrix, &svector);
    matrix_t res = matrix_vector_product(&matrix, &vector);

    // sparse_print(&sres);
    sparse_print_pretty(&sres);
    matrix_print(&res);
    matrix_delete(&res);
    matrix_delete(&matrix);
    matrix_delete(&vector);

    return 0;
}