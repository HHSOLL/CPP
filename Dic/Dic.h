#include <iostream>

class AVL {
 public:
  struct Word {
    std::string w;
    std::string m;
  };
  struct Node {
    Word word;
    Node* left = nullptr;
    Node* right = nullptr;
  };

  int height() { return height(root_); }
  int height(Node* node) {
    if (!node) return 0;
    return 1 + std::max(height(node->left), height(node->right));
  }

  int Balance(Node* node) {
    if (node)
      return height(node->left) - height(node->right);
    else
      return 0;
  }

  Node* RotateRight(Node* parent) {
    Node* cld = parent->left;
    parent->left = cld->right;
    cld->right = parent;
    return cld;
  }

  Node* RotateLeft(Node* parent) {
    Node* cld = parent->right;
    parent->right = cld->left;
    cld->left = parent;
    return cld;
  }

  void Insert(Word& word) { root_ = Insert(root_, word); }
  Node* Insert(Node* node, Word& word) {
    if (!node) return new Node{word, nullptr, nullptr};

    if (word.w < node->word.w) {
      node->left = Insert(node->left, word);
    } else if (word.w > node->word.w) {
      node->right = Insert(node->right, word);
    } else {
      node->word = word;
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

  void Remove(std::string& word) { root_ = Remove(root_, word); }
  Node* Remove(Node* node, std::string& word) {
    if (!node) return node;

    if (word < node->word.w) {
      node->left = Remove(node->left, word);
    } else if (word > node->word.w) {
      node->right = Remove(node->right, word);
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
      node->word = temp->word;
      node->right = Remove(node->right, temp->word.w);
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

  Node* search(Node* node, const std::string& word) const {
    if (!node || node->word.w == word) return node;

    if (word < node->word.w)
      return search(node->left, word);
    else
      return search(node->right, word);

    return nullptr;
  }

  void clear(Node* node) {}

 protected:
  Node* root_ = nullptr;
};

class Dictionary : public AVL {
 public:
  using Node = AVL::Node;
  using Word = AVL::Word;

  Dictionary() = default;
  ~Dictionary() = default;

  std::string search(const std::string& word) const {
    Node* node = AVL::search(AVL::root_, word);

    if (node) {
      return node->word.m;
    } else {
      return "No result";
    }
  }

  void Insert(const std::string& w, const std::string& m) {
    Word word{w, m};
    AVL::Insert(word);
  }
};