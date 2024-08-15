#include "ArrayOfArrays.h"

#include <iostream>

Array2D::Array2D(int num_rows, int num_cols) {
  num_rows_ = num_rows;
  num_cols_ = num_cols;

  arrays_ = new float*[num_rows_];
  for (int i = 0; i < num_rows_; i++) {
    arrays_[i] = new float[num_cols_];
    for (int j = 0; j < num_cols; j++) {
      arrays_[i][j] = 0.0f;
    }
  }
}

Array2D::Array2D(const Array2D& b) {
  num_rows_ = b.num_rows_;
  num_cols_ = b.num_cols_;

  for (int i = 0; i < num_rows_; i++) {
    for (int j = 0; j < num_cols_; j++) {
      arrays_[i][j] = b.arrays_[i][j];
    }
  }
}

Array2D::~Array2D() {
  for (int i = 0; i < num_rows_; i++) {
    if (arrays_[i]) {
      delete[] arrays_[i];
    }
  }
  if (arrays_) delete[] arrays_;
}

void Array2D::SetValue(int row, int col, float value) {
  arrays_[row][col] = value;
}

float Array2D::GetValue(int row, int col) const { return arrays_[row][col]; }

Array2D Array2D::Add(const Array2D& b) {
  Array2D temp(num_rows_, num_cols_);

  for (int i = 0; i < num_rows_; i++) {
    for (int j = 0; j < num_cols_; j++) {
      temp.SetValue(i, j, GetValue(i, j) + b.GetValue(i, j));
    }
  }

  return temp;
}

Array2D Array2D::Transpose() {
  Array2D temp(num_cols_, num_rows_);

  for (int i = 0; i < num_rows_; i++) {
    for (int j = 0; j < num_cols_; j++) {
      temp.SetValue(j, i, GetValue(i, j));
    }
  }
  return temp;
}

void Array2D::Print() {
  for (int i = 0; i < num_rows_; i++) {
    for (int j = 0; j < num_cols_; j++) {
      std::cout << arrays_[i][j] << " ";
    }
    std::cout << '\n';
  }
}