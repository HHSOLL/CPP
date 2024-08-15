#include <fstream>
#include <iostream>
#include <string>

#include "Queue.h"
#include "Stack.h"

template <typename T>
class BinaryTree {
 public:
  struct Node {
    T item;
    Node* left = nullptr;
    Node* right = nullptr;
  };

  class MyQueue : public Queue<Node*> {
   public:
    void Print() {
      using namespace std;

      for (int i = (this->front_ + 1) % this->capacity_;
           i != (this->rear_ + 1) % this->capacity_;
           i = (i + 1) % this->capacity_)
        cout << this->queue_[i]->item << " ";
      cout << endl;
    }
  };

  class MyStack : public Stack<Node*> {
   public:
    void Print() {
      using namespace std;

      for (int i = 0; i < this->Size(); i++)
        cout << this->stack_[i]->item << " ";
      cout << endl;
    }
  };

  BinaryTree() {}
  BinaryTree(Node* root) : root_(root) {}
  ~BinaryTree() { DeleteTree(root_); }
  void DeleteTree(Node* node) {
    if (!node) return;
    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
  }

  bool IsEmpty() { return root_ == nullptr; }

  void Visit(Node* node) { std::cout << node->item << " "; }

  int Sum() { return Sum(root_); }
  int Sum(Node* root) {
    // if (root->left == nullptr && root->right == nullptr) {
    //   return root->item;
    // } else if (root->left == nullptr && root->right != nullptr) {
    //   return root->item + Sum(root->right);
    // } else if (root->left != nullptr && root->right == nullptr) {
    //   return root->item + Sum(root->left);
    // } else {
    //   return root->item + Sum(root->left) + Sum(root->right);
    // }
    // return 0;
    if (!root) return 0;
    return root->item + Sum(root->left) + Sum(root->right);
  }

  int Height() { return Height(root_); }
  int Height(Node* root) {
    // if (root->left == nullptr && root->right == nullptr) {
    //   return 1;
    // } else if (root->left == nullptr && root->right != nullptr) {
    //   return 1 + Height(root->right);
    // } else if (root->left != nullptr && root->right == nullptr) {
    //   return 1 + Height(root->left);
    // } else {
    //   return (1 + Height(root->left)) >= (1 + Height(root->right))
    //              ? (1 + Height(root->left))
    //              : (1 + Height(root->right));
    // }
    if (!root) return 0;
    return 1 + Height(root->left) >= 1 + Height(root->right)
               ? 1 + Height(root->left)
               : 1 + Height(root->right);
  }

  void Preorder() { Preorder(root_); }
  void Preorder(Node* node) {
    // if (!node) return;
    // if (node->left == nullptr && !node->right) {
    //   std::cout << node->item << " ";
    // } else if (node->left != nullptr && node->right == nullptr) {
    //   std::cout << node->item << " ";
    //   Preorder(node->left);
    // } else if (node->left == nullptr && node->right != nullptr) {
    //   std::cout << node->item << " ";
    //   Preorder(node->right);
    // } else {
    //   std::cout << node->item << " ";
    //   Preorder(node->left);
    //   Preorder(node->right);
    // }
    if (!node) return;
    Visit(node);
    Preorder(node->left);
    Preorder(node->right);
  }

  void Inorder() { Inorder(root_); }
  void Inorder(Node* node) {
    if (!node) return;
    Inorder(node->left);
    Visit(node);
    Inorder(node->right);
  }

  void Postorder() { Postorder(root_); }
  void Postorder(Node* node) {
    if (!node) return;
    Postorder(node->left);
    Postorder(node->right);
    Visit(node);
  }

  void LevelOrder() {
    if (!root_) return;
    Queue<Node*> q;
    Node* current = root_;
    while (current) {
      Visit(current);
      //   if (current->left == nullptr && current->right == nullptr)
      //     break;
      //   else if (current->left == nullptr && current->right != nullptr)
      //     q.Enqueue(current->right);
      //   else if (current->left != nullptr && current->right == nullptr)
      //     q.Enqueue(current->left);
      //   else {
      //     q.Enqueue(current->left);
      //     q.Enqueue(current->right);
      //   }
      if (current->left) q.Enqueue(current->left);
      if (current->right) q.Enqueue(current->right);
      if (q.IsEmpty()) return;
      current = q.Front();
      q.Dequeue();
    }
    std::cout << q.Front()->item;
  }

  void IterPreorder() {
    if (!root_) return;

    Stack<Node*> s;
    s.Push(root_);
    Node* curr = root_;
    while (!s.IsEmpty()) {
      Visit(curr);
      s.Pop();
      if (curr->right) s.Push(curr->right);
      if (curr->left) s.Push(curr->left);
      if (s.IsEmpty()) return;
      curr = s.Top();
    }
  }

  void IterInorder() {
    if (!root_) return;

    Stack<Node*> s;
    Node* curr = root_;
    while (curr || !s.IsEmpty()) {
      while (curr) {
        s.Push(curr);
        curr = curr->left;
      }
      curr = s.Top();
      Visit(curr);
      s.Pop();
      curr = curr->right;
    }
  }

  void IterPostorder() {
    using namespace std;
    if (!root_) return;

    Stack<Node*> s1;
    Stack<Node*> s2;

    Node* prev = nullptr;
    Node* curr = nullptr;
    s1.Push(root_);
    // while (!s1.IsEmpty()) {
    //   curr = s1.Top();

    //   if (!prev || prev->left == curr || prev->right == curr) {
    //     if (curr->left) {
    //       s1.Push(curr->left);
    //     } else if (curr->right) {
    //       s1.Push(curr->right);
    //     } else {
    //       Visit(curr);
    //       s1.Pop();
    //     }
    //   } else if (curr->left == prev) {
    //     if (curr->right)
    //       s1.Push(curr->right);
    //     else {
    //       Visit(curr);
    //       s1.Pop();
    //     }
    //   } else if (curr->right == prev) {
    //     Visit(curr);
    //     s1.Pop();
    //   }
    //   prev = curr;
    // }
    while (!s1.IsEmpty()) {
      Node* node = s1.Top();
      s1.Pop();
      s2.Push(node);

      if (node->left) s1.Push(node->left);
      if (node->right) s1.Push(node->right);
    }
    while (!s2.IsEmpty()) {
      Node* node = s2.Top();
      s2.Pop();
      Visit(node);
    }
  }
  void Print2D();
  void PrintLevel(int n);
  void DisplayLevel(Node* p, int lv, int d);

 protected:
  Node* root_ = nullptr;
};

template <typename T>
void BinaryTree<T>::Print2D() {
  using namespace std;
  int i = 0;
  while (i < Height()) {
    PrintLevel(i);
    i++;
    cout << endl;
  }
}

template <typename T>
void BinaryTree<T>::PrintLevel(int n) {
  using namespace std;
  Node* temp = root_;
  int val = (int)pow(2.0, Height() - n + 1.0);
  cout << setw(val) << "";
  DisplayLevel(temp, n, val);
}

template <typename T>
void BinaryTree<T>::DisplayLevel(Node* p, int lv, int d) {
  using namespace std;
  int disp = 2 * d;
  if (lv == 0) {
    if (p == NULL) {
      cout << "   ";
      cout << setw(disp - 3) << "";
      return;
    } else {
      int result = ((p->item <= 1) ? 1 : (int)log10(p->item) + 1);
      cout << " " << p->item << " ";
      cout << setw(static_cast<streamsize>(disp) - result - 2) << "";
    }
  } else {
    if (p == NULL && lv >= 1) {
      DisplayLevel(NULL, lv - 1, d);
      DisplayLevel(NULL, lv - 1, d);
    } else {
      DisplayLevel(p->left, lv - 1, d);
      DisplayLevel(p->right, lv - 1, d);
    }
  }
}