#include <cassert>
#include <iomanip>
#include <iostream>

template <typename T>
class MaxHeap {
 public:
  MaxHeap(int cap = 10) : capacity_(cap), size_(0) { heap_ = new T[cap + 1]; }
  void Resize(int new_capacity) {
    T* new_heap = new T[new_capacity + 1];

    std::memcpy(new_heap, heap_, sizeof(T) * size_);
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
    int curr = size_;

    while (curr != 1 && item > heap_[curr / 2]) {
      heap_[curr] = heap_[curr / 2];

      curr /= 2;
    }
    heap_[curr] = item;
  }

  void Pop() {
    assert(!IsEmpty());
    std::cout << "POP" << '\n';
    // heap_[1].~T();

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

      curr_idx = child_idx;
    }
  }

 private:
  T* heap_ = nullptr;
  int capacity_ = 0;
  int size_ = 0;
};

struct Patient {
  int severity;
  int time;
  const char* name;

  friend bool operator>=(const Patient a, const Patient b) {
    if (a.severity == b.severity) {
      return a.time <= b.time;
    } else {
      return a.severity > b.severity;
    }
  }

  friend bool operator>(const Patient& a, const Patient& b) {
    return a.severity > b.severity;
  }
  friend bool operator<(const Patient a, const Patient b) { return !(a >= b); }

  friend std::ostream& operator<<(std::ostream& os, const Patient& p) {
    return os;
  }
};

int main(void) {
  MaxHeap<Patient> h;

  h.Push({1, 0, "Ironman"});
  h.Push({1, 1, "Nick Fury"});
  h.Push({3, 2, "Hulk"});

  std::cout << h.Top().name << '\n';
  h.Pop();

  std::cout << h.Top().name << '\n';  // 중증도가 동일하지만 먼저 도착한 Ironman
  h.Pop();

  h.Push({2, 3, "Blue Beetle"});

  std::cout << h.Top().name
            << '\n';  // 늦게 도착했지만 중증도가 높은 Blue Beetle
  h.Pop();

  std::cout << h.Top().name << '\n';  // 마지막으로 Nick Fury
  h.Pop();

  return 0;
}