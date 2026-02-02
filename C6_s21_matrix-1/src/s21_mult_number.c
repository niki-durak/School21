#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    // Проверка на корректность входных данных
    if (A == NULL || A->matrix == NULL) {
        return INCORRECT_MATRIX;
    }

    // Создание результирующей матрицы
    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
        return INCORRECT_MATRIX;  // Ошибка при создании матрицы
    }

    // Умножение каждого элемента матрицы A на число number
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] * number;
        }
    }

    return OK;  // Успешное выполнение
}
