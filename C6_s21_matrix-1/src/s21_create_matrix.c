#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    // Проверка на корректность входных данных
    if (rows <= 0 || columns <= 0) {
        return INCORRECT_MATRIX;
    }

    // Выделение памяти для структуры матрицы
    result->rows = rows;
    result->columns = columns;

    // Выделение памяти для массива указателей на строки
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (result->matrix == NULL) {
        return INCORRECT_MATRIX;
    }

    // Выделение памяти для каждого ряда
    for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)malloc(columns * sizeof(double));
        if (result->matrix[i] == NULL) {
            // Если произошла ошибка выделения памяти, освобождаем уже выделенную память
            for (int j = 0; j < i; j++) {
                free(result->matrix[j]);
            }
            free(result->matrix);
            return INCORRECT_MATRIX;
        }
    }

    // Инициализация элементов матрицы нулями (по необходимости)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result->matrix[i][j] = 0.0;
        }
    }

    return OK;  // Возвращаем статус успешного выполнения
}