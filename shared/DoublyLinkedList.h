#include <stdint.h>

#include <algorithm>
#include <cassert>
#include <iostream>

template <typename T>
class DoublyLinkedList {
 public:
  struct Node {
    T item;

    Node* left = nullptr;
    Node* right = nullptr;
  };

  DoublyLinkedList() {}
  DoublyLinkedList(const DoublyLinkedList& list) {
    Node* temp = list.first_;
    while (temp) {
      this->PushBack(temp->item);
      temp = temp->right;
    }
  }
  ~DoublyLinkedList() { Clear(); }
  void Clear() {
    while (first_) {
      Node* temp = first_;
      first_ = first_->right;
      delete temp;
    }
  }

  bool IsEmpty() { return first_ == nullptr; }

  int Size() {
    int size = 0;
    Node* temp = first_;
    while (temp) {
      size++;
      temp = temp->right;
    }
    return size;
  }

  T Front() { return first_->item; }
  T Back() {
    Node* temp = first_;
    while (temp->right) temp = temp->right;
    return temp->item;
  }

  void InsertBack(Node* node, T item) {
    Node* new_node = new Node;
    new_node->item = item;

    node->right->left = new_node;
    new_node->right = node->right;

    node->right = new_node;
    new_node->left = node;
  }

  void PushFront(T item) {
    Node* new_node = new Node;
    new_node->item = item;
    if (first_ == nullptr)
      first_ = new_node;
    else {
      new_node->right = first_;
      first_->left = new_node;
      first_ = new_node;
    }
  }
  void PushBack(T item) {
    if (first_ == nullptr) {
      PushFront(item);
    } else {
      Node* temp = first_;
      while (temp->right) temp = temp->right;

      Node* new_node = new Node;
      new_node->item = item;
      temp->right = new_node;
      new_node->left = temp;
    }
  }

  void PopFront() {
    if (IsEmpty()) {
      std::cout << "emtpy" << '\n';
      return;
    }
    Node* temp = first_;
    first_ = first_->right;
    first_->left = nullptr;
    delete temp;
  }
  void PopBack() {
    if (IsEmpty()) {
      std::cout << "empty" << '\n';
      return;
    }
    Node* temp = first_;
    while (temp->right) temp = temp->right;
    Node* curr = temp->left;
    curr->right = nullptr;
    delete temp;
  }

  void Reverse() {
    while (true) {
      std::swap(first_->right, first_->left);
      if (first_->left == nullptr) break;
      first_ = first_->left;
    }
  }

  Node* Find(T item) {
    Node* temp = first_;
    while (temp) {
      if (temp->item == item) break;
      temp = temp->right;
    }
    return temp;
  }

  void Print() {
    if (IsEmpty()) {
      std::cout << "Empty" << '\n';
      return;
    }
    Node* temp = first_;
    std::cout << "size : " << Size() << '\n';

    std::cout << "Forward  : ";
    while (true) {
      std::cout << temp->item << " ";
      if (temp->right == nullptr) break;
      temp = temp->right;
    }
    std::cout << '\n';

    std::cout << "Backward : ";
    while (true) {
      std::cout << temp->item << " ";
      if (temp->left == nullptr) break;
      temp = temp->left;
    }
    std::cout << '\n';
  }

 protected:
  Node* first_ = nullptr;
};