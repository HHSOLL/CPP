#include "MyString.h"

MyString::MyString() {
  str_ = nullptr;
  size_ = 0;
};

MyString::MyString(const char* init_str) {
  if (init_str == nullptr) {
    str_ = nullptr;
    size_ = 0;
  } else {
    size_ = 0;
    while (init_str[size_] != '\0') size_++;

    if (size_ > 0) {
      str_ = new char[size_];
      std::memcpy(str_, init_str, size_);
    }
  }
}

MyString::MyString(const MyString& str) {
  size_ = str.size_;
  str_ = new char[str.size_];
  std::memcpy(str_, str.str_, size_);
}

MyString::~MyString() {
  if (str_) {
    delete[] str_;
    str_ = nullptr;
    size_ = 0;
  }
}

int MyString::Length() { return size_; }

bool MyString::IsEmpty() { return size_ == 0; }

bool MyString::IsEqual(const MyString& str) {
  if (size_ != str.size_) return false;
  return std::memcmp(str_, str.str_, size_) == 0;
}

void MyString::Resize(int new_size) {
  char* new_str = new char[new_size];

  int copy_size = (new_size < size_) ? new_size : size_;

  std::memcpy(new_str, str_, copy_size);

  if (new_size > size_) {
    for (int i = size_ + 1; i < new_size; i++) {
      new_str[i] = '\0';
    }
  }
  delete[] str_;
  str_ = new_str;
  size_ = new_size;
}

MyString MyString::Insert(MyString t, int start) {
  assert(start >= 0);
  assert(start <= this->size_);

  MyString temp;
  temp.size_ = t.size_ + size_;
  temp.str_ = new char[temp.size_];

  std::memcpy(temp.str_, str_, start);
  std::memcpy(temp.str_ + start, t.str_, t.size_);
  std::memcpy(temp.str_ + start + t.size_, str_ + start, size_ - start);

  //   for (int i = start; i < start + t.size_; i++) {
  //     temp.str_[i] = t.str_[i];
  //   }
  //   int k = size_ - 1;
  //   for (int i = 0; i < temp.size_; i++) {
  //     if (temp.str_[i] == 0) {
  //       temp.str_[i] = str_[k - size_ + 1];
  //       k++;
  //     }
  //   }
  return temp;
}
MyString MyString::Concat(const MyString app_str) {
  MyString temp;
  temp.size_ = size_ + app_str.size_;
  temp.str_ = new char[temp.size_];

  std::memcpy(temp.str_, str_, size_);
  std::memcpy(temp.str_ + size_, app_str.str_, app_str.size_);

  return temp;
}

MyString MyString::Substr(int start, int num) {
  MyString temp;
  temp.size_ = num;
  temp.str_ = new char[temp.size_];

  std::memcpy(temp.str_, str_ + start, num);

  //   for (int i = 0; i < temp.size_; i++) {
  //     temp.str_[i] = str_[start];
  //     start++;
  //   }

  return temp;
}

int MyString::Find(MyString pat) {
  //   std::string s = str_;
  //   return s.find(pat.str_);
  for (int i = 0; i < this->size_; i++) {
    if (this->str_[i] == pat.str_[0]) {
      for (int j = 0; j < pat.size_; j++) {
        if (this->str_[i + j] != pat.str_[j]) break;

        if (j == pat.Length() - 1) return i;
      }
    }
  }
  return -1;
}

void MyString::Print() {
  for (int i = 0; i < size_; i++) {
    std::cout << str_[i];
  }
  std::cout << '\n';
}