// #include "Matrix.h"

// #include <cassert>
// #include <iostream>

// Matrix::Matrix(int num_rows, int num_cols) {
//   num_rows_ = num_rows;
//   num_cols_ = num_cols;
//   values_ = new float*[num_rows_];

//   for (int i = 0; i < num_rows_; i++) {
//     values_[i] = new float[num_cols_];
//     for (int j = 0; j < num_cols_; j++) {
//       values_[i][j] = 0.0f;
//     }
//   }
// }

// Matrix::Matrix(const Matrix& b) {
//   num_rows_ = b.num_rows_;
//   num_cols_ = b.num_cols_;

//   if (values_) delete[] values_;

//   values_ = new float*[num_rows_];

//   for (int i = 0; i < num_rows_; i++) {
//     values_[i] = new float[num_cols_];
//     for (int j = 0; j < num_cols_; j++) {
//       values_[i][j] = b.values_[i][j];
//     }
//   }
// }

// Matrix::~Matrix() {
//   if (values_) {
//     for (int i = 0; i < num_rows_; i++) {
//       delete[] values_[i];
//     }
//     delete[] values_;
//   }
// }

// void Matrix::SetValue(int row, int col, int value) {
//   values_[row][col] = value;
// }

// float Matrix::GetValue(int row, int col) const { return values_[row][col]; }

// Matrix Matrix::Add(const Matrix& b) {
//   Matrix temp(num_rows_, num_cols_);
//   for (int i = 0; i < num_rows_; i++) {
//     for (int j = 0; j < num_cols_; j++) {
//       temp.values_[i][j] = values_[i][j] + b.values_[i][j];
//     }
//   }
//   return temp;
// }

// Matrix Matrix::Transpose() {
//   Matrix temp(num_cols_, num_rows_);
//   for (int i = 0; i < temp.num_rows_; i++) {
//     for (int j = 0; j < temp.num_cols_; j++) {
//       temp.values_[i][j] = values_[j][i];
//     }
//   }
//   return temp;
// }

// void Matrix::Print() {
//   for (int i = 0; i < num_rows_; i++) {
//     for (int j = 0; j < num_cols_; j++) {
//       std::cout << values_[i][j] << " ";
//     }
//     std::cout << '\n';
//   }
//   std::cout << '\n';
// }