#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    // Проверка на корректность входной матрицы
    if (A == NULL || A->matrix == NULL || A->rows != A->columns) {
        return INCORRECT_MATRIX;  // Некорректная матрица
    }

    int n = A->rows;
    double det;

    // Вычисление определителя матрицы A
    if (s21_determinant(A, &det) != OK || det == 0) {
        return CALCULATION_ERROR;  // Матрица вырождена, обратной матрицы не существует
    }

    // Создание матрицы алгебраических дополнений
    matrix_t complements;
    if (s21_create_matrix(n, n, &complements) != OK) {
        return INCORRECT_MATRIX;  // Ошибка при создании матрицы
    }

    // Вычисление матрицы алгебраических дополнений
    if (s21_calc_complements(A, &complements) != OK) {
        s21_remove_matrix(&complements);  // Освобождение памяти в случае ошибки
        return CALCULATION_ERROR;
    }

    // Транспонирование матрицы алгебраических дополнений
    if (s21_transpose(&complements, result) != OK) {
        s21_remove_matrix(&complements);  // Освобождение памяти в случае ошибки
        return CALCULATION_ERROR;
    }

    // Делим каждую ячейку результирующей матрицы на определитель
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result->matrix[i][j] /= det;
        }
    }

    // Освобождение памяти для матрицы алгебраических дополнений
    s21_remove_matrix(&complements);

    return OK;  // Успешное выполнение
}
