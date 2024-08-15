#include <iostream>

template <typename T>
class ThreadedBinaryTree {
 public:
  struct Node {
    T item = T();
    Node* left = nullptr;
    Node* right = nullptr;
    int right_thread = 0;
  };

  ThreadedBinaryTree(Node* node) : root_(node) {}

  Node* Next(Node* node) {
    Node* next = node->right;

    if (!next || node->right_thread) return next;

    while (next->left) next = next->left;

    return next;
  }

  void Inorder() { Inorder(root_); }
  void Inorder(Node* node) {
    while (node->left) node = node->left;

    do {
      std::cout << node->item << " ";
      node = Next(node);
    } while (node);

    std::cout << '\n';
  }

 private:
  Node* root_ = nullptr;
};

int main() {
  using Node = ThreadedBinaryTree<int>::Node;

  Node* n1 = new Node{1, nullptr, nullptr};
  Node* n2 = new Node{2, n1, nullptr};
  Node* n3 = new Node{3, nullptr, nullptr};
  Node* n4 = new Node{4, nullptr, nullptr};
  Node* n5 = new Node{5, nullptr, n4};
  Node* n6 = new Node{6, n2, n5};
  n1->right = n3;

  n3->right = n2;
  n3->right_thread = 1;

  n2->right = n6;
  n2->right_thread = 1;

  ThreadedBinaryTree<int> tree(n6);

  tree.Inorder();  // 1 3 2 6 5 4

  return 0;
}