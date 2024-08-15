#include <cassert>
#include <iomanip>
#include <iostream>

template <typename K, typename V>
class BinarySearchTree {
 public:
  struct Item {
    K key = K();
    V value = V();
  };
  struct Node {
    Item item;

    Node* left = nullptr;
    Node* right = nullptr;
  };

  void Preorder() {
    Preorder(root_);
    std::cout << '\n';
  }
  void Preorder(Node* node) {
    if (!node) return;

    std::cout << node->item.key << " ";
    Preorder(node->left);
    Preorder(node->right);
  }

  void Inorder() {
    Inorder(root_);
    std::cout << '\n';
  }
  void Inorder(Node* node) {
    if (!node) return;

    Inorder(node->left);
    std::cout << node->item.key << " ";
    Inorder(node->right);
  }

  Item* RecurGet(const K& key) { return RecurGet(root_, key); }
  Item* RecurGet(Node* node, const K& key) {
    if (!node) return nullptr;

    if (key < node->item.key) return RecurGet(node->left, key);

    if (key > node->item.key) return RecurGet(node->right, key);

    return &node->item;
  }

  Item* IterGet(const K& key) { return IterGet(root_, key); }
  Item* IterGet(Node* node, const K& key) {
    if (!node) return nullptr;

    Node* temp = node;
    while (temp) {
      if (key < temp->item.key)
        temp = temp->left;
      else if (key > temp->item.key)
        temp = temp->right;
      else
        break;
    }
    return &temp->item;
  }

  void Insert(const Item& item) {
    std::cout << "Insert " << item.key << item.value << '\n';
    root_ = Insert(root_, item);
  }
  Node* Insert(Node* node, const Item& item) {
    if (!node) return new Node{item, nullptr, nullptr};

    if (node->item.key > item.key)
      node->left = Insert(node->left, item);
    else if (node->item.key < item.key)
      node->right = Insert(node->right, item);
    else
      node->item = item;

    return node;
  }
  void IterInsert(const Item& item) {
    std::cout << "IterInsert " << item.key << item.value << '\n';
    root_ = IterInsert(root_, item);
  }
  Node* IterInsert(Node* node, const Item& item) {
    if (!node) return new Node{item, nullptr, nullptr};

    Node* temp = node;
    Node* prev = node;
    int check = -1;
    while (temp) {
      if (item.key > temp->item.key) {
        prev = temp;
        temp = temp->right;
        check = 0;
      } else if (item.key < temp->item.key) {
        prev = temp;
        temp = temp->left;
        check = 1;
      }
    }

    if (check == 0) {
      prev->right = new Node{item, nullptr, nullptr};
    } else if (check == 1) {
      prev->left = new Node{item, nullptr, nullptr};
    }
    return node;
  }

  Node* MinKeyLeft(Node* node) {
    assert(node);
    while (node->left) {
      node = node->left;
    }
    return node;
  }

  void Remove(const K& key) {
    std::cout << "Remove  " << key << '\n';
    root_ = Remove(root_, key);
  }
  Node* Remove(Node* node, const K& key) {
    if (!node) return nullptr;

    if (key < node->item.key)
      node->left = Remove(node->left, key);
    else if (key > node->item.key)
      node->right = Remove(node->right, key);
    else {
      if (!node->left) {
        Node* temp = node->right;
        delete node;
        return temp;
      } else if (!node->right) {
        Node* temp = node->left;
        delete node;
        return temp;
      }

      Node* temp = MinKeyLeft(node->right);
      node->item = temp->item;
      node->right = Remove(node->right, temp->item.key);
    }
    return node;
  }

  int Height() { return Height(root_); }
  int Height(Node* node) {
    if (!node) return 0;
    return 1 + std::max(Height(node->left), Height(node->right));
  }

  void Print2D();
  void PrintLevel(int n);
  void DisplayLevel(Node* p, int lv, int d);

 protected:
  Node* root_ = nullptr;
};

template <typename K, typename V>
void BinarySearchTree<K, V>::Print2D() {
  using namespace std;
  cout << "Height = " << Height() << endl;
  int i = 0;
  while (i < Height()) {
    PrintLevel(i);
    i++;
    cout << endl;
  }
  cout << endl;
}

template <typename K, typename V>
void BinarySearchTree<K, V>::PrintLevel(int n) {
  using namespace std;
  Node* temp = root_;
  int val = (int)pow(2.0, Height() - n + 1.0);
  cout << setw(val) << "";
  DisplayLevel(temp, n, val);
}

template <typename K, typename V>
void BinarySearchTree<K, V>::DisplayLevel(Node* p, int lv, int d) {
  using namespace std;
  int disp = 2 * d;
  if (lv == 0) {
    if (p == NULL) {
      cout << "   ";
      cout << setw(disp - 3) << "";
      return;
    } else {
      int result = ((p->item.key <= 1) ? 1 : (int)log10(p->item.key) + 1);
      cout << " " << p->item.key << p->item.value << " ";
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