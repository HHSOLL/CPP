#include <cassert>
#include <iomanip>
#include <iostream>

template <typename T>

class Queue {
 public:
  Queue(int capacity = 2) : capacity_(capacity), rear_(0), front_(0) {
    Queue_ = new T[capacity_];
  }

  ~Queue() {
    if (Queue_) delete[] Queue_;
  };

  bool IsEmpty() { return front_ == rear_; }

  bool IsFull() { return ((rear_ + 1) % capacity_ == front_ % capacity_); }

  T& Front() { return Queue_[front_ % capacity_]; }

  T& Rear() { return Queue_[(rear_ - 1) % capacity_]; }

  int Size() {
    if (front_ <= rear_)
      return rear_ - front_;
    else
      return capacity_ - front_ + rear_;

    return 0;
  }

  void Resize() {
    T* New_Queue = new T[capacity_ * 2];

    if (front_ < rear_) {
      std::memcpy(New_Queue, Queue_ + front_, sizeof(T) * (rear_ - front_));
    } else if (front_ > rear_) {
      std::memcpy(New_Queue, Queue_ + front_, sizeof(T) * (capacity_ - front_));
      std::memcpy(New_Queue + capacity_ - front_, Queue_, sizeof(T) * (rear_));
    }
    delete[] Queue_;
    Queue_ = New_Queue;
    front_ = 0;
    rear_ = capacity_ - 1;
    capacity_ *= 2;
  }

  void Enqueue(const T& item) {
    if ((rear_ + 1) % capacity_ == front_) Resize();

    Queue_[rear_] = item;
    rear_++;
    rear_ %= capacity_;
  }

  void Dequeue() {
    if (IsEmpty()) {
      std::cout << "underflow" << '\n';
      return;
    }

    // Queue_[front_] = '0';
    front_++;
    front_ %= capacity_;
  }

  void Print() {
    int index = front_;
    while (index % capacity_ != rear_ % capacity_) {
      std::cout << Queue_[index++ % capacity_] << " ";
    }
    std::cout << '\n';
  }

  void PrintDebug() {
    using namespace std;

    cout << "Cap = " << capacity_ << ", Size = " << Size();
    cout << endl;

    // front와 rear 위치 표시
    for (int i = 0; i < capacity_; i++) {
      if (i == front_)
        cout << " F ";
      else if (i == rear_)
        cout << " R ";
      else
        cout << "   ";
    }
    cout << endl;

    // 0 based index
    for (int i = 0; i < capacity_; i++) cout << setw(2) << i << " ";
    cout << endl;

    if (front_ < rear_) {
      // front 앞 사용하지 않은 공간
      for (int i = 0; i < front_ + 1; i++) cout << " - ";

      // 저장된 내용물
      for (int i = front_ + 1; i <= rear_; i++)
        cout << setw(2) << Queue_[i] << " ";

      // rear 뒤 사용하지 않은 공간
      for (int i = rear_ + 1; i < capacity_; i++) cout << " * ";

      cout << endl << endl;
    } else if (front_ > rear_) {
      // rear 이전에 저장된 내용물
      for (int i = 0; i <= rear_; i++) cout << setw(2) << Queue_[i] << " ";

      // rear와 front 사이 사용하지 않은 공간
      for (int i = rear_ + 1; i <= front_; i++) cout << " * ";

      // front 뒤 내용물
      for (int i = front_ + 1; i < capacity_; i++)
        cout << setw(2) << Queue_[i] << " ";

      cout << endl << endl;
    } else  // 비었을 경우
    {
      for (int i = 0; i < capacity_; i++) cout << " - ";
      cout << endl << endl;
    }
  }

  void SetDebugFlag(bool flag) { print_debug_ = flag; }

 protected:
  T* Queue_ = nullptr;
  int front_ = 0;
  int rear_ = 0;
  int capacity_;
  bool print_debug_ = true;
};