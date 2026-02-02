#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
    if (A != NULL && A->matrix != NULL) {
        // Освобождаем память, выделенную для каждой строки
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
        // Освобождаем память, выделенную для массива указателей на строки
        free(A->matrix);

        // Обнуляем указатели и размеры, чтобы предотвратить возможное повторное использование
        A->matrix = NULL;
        A->rows = 0;
        A->columns = 0;
    }
}
