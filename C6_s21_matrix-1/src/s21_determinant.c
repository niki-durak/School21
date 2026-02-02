#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
    // Проверка на корректность входных данных
    if (A == NULL || A->matrix == NULL || A->rows != A->columns) {
        return INCORRECT_MATRIX;  // Некорректная матрица
    }

    int n = A->rows;

    // Базовый случай: определитель 1x1
    if (n == 1) {
        *result = A->matrix[0][0];
        return OK;
    }

    // Базовый случай: определитель 2x2
    if (n == 2) {
        *result = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
        return OK;
    }

    double det = 0;  // Переменная для хранения определителя

    // Вспомогательная матрица для хранения миноров
    matrix_t minor;
    s21_create_matrix(n - 1, n - 1, &minor);

    // Вычисление определителя по формуле разложения по первой строке
    for (int j = 0; j < n; j++) {
        // Формирование минора для элемента A[0][j]
        for (int row = 1; row < n; row++) {  // Пропускаем первую строку
            for (int col = 0, m_col = 0; col < n; col++) {
                if (col == j) continue;  // Пропускаем текущий столбец
                minor.matrix[row - 1][m_col] = A->matrix[row][col];
                m_col++;
            }
        }

        // Вычисляем определитель минора
        double minor_det;
        s21_determinant(&minor, &minor_det);

        // Суммируем определитель с учетом знака
        det += (j % 2 == 0 ? 1 : -1) * A->matrix[0][j] * minor_det;
    }

    // Освобождение памяти для минора
    s21_remove_matrix(&minor);

    *result = det;  // Сохраняем определитель в указателе result

    return OK;  // Успешное выполнение
}
