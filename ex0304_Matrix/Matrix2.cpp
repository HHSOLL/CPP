#include <cassert>
#include <iostream>

#include "Matrix.h"

Matrix::Matrix(int num_rows, int num_cols) {
  num_rows_ = num_rows;
  num_cols_ = num_cols;
  values_ = new float[num_rows_ * num_cols_];

  for (int i = 0; i < num_rows_ * num_cols_; i++) {
    values_[i] = 0.0f;
  }
}

Matrix::Matrix(const Matrix& b) {
  num_rows_ = b.num_rows_;
  num_cols_ = b.num_cols_;
  values_ = new float[b.num_rows_ * b.num_cols_];

  for (int i = 0; i < num_rows_ * num_cols_; i++) {
    values_[i] = b.values_[i];
  }
}

Matrix::~Matrix() {
  if (values_) delete[] values_;
}

void Matrix::SetValue(int row, int col, int value) {
  values_[col + num_cols_ * row] = value;
}

float Matrix::GetValue(int row, int col) const {
  return values_[col + num_cols_ * row];
}

Matrix Matrix::Add(const Matrix& b) {
  Matrix temp(num_rows_, num_cols_);
  for (int i = 0; i < num_rows_ * num_cols_; i++) {
    temp.values_[i] = values_[i] + b.values_[i];
  }
  return temp;
}

Matrix Matrix::Transpose() {
  Matrix temp(num_cols_, num_rows_);

  int index = 0;
  for (int i = 0; i < temp.num_rows_; i++) {
    for (int j = 0; j < temp.num_cols_; j++) {
      temp.values_[index] = values_[i + j * num_cols_];
      index++;
    }
  }

  return temp;
}

void Matrix::Print() {
  int index = 0;
  for (int i = 0; i < num_rows_; i++) {
    for (int j = 0; j < num_cols_; j++) {
      std::cout << values_[index++] << " ";
    }
    std::cout << '\n';
  }
}