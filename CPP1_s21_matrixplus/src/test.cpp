#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// Тесты на создание матрицы
TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.GetRows(), 0);
  EXPECT_EQ(m.GetCols(), 0);
}

TEST(S21MatrixTest, ParamConstructor) {
  S21Matrix m(3, 3);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 3);
}

TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  S21Matrix m2(m1);
  EXPECT_EQ(m2(0, 0), 1.0);
  EXPECT_EQ(m2(0, 1), 2.0);
}

TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 5.0;
  S21Matrix m2(std::move(m1));
  EXPECT_EQ(m2(0, 0), 5.0);
  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);
}

// Тесты операторов
TEST(S21MatrixTest, SumOperator) {
  S21Matrix m1(2, 2), m2(2, 2);
  m1(0, 0) = 1;
  m2(0, 0) = 2;
  S21Matrix result = m1 + m2;
  EXPECT_EQ(result(0, 0), 3);
}

TEST(S21MatrixTest, SubOperator) {
  S21Matrix m1(2, 2), m2(2, 2);
  m1(0, 0) = 3;
  m2(0, 0) = 2;
  S21Matrix result = m1 - m2;
  EXPECT_EQ(result(0, 0), 1);
}

TEST(S21MatrixTest, MulOperatorMatrix) {
  S21Matrix m1(2, 2), m2(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m2(0, 0) = 3;
  m2(1, 0) = 4;
  S21Matrix result = m1 * m2;
  EXPECT_EQ(result(0, 0), 11);
}

TEST(S21MatrixTest, MulOperatorNumber) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 3;
  S21Matrix result = m1 * 2.0;
  EXPECT_EQ(result(0, 0), 6.0);
}

TEST(S21MatrixTest, EqualOperator) {
  S21Matrix m1(2, 2), m2(2, 2);
  m1(0, 0) = 5;
  m2(0, 0) = 5;
  EXPECT_TRUE(m1 == m2);
}

// Тесты методов
TEST(S21MatrixTest, Transpose) {
  S21Matrix m1(2, 3);
  m1(0, 1) = 1;
  S21Matrix result = m1.Transpose();
  EXPECT_EQ(result.GetRows(), 3);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_EQ(result(1, 0), 1);
}

TEST(S21MatrixTest, Determinant) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 3;
  m1(1, 1) = 4;
  EXPECT_EQ(m1.Determinant(), -2);
}

TEST(S21MatrixTest, Inverse) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 4;
  m1(0, 1) = 7;
  m1(1, 0) = 2;
  m1(1, 1) = 6;
  S21Matrix inv = m1.InverseMatrix();
  EXPECT_NEAR(inv(0, 0), 0.6, 1e-6);
  EXPECT_NEAR(inv(0, 1), -0.7, 1e-6);
  EXPECT_NEAR(inv(1, 0), -0.2, 1e-6);
  EXPECT_NEAR(inv(1, 1), 0.4, 1e-6);
}

TEST(S21MatrixTest, IndexOutOfRange) {
  S21Matrix m1(2, 2);
  EXPECT_THROW(m1(2, 2), std::out_of_range);
}

TEST(S21MatrixTest, SingularMatrixInverse) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(1, 0) = 2;
  m1(1, 1) = 4;
  EXPECT_THROW(m1.InverseMatrix(), std::invalid_argument);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}