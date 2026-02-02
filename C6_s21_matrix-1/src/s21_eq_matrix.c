#include "s21_eq_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    // Проверка на корректность матриц
    if (A == NULL || B == NULL || A->rows != B->rows || A->columns != B->columns) {
        return FAILURE;  // Матрицы некорректны или имеют разные размеры
    }

    // Задаем небольшую погрешность для сравнения элементов с плавающей точкой
    const double EPSILON = 1e-7;

    // Сравниваем каждый элемент матриц
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON) {
                return FAILURE;  // Найдены разные элементы
            }
        }
    }

    return SUCCESS;  // Все элементы равны
}
