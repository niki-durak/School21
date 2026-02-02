#include "s21_matrix_oop.h"

void S21Matrix::AllocateMemory() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::FreeMemory() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

// --- Конструкторы ---
S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Matrix size must be positive");
  }
  AllocateMemory();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  AllocateMemory();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { FreeMemory(); }

// --- Методы ---
void S21Matrix::CheckSizeEquality(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Matrix sizes are not equal!");
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) { return *this == other; }

void S21Matrix::SumMatrix(const S21Matrix& other) { *this += other; }

void S21Matrix::SubMatrix(const S21Matrix& other) { *this -= other; }

void S21Matrix::MulMatrix(const S21Matrix& other) { *this = *this * other; }

void S21Matrix::MulNumber(const double num) { *this = *this * num; }

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(j, i) = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Matrix must be square to calculate complements");
  }

  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = GetMinor(i, j);
      result(i, j) = pow(-1, i + j) * minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::GetMinor(int row, int col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int minor_row = 0, minor_col = 0;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i != row && j != col) {
        minor(minor_row, minor_col++) = matrix_[i][j];
        if (minor_col == cols_ - 1) {
          minor_col = 0;
          minor_row++;
        }
      }
    }
  }
  return minor;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Matrix must be square to calculate determinant");
  }

  if (rows_ == 1) {
    return matrix_[0][0];
  }

  double det = 0.0;
  for (int i = 0; i < rows_; i++) {
    S21Matrix minor = GetMinor(0, i);
    det += matrix_[0][i] * pow(-1, i) * minor.Determinant();
  }
  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (fabs(det) < 1e-6) {  // Проверка на детерминант 0
    throw std::invalid_argument("Matrix is singular and cannot be inverted");
  }

  S21Matrix complements = CalcComplements();
  S21Matrix adjugate = complements.Transpose();
  return adjugate * (1.0 / det);
}

// --- Операторы ---
S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  CheckSizeEquality(other);
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(i, j) = matrix_[i][j] + other(i, j);
    }
  }
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  CheckSizeEquality(other);
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(i, j) = matrix_[i][j] - other(i, j);
    }
  }
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  if (cols_ != other.rows_) {
    throw std::out_of_range(
        "The number of columns of the first matrix is ​​not equal to the "
        "number of rows of the second!");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result(i, j) = 0.0;
      for (int k = 0; k < cols_; k++) {
        result(i, j) += matrix_[i][k] * other(k, j);
      }
    }
  }

  return result;
}

S21Matrix S21Matrix::operator*(double number) const {
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(i, j) = matrix_[i][j] * number;
    }
  }
  return result;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {  // Защита от самоприсваивания
    FreeMemory();        // Очищаем старую память
    rows_ = other.rows_;
    cols_ = other.cols_;
    AllocateMemory();  // Выделяем новую память
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
  if (this != &other) {
    FreeMemory();  // Очищаем старую память
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;  // Забираем данные
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;  // Очищаем объект-источник
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-6) {
        return false;
      }
    }
  }
  return true;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  *this = *this + other;
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  *this = *this - other;
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  *this = *this * other;
  return *this;
}

S21Matrix& S21Matrix::operator*=(double number) {
  *this = *this * number;
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[row][col];
}
