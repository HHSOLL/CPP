#include "Polynomial.h"

#include <math.h>

#include <cassert>
#include <iostream>

Polynomial::Polynomial(int max_degree) {
  assert(max_degree > 0);

  capacity_ = max_degree + 1;

  coeffs_ = new float[capacity_];

  for (int i = 0; i < capacity_; i++) {
    coeffs_[i] = 0.0f;
  }
}

Polynomial::Polynomial(const Polynomial& poly) {
  this->capacity_ = poly.capacity_;
  this->coeffs_ = new float[this->capacity_];
  std::memcpy(this->coeffs_, poly.coeffs_, this->capacity_);
}

Polynomial::~Polynomial() {
  if (coeffs_) {
    delete[] coeffs_;
    capacity_ = 0;
  }
}

int Polynomial::MaxDgree() {
  int MaxDegree = this->capacity_ - 1;

  return MaxDegree;
}

void Polynomial::NewTerm(const float coef, const int exp) {
  this->coeffs_[exp] += coef;
}

Polynomial Polynomial::Add(const Polynomial& poly) {
  int Degree =
      this->capacity_ > poly.capacity_ ? this->capacity_ : poly.capacity_;

  Polynomial temp(Degree - 1);

  for (int i = 0; i < Degree; i++) {
    temp.coeffs_[i] = this->coeffs_[i] + poly.coeffs_[i];
  }

  return temp;
}

Polynomial Polynomial::Mul(const Polynomial& poly) {
  int Degree = this->capacity_ + poly.capacity_;

  Polynomial temp(Degree - 1);

  for (int i = 0; i <= this->capacity_; i++) {
    for (int j = 0; j <= poly.capacity_; j++) {
      temp.coeffs_[i + j] += (this->coeffs_[i] * poly.coeffs_[j]);
    }
  }
  return temp;
}

float Polynomial::Eval(float x) {
  float sum = 0.0f;
  for (int i = 0; i < this->capacity_ - 1; i++) {
    if (this->coeffs_[i] != 0) {
      sum += pow(x, i) * this->coeffs_[i];
    }
  }
  return sum;
}

void Polynomial::Print() {
  bool check = false;
  int i;
  for (i = this->capacity_ - 1; i >= 0; i--) {
    if (this->coeffs_[i] != 0 && i != 0) {
      std::cout << this->coeffs_[i] << "x^" << i << " + ";
    }
  }
  std::cout << this->coeffs_[i + 1] << '\n';
}
