
#include <stdint.h>

#include <cassert>
#include <iostream>

template <typename T>
class SinglyLinkedList {
 public:
  struct Node {
    T item;
    Node* next = nullptr;
  };
  SinglyLinkedList() {}

  SinglyLinkedList(const SinglyLinkedList& list) {
    Node* current = list.first_;
    while (current) {
      this->PushBack(current->item);
      current = current->next;
    }
  }
  ~SinglyLinkedList() { Clear(); }

  void Clear() {
    while (first_) {
      Node* temp = first_;
      first_ = first_->next;
      delete temp;
    }
  }

  bool IsEmpty() { return first_ == nullptr; }

  int Size() {
    int size = 0;
    Node* temp = first_;
    while (temp) {
      temp = temp->next;
      size++;
    }

    return size;
  }

  T Front() {
    assert(first_);

    return first_->item;
  }
  T Back() {
    assert(first_);

    Node* temp = first_;
    while (temp->next) temp = temp->next;
    return temp->item;
  }

  Node* Find(T item) {
    Node* temp = first_;
    while (temp) {
      if (temp->item == item) break;
      temp = temp->next;
    }
    return temp;
  }

  void InsertBack(Node* node, T item) {
    Node* temp = new Node;
    temp->item = item;
    temp->next = node->next;
    node->next = temp;
  }

  void Remove(Node* n) {
    if (first_ == n) {
      first_ = first_->next;
      delete n;
      return;
    }
    Node* temp = first_;
    while (temp) {
      if (temp->next == n) break;
      temp = temp->next;
    }
    temp->next = temp->next->next;
    delete n;
  }

  void PushFront(T item) {
    Node* new_node = new Node;
    new_node->item = item;

    new_node->next = first_;
    first_ = new_node;
  }

  void PushBack(T item) {
    if (first_ == nullptr) {
      PushFront(item);
    } else {
      Node* temp = first_;
      while (temp->next) temp = temp->next;

      Node* new_node = new Node;
      new_node->item = item;
      new_node->next = nullptr;
      temp->next = new_node;
    }
  }

  void PopFront() {
    if (first_) {
      Node* temp = first_;
      first_ = first_->next;
      delete temp;
    } else {
      std::cout << "already empty" << '\n';
      return;
    }
  }

  void PopBack() {
    if (IsEmpty()) {
      std::cout << "already empty" << '\n';
      return;
    }
    Node* temp = first_;
    Node* prev = nullptr;
    while (temp->next) {
      prev = temp;
      temp = temp->next;
    }
    prev->next = nullptr;
    delete temp;
  }

  void Reverse() {
    // if (!first_) return;

    // Node* current = first_;
    // Node* temp = first_->next;
    // current = temp;
    // temp = temp->next;
    // first_->next = nullptr;
    // current->next = first_;
    // first_ = current;
    // while (temp) {
    //   current = temp;
    //   temp = temp->next;
    //   current->next = first_;
    //   first_ = current;
    // }

    Node* current = first_;
    Node* temp = first_;
    Node* prev = nullptr;
    while (current) {
      current = current->next;
      temp->next = prev;
      prev = temp;
      temp = current;
    }
    first_ = prev;
  }

  void SetPrintDebug(bool flag) { print_debug_ = flag; }

  void Print() {
    using namespace std;
    Node* current = first_;

    if (IsEmpty()) {
      std::cout << "Empty" << '\n';
    } else

    {
      while (current) {
        if (print_debug_) {
          // cout << "[" << current << ", " << current->item << ", " <<
          // current->next << "]";

          // 주소를 짧은 정수로 출력 (앞 부분은 대부분 동일하기때문에 뒷부분만
          // 출력)
          cout << "[" << reinterpret_cast<uintptr_t>(current) % 100000 << ", "
               << current->item << ", "
               << reinterpret_cast<uintptr_t>(current->next) % 100000 << "]";
        } else {
          cout << current->item;
        }

        if (current->next) {
          cout << " -> ";
        } else {
          cout << " -> NULL";
        }
        current = current->next;
      }
      cout << '\n';
    }
  }

 protected:
  Node* first_ = nullptr;
  bool print_debug_ = true;
};