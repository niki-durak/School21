#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    // Проверка на корректность входных данных и соответствие размеров для умножения
    if (A == NULL || B == NULL || A->columns != B->rows) {
        return INCORRECT_MATRIX;
    }

    // Создание результирующей матрицы (размер: строки A x столбцы B)
    if (s21_create_matrix(A->rows, B->columns, result) != OK) {
        return INCORRECT_MATRIX;  // Ошибка при создании матрицы
    }

    // Выполнение умножения матриц
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
            result->matrix[i][j] = 0;  // Инициализация элемента результатирующей матрицы
            for (int k = 0; k < A->columns; k++) {
                result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
        }
    }

    return OK;  // Успешное выполнение
}
