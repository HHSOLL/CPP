#include "Matrix.h"

#include <iostream>

Matrix::Matrix(int num_rows, int num_cols)
    : num_rows_(num_rows),
      num_cols_(num_cols),
      values_(num_rows, std::vector<float>(num_cols, 0.0f)) {}
Matrix::Matrix(const Matrix& b)
    : num_rows_(b.num_rows_), num_cols_(b.num_cols_), values_(b.values_) {}

void Matrix::SetValue(int row, int col, int value) {
  values_[row][col] = value;
}

float Matrix::GetValue(int row, int col) const { return values_[row][col]; }

Matrix Matrix::Add(const Matrix& b) {
  Matrix result(num_rows_, num_cols_);

  for (int i = 0; i < num_rows_; i++) {
    for (int j = 0; j < num_cols_; j++) {
      result.values_[i][j] = values_[i][j] + b.values_[i][j];
    }
  }
  return result;
}

Matrix Matrix::Transpose() {
  Matrix result(num_cols_, num_rows_);

  for (int i = 0; i < num_rows_; i++) {
    for (int j = 0; j < num_cols_; j++) {
      result.values_[j][i] = values_[i][j];
    }
  }

  return result;
}

void Matrix::Print() {
  for (int i = 0; i < num_rows_; i++) {
    for (int j = 0; j < num_cols_; j++) {
      std::cout << values_[i][j] << " ";
    }
    std::cout << '\n';
  }
}