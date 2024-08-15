#include <cmath>
#include <iostream>

#include "../shared/SinglyLinkedList.h"

struct Term {
  float coef;
  int exp;
};

class LinkedPolynomial : public SinglyLinkedList<Term> {
 public:
  typedef SinglyLinkedList<Term>::Node Node;

  void NewTerm(float coef, int exp) { PushBack({coef, exp}); }

  float Eval(float x) {
    float sum = 0.0f;

    Node* temp = first_;
    while (temp) {
      sum += temp->item.coef * pow(x, temp->item.exp);
      temp = temp->next;
    }
    return sum;
  }

  LinkedPolynomial Add(const LinkedPolynomial& poly) {
    LinkedPolynomial temp;
    Node* i = this->first_;
    Node* j = poly.first_;

    while (i && j) {
      if (i->item.exp == j->item.exp) {
        temp.PushBack({i->item.coef + j->item.coef, i->item.exp});
        i = i->next;
        j = j->next;
      } else if (i->item.exp < j->item.exp) {
        temp.PushBack({i->item.coef, i->item.exp});
        i = i->next;
      } else if (i->item.exp > j->item.exp) {
        temp.PushBack({j->item.coef, j->item.exp});
        j = j->next;
      }
    }

    if (i == nullptr) {
      while (j) {
        temp.PushBack({j->item.coef, j->item.exp});
        j = j->next;
      }
    } else if (j == nullptr) {
      while (i) {
        temp.PushBack({i->item.coef, i->item.exp});
        i = i->next;
      }
    }

    return temp;
  }

  void Print() {
    bool is_first = true;

    Node* current = first_;
    while (current->next) {
      std::cout << current->item.coef << "*x^" << current->item.exp;
      if (is_first) std::cout << " + ";
      current = current->next;
    }
    std::cout << current->item.coef << "*x^" << current->item.exp << '\n';
  }

 private:
};

int main(void) {
  LinkedPolynomial p1;

  p1.NewTerm(1.0f, 0);
  p1.NewTerm(1.5f, 1);
  p1.NewTerm(2.0f, 2);

  p1.Print();

  std::cout << p1.Eval(0.0f) << '\n';  // 1 + 1.5*0 + 2*0^2 = 1
  std::cout << p1.Eval(1.0f) << '\n';  // 1 + 1.5*1 + 2*1^2 = 4.5
  std::cout << p1.Eval(2.0f) << '\n';  // 1 + 1.5*2 + 2*2^2 = 1 + 3 + 8 = 12
  std::cout << '\n';

  // Add() Test1
  std::cout << "Add() Test" << '\n';
  {
    LinkedPolynomial p1;  // max_degree는 기본값으로 설정

    // exp가 작은 항부터 추가한다고 가정
    p1.NewTerm(1.0f, 0);
    p1.NewTerm(1.5f, 1);
    p1.NewTerm(2.0f, 2);

    p1.Print();  // 1 + 1.5*x^1 + 2*x^2

    LinkedPolynomial p2;

    // exp가 작은 항부터 추가한다고 가정
    p2.NewTerm(1.0f, 1);
    p2.NewTerm(3.0f, 2);
    p2.NewTerm(5.0f, 7);
    p2.NewTerm(2.0f, 11);

    p2.Print();  // 1*x^1 + 3*x^2 + 5*x^7 + 2*x^11

    std::cout << '\n';

    LinkedPolynomial psum = p1.Add(p2);
    psum.Print();  // 1 + 2.5*x^1 + 5*x^2 + 5*x^7 + 2*x^11

    std::cout << '\n';
  }

  // Add() Test2
  std::cout << "Add() Test2" << '\n';
  {
    LinkedPolynomial p1;  // max_degree는 기본값으로 설정

    // exp가 작은 항부터 추가한다고 가정
    p1.NewTerm(1.0f, 0);
    p1.NewTerm(1.5f, 1);
    p1.NewTerm(2.0f, 2);
    p1.NewTerm(5.0f, 7);
    p1.NewTerm(3.5f, 10);
    p1.NewTerm(5.5f, 20);
    p1.NewTerm(5.0f, 1000);

    p1.Print();  // 1 + 1.5*x^1 + 2*x^2 + 5*x^7 + 3.5*x^10 + 5.5*x^20 +5*x^1000

    LinkedPolynomial p2;

    // exp가 작은 항부터 추가한다고 가정
    p2.NewTerm(3.2f, 0);
    p2.NewTerm(1.0f, 1);
    p2.NewTerm(3.0f, 2);
    p2.NewTerm(2.0f, 11);

    p2.Print();  // 3.2 + 1*x^1 + 3*x^2 + 2*x^11

    std::cout << '\n';

    LinkedPolynomial psum = p1.Add(p2);
    psum.Print();  // 4.2 + 2.5*x^1 + 5*x^2 + 5*x^7 + 3.5*x^10 + 2*x^11
                   // + 5.5*x^20 + 5*x^1000

    std::cout << '\n';
  }

  return 0;
}