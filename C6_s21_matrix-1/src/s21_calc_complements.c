#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    // Проверка на корректность матрицы (она должна быть квадратной)
    if (A == NULL || A->matrix == NULL || A->rows != A->columns || A->rows < 1) {
        return INCORRECT_MATRIX;
    }

    int n = A->rows; // Размер квадратной матрицы

    // Создание матрицы для хранения алгебраических дополнений
    if (s21_create_matrix(n, n, result) != OK) {
        return INCORRECT_MATRIX;  // Ошибка при создании матрицы
    }

    // Вспомогательная матрица для хранения миноров
    matrix_t minor;
    s21_create_matrix(n - 1, n - 1, &minor);

    // Вычисление алгебраических дополнений
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Формирование минора для элемента A[i][j]
            for (int row = 0, m_row = 0; row < n; row++) {
                if (row == i) continue;  // Пропускаем текущую строку
                for (int col = 0, m_col = 0; col < n; col++) {
                    if (col == j) continue;  // Пропускаем текущий столбец
                    minor.matrix[m_row][m_col] = A->matrix[row][col];
                    m_col++;
                }
                m_row++;
            }

            // Вычисление определителя минора
            double det_minor;
            s21_determinant(&minor, &det_minor);

            // Алгебраическое дополнение для элемента A[i][j]
            result->matrix[i][j] = pow(-1, i + j) * det_minor;
        }
    }

    // Освобождение памяти для минора
    s21_remove_matrix(&minor);

    return OK;  // Успешное выполнение
}
