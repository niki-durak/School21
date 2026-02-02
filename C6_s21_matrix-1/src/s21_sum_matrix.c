#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    // Проверка на корректность матриц и на совпадение их размеров
    if (A == NULL || B == NULL || A->rows != B->rows || A->columns != B->columns) {
        return INCORRECT_MATRIX;  // Некорректные входные данные
    }

    // Создание результирующей матрицы
    if (s21_create_matrix(A->rows, A->columns, result) != OK) {
        return INCORRECT_MATRIX;  // Ошибка при создании матрицы
    }

    // Сложение элементов матриц A и B
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
    }

    return OK;  // Успешное выполнение
}
