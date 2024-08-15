#include <cassert>
#include <iomanip>
#include <iostream>

template <typename T>
class MaxHeap {
 public:
  MaxHeap(int cap = 10) : size_(0), capacity_(cap) {
    heap_ = new T[capacity_ + 1];
  }

  void Resize(int new_capacity) {
    T* new_heap = new T[new_capacity + 1];

    std::memcpy(new_heap, heap_, sizeof(T) * (size_ + 1));
    if (heap_) delete[] heap_;

    heap_ = new_heap;
    capacity_ = new_capacity;
  }

  T Top() { return heap_[1]; }

  bool IsEmpty() { return size_ == 0; }

  void Print() {
    using namespace std;
    cout << "index : ";
    for (int i = 1; i <= size_; i++) cout << setw(3) << i;
    cout << '\n';

    cout << "value : ";
    for (int i = 1; i <= size_; i++) cout << setw(3) << heap_[i];
    cout << '\n' << '\n';
  }

  void Push(const T& item) {
    if (size_ == capacity_) Resize(capacity_ * 2);

    size_++;
    int current = size_;

    std::cout << "Push " << item << '\n';
    while (current != 1 && item > heap_[current / 2]) {
      heap_[current] = heap_[current / 2];

      std::cout << "Current : " << current << '\n';
      Print();

      current /= 2;
    }
    heap_[current] = item;
  }

  void Pop() {
    assert(!IsEmpty());

    std::cout << "POP " << '\n';
    heap_[1].~T();

    T temp = heap_[size_];
    size_--;

    int curr_idx = 1;
    int child_idx = 1;

    while (child_idx <= size_) {
      if (size_ > curr_idx * 2) {
        child_idx = heap_[curr_idx * 2] >= heap_[curr_idx * 2 + 1]
                        ? curr_idx * 2
                        : curr_idx * 2 + 1;
      } else if (size_ == curr_idx * 2) {
        child_idx = curr_idx * 2;
      } else {
        heap_[curr_idx] = temp;
        break;
      }

      if (temp >= heap_[child_idx]) {
        heap_[curr_idx] = temp;
        break;
      } else {
        heap_[curr_idx] = heap_[child_idx];
      }

      std::cout << "curr : " << curr_idx << '\n';
      std::cout << "child : " << child_idx << '\n';
      Print();

      curr_idx = child_idx;
    }
    Print();
  }

 private:
  T* heap_ = nullptr;
  int size_ = 0;
  int capacity_ = 0;
};