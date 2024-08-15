#include "SparseMatrix.h"

#include <algorithm>
#include <cassert>
#include <iostream>

SparseMatrix::SparseMatrix(int num_rows, int num_cols, int capacity)
    : num_rows_(num_rows), num_cols_(num_cols), capacity_(capacity) {
  terms_ = new MatrixTerm[capacity_];
}

SparseMatrix::SparseMatrix(const SparseMatrix& b)
    : num_rows_(b.num_rows_),
      num_cols_(b.num_cols_),
      num_terms_(b.num_terms_),
      capacity_(b.capacity_) {
  terms_ = new MatrixTerm[capacity_];
  std::memcpy(terms_, b.terms_, sizeof(MatrixTerm) * num_terms_);
}

SparseMatrix::~SparseMatrix() {
  if (terms_) delete[] terms_;
}

void SparseMatrix::SetValue(int row, int col, int value) {
  //   for (int i = 0; i < num_terms_; i++) {  // 중복 있는지 검사
  //     if (terms_[i].row == row && terms_[i].col == col) {
  //       terms_[i].value = value;
  //       return;
  //     }
  //   }

  int key = col + num_cols_ * row;
  int i = 0;
  for (; i < num_terms_; i++) {
    int key_i = terms_[i].col + num_cols_ * terms_[i].row;
    if (key_i == key) {  // 중복 검사 2
      terms_[i].value = value;
      return;
    } else if (key_i > key)
      break;
  }

  //   assert(num_terms_ > capacity_);
  num_terms_++;

  for (int j = num_terms_ - 1; j > i; j--) {
    terms_[j] = terms_[j - 1];
  }

  terms_[i].row = row;
  terms_[i].col = col;
  terms_[i].value = value;
}

float SparseMatrix::Getvalue(int row, int col) const {
  for (int i = 0; i < num_terms_; i++) {
    if (terms_[i].row == row && terms_[i].col == col) {
      return terms_[i].value;
    }
  }
  return 0.0f;
}

SparseMatrix SparseMatrix::Transpose() const {
  SparseMatrix temp(num_cols_, num_rows_, capacity_);

  for (int i = 0; i < num_terms_; i++) {
    temp.terms_[i].value = terms_[i].value;
    temp.terms_[i].row = terms_[i].col;
    temp.terms_[i].col = terms_[i].row;
    temp.num_terms_++;
  }

  return temp;
}

void SparseMatrix::PrintTerms() const {
  for (int i = 0; i < num_terms_; i++) {
    std::cout << "(" << terms_[i].row << ", " << terms_[i].col << ", "
              << terms_[i].value << ")" << '\n';
  }
}

void SparseMatrix::Print() const {
  for (int i = 0; i < num_rows_; i++) {
    for (int j = 0; j < num_cols_; j++) {
      std::cout << Getvalue(i, j) << " ";
    }
    std::cout << '\n';
  }
}