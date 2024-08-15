#include <algorithm>
#include <cassert>
#include <iostream>

class MyString {
 public:
  MyString();
  MyString(const char* init_str);
  MyString(const MyString& str);
  ~MyString();

  int Length();
  bool IsEmpty();

  bool IsEqual(const MyString& str);
  void Resize(int new_size);

  MyString Substr(int start, int num);
  MyString Concat(MyString app_str);
  MyString Insert(MyString t, int start);

  int Find(MyString pat);

  void Print();

 private:
  char* str_ = nullptr;
  int size_ = 0;
};