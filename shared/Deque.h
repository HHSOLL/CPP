#include <cassert>
#include <iomanip>
#include <iostream>

#include "Queue.h"

template <typename T>

class Deque : public Queue<T> {
  typedef Queue<T> Base;

 public:
  Deque(int capacity = 2) : Base(capacity) {}

  T& Front() { return Base::Front(); }

  T& Back() { return Base::Rear(); }

  void PushFront(const T& item) {
    if (Base::IsFull()) Base::Resize();

    Base::front_ = (Base::front_ - 1 + Base::capacity_) % Base::capacity_;
    Base::Queue_[Base::front_] = item;
  }

  void PushBack(const T& item) { Base::Enqueue(item); }

  void PopFront() { Base::Dequeue(); }

  void PopBack() {
    assert(!Base::IsEmpty());

    Base::rear_ = (Base::rear_ - 1 + Base::capacity_) % Base::capacity_;
  }

 private:
  //   T* Queue_ = nullptr;
  //   int front_ = 0;
  //   int rear_ = 0;
  //   int capacity_ = 0;
  //   bool print_debug_ = false;

  // 이 선언을 통해
  int& rear_ = Base::rear_;
};