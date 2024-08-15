#include "SparsePolynomial.h"

#include <algorithm>
#include <cassert>
#include <iostream>

void SparsePolynomial::NewTerm(float coef, int exp) {
  if (coef == 0.0f) return;

  if (num_terms_ >= capacity_ || num_terms_ == capacity_ - 1) {
    capacity_ = capacity_ > 0 ? capacity_ * 2 : 1;
    Term* new_term = new Term[capacity_];

    std::memcpy(new_term, terms_, sizeof(Term) * num_terms_);

    if (terms_) delete[] terms_;
    terms_ = new_term;
  }

  terms_[num_terms_].coef = coef;
  terms_[num_terms_].exp = exp;

  num_terms_++;
}

float SparsePolynomial::Eval(float x) {
  float temp = 0.0f;

  for (int i = 0; i < num_terms_; i++) {
    if (terms_[i].exp == 0)
      temp += terms_[i].coef;
    else
      temp += terms_[i].coef * pow(x, terms_[i].exp);
  }

  return temp;
}

SparsePolynomial SparsePolynomial::Add(const SparsePolynomial& poly) {
  SparsePolynomial temp;

  temp.capacity_ = this->num_terms_ + poly.num_terms_;

  temp.terms_ = new Term[temp.capacity_];

  int i = 0;
  int j = 0;
  int index = 0;

  while (1) {
    if (i == this->num_terms_ && j == poly.num_terms_) break;

    if (i == this->num_terms_)
      this->terms_[i].exp = poly.terms_[poly.num_terms_ - 1].exp + 1;

    if (j == poly.num_terms_)
      poly.terms_[j].exp = this->terms_[this->num_terms_ - 1].exp + 1;

    if (this->terms_[i].exp == poly.terms_[j].exp) {
      temp.terms_[index].coef = this->terms_[i].coef + poly.terms_[j].coef;
      temp.terms_[index].exp = this->terms_[i].exp;

      index++;
      i++;
      j++;
      temp.num_terms_++;
      continue;
    } else if (this->terms_[i].exp > poly.terms_[j].exp) {
      temp.terms_[index].coef = poly.terms_[j].coef;
      temp.terms_[index].exp = poly.terms_[j].exp;

      index++;
      j++;
      temp.num_terms_++;
      continue;
    } else if (this->terms_[i].exp < poly.terms_[j].exp) {
      temp.terms_[index].coef = this->terms_[i].coef;
      temp.terms_[index].exp = this->terms_[i].exp;

      index++;
      i++;
      temp.num_terms_++;
      continue;
    }
  }

  return temp;
}

void SparsePolynomial::Print() {
  for (int i = num_terms_ - 1; i >= 0; i--) {
    if (terms_[i].exp == 0)
      std::cout << terms_[i].coef << '\n';
    else {
      std::cout << terms_[i].coef << "x^" << terms_[i].exp << " + ";
    }
  }
}