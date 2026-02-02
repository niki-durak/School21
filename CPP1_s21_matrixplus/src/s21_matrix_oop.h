#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <stdexcept>  // Для исключений

class S21Matrix {
 private:
  int rows_, cols_;  // Размер матрицы
  double** matrix_;  // Двумерный массив

  void AllocateMemory();  // Выделение памяти
  void FreeMemory();      // Освобождение памяти

 public:
  // Конструкторы и деструктор
  S21Matrix();  // Конструктор по умолчанию
  S21Matrix(int rows, int cols);  // Конструктор с параметрами
  S21Matrix(const S21Matrix& other);  // Конструктор копирования
  S21Matrix(S21Matrix&& other) noexcept;  // Конструктор перемещения
  ~S21Matrix();                           // Деструктор

  void CheckSizeEquality(const S21Matrix& other) const;  // Проверка размеров

  int GetRows() const { return rows_; }
  int GetCols() const { return cols_; }

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix GetMinor(int row, int col) const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(double number) const;
  S21Matrix& operator=(const S21Matrix& other);  // Присваивание копированием
  S21Matrix& operator=(
      S21Matrix&& other) noexcept;  // Присваивание перемещением
  bool operator==(const S21Matrix& other) const;  // Проверка на равенство
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double number);
  double& operator()(int row, int col);  // Доступ к элементу
  const double& operator()(
      int row, int col) const;  // Доступ к элементу (для const объектов)
};

#endif  // S21_MATRIX_OOP_H
