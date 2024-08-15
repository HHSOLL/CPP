#include "BinarySearchTree.h"

template <typename K, typename V>
class AVL : public BinarySearchTree<K, V> {
 public:
  using Base = BinarySearchTree<K, V>;
  using typename BinarySearchTree<K, V>::Item;
  using typename BinarySearchTree<K, V>::Node;

  int Height(Node* node) { return Base::Height(node); }

  int Balance(Node* node) {
    if (node)
      return Base::Height(node->left) - Base::Height(node->right);
    else
      return 0;
  }

  Node* RotateRight(Node* parent) {
    Node* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
  }

  Node* RotateLeft(Node* parent) {
    Node* temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
  }

  void Insert(const Item& item) { root_ = Insert(root_, item); }
  Node* Insert(Node* node, const Item& item) {
    if (!node) return new Node{item, nullptr, nullptr};

    const auto& key = item.key;

    if (key < node->item.key)
      node->left = Insert(node->left, item);
    else if (key > node->item.key)
      node->right = Insert(node->right, item);
    else {
      node->item = item;
      return node;
    }

    int balance = Balance(node);

    if (balance == 0 || balance == 1 || balance == -1) return node;

    if (balance > 1 && Balance(node->left) >= 0) {
      return RotateRight(node);
    } else if (balance < -1 && Balance(node->right) <= 0) {
      return RotateLeft(node);
    } else if (balance > 1 && Balance(node->left) <= -1) {
      node->left = RotateLeft(node->left);
      return RotateRight(node);
    } else if (balance < -1 && Balance(node->right) >= 1) {
      node->right = RotateRight(node->right);
      return RotateLeft(node);
    }

    return node;
  }

  Node* MinKeyNode(Node* node) {
    while (node->left) node = node->left;
    return node;
  }

  void Remove(const K& key) { root_ = Remove(root_, key); }
  Node* Remove(Node* node, const K& key) {
    if (!node) return node;

    if (key < node->item.key) {
      node->left = Remove(node->left, key);
    } else if (key > node->item.key) {
      node->right = Remove(node->right, key);
    } else {
      if (!node->right) {
        Node* temp = node->left;
        delete node;
        return temp;
      } else if (!node->left) {
        Node* temp = node->right;
        delete node;
        return temp;
      }

      Node* temp = MinKeyNode(node->right);
      node->item = temp->item;
      node->right = Remove(node->right, temp->item.key);
    }

    int balance = Balance(node);
    if (balance == 0 || balance == 1 || balance == -1) return node;

    if (balance > 1 && Balance(node->left) >= 0)
      return RotateRight(node);
    else if (balance > -1 && Balance(node->right) <= 0)
      return RotateLeft(node);
    else if (balance > 1 && Balance(node->left) <= -1) {
      node->left = RotateLeft(node->left);
      return RotateRight(node);
    } else if (balance < -1 && Balance(node->right) >= 1) {
      node->right = RotateLeft(node->right);
      return RotateRight(node);
    }

    return node;
  }

 private:
  Node*& root_ = BinarySearchTree<K, V>::root_;
};