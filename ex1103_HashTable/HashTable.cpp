#include <iostream>
#include <string>

using namespace std;

template <typename K, typename V>
class HashTable {
 public:
  struct Item {
    K key = K();
    V value = V();
  };

  HashTable(const int& cap = 8) {
    capacity_ = cap;
    table_ = new Item[capacity_];
  }

  ~HashTable() { delete[] table_; }

  void Insert(const Item& item) {
    size_t index = HashFunc(item.key);

    if (table_[index].key != K()) cout << "collision!!" << '\n';

    // while (table_[index].key != K()) {
    //   index = (index + 1) % capacity_;
    // }
    // table_[index] = item;

    for (int i = 0; i < capacity_; i++) {
      index = (index + 1) % capacity_;
      if (table_[index].key == K()) {
        table_[index] = item;
        return;
      }
    }
    cout << "failed to Insert" << '\n';
  }

  V Get(const K& key) {
    size_t index = HashFunc(key);

    for (int i = 0; i < capacity_; i++) {
      index = (index + 1) % capacity_;
      if (table_[index].key == key) return table_[index].value;
    }

    return V();
  }

  size_t HashFunc(const int& key) { return key % capacity_; }

  size_t HashFunc(const string& str) {
    size_t index = 0;
    int g = 31;
    for (int i = 0; i < str.size(); i++) {
      index = g * index + int(str.at(i));
    }
    return index % capacity_;
  }

  void Print() {
    for (int i = 0; i < capacity_; i++)
      cout << i << " : " << table_[i].key << " " << table_[i].value << endl;
    cout << endl;
  }

 private:
  Item* table_ = nullptr;
  int capacity_ = 0;
};

int main(void) {
  //   using Item = HashTable<int, int>::Item;

  //   HashTable<int, int> h(8);

  //   h.Insert(Item{123, 456});

  //   h.Print();

  //   cout << "Get 123 " << h.Get(123) << endl;

  //   h.Insert(Item{1000021, 9898});

  //   h.Print();

  //   cout << "Get 1000021 " << h.Get(1000021) << endl;

  //   h.Insert(Item{1211, 999});  // 충돌!

  //   h.Print();

  //   cout << "Get 123 " << h.Get(123) << endl;
  //   cout << "Get 1211 " << h.Get(1211) << endl;

  {
    using Item = HashTable<string, int>::Item;

    HashTable<string, int> h(8);

    h.Insert(Item{"apple", 1});
    h.Insert(Item{"orange", 2});
    h.Insert(Item{"mandarin", 4});

    h.Print();

    cout << "apple " << h.Get("apple") << endl;
    cout << "orange " << h.Get("orange") << endl;
    cout << endl;

    h.Print();

    h.Insert(Item{"tomato", 4});

    h.Print();

    cout << "apple " << h.Get("apple") << endl;
    cout << "orange " << h.Get("orange") << endl;
    cout << "pineapple " << h.Get("pineapple") << endl;
    cout << endl;
  }
}