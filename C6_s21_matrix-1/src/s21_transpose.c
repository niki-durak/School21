#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
    // Проверка на корректность входных данных
    if (A == NULL || A->matrix == NULL) {
        return INCORRECT_MATRIX;
    }

    // Создание результирующей матрицы с транспонированными размерами
    if (s21_create_matrix(A->columns, A->rows, result) != OK) {
        return INCORRECT_MATRIX;  // Ошибка при создании матрицы
    }

    // Транспонирование матрицы (замена строк на столбцы)
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[j][i] = A->matrix[i][j];
        }
    }

    return OK;  // Успешное выполнение
}
