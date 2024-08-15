#include <algorithm>
#include <cassert>
#include <iostream>

struct Element {
  int key;
  char value;
};

bool CheckSorted(Element* arr, int size);
void PrintArr(Element* arr, int size);

int main(void) {
  Element arr[] = {{2, 'a'}, {2, 'b'}, {1, 'c'}};
  int size = sizeof(arr) / sizeof(arr[0]);
  PrintArr(arr, size);

  int min_index;
  for (int i = 0; i < size - 1; i++) {
    min_index = i;
    for (int j = i + 1; j < size; j++) {
      if (arr[j].key < arr[min_index].key) {
        min_index = j;
      }
    }
    std::swap(arr[i], arr[min_index]);
    PrintArr(arr, size);
  }

  return 0;
}

bool CheckSorted(Element* arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    if (arr[i].key > arr[i + 1].key) return false;
  }
  return true;
}

void PrintArr(Element* arr, int size) {
  for (int i = 0; i < size; i++) {
    std::cout << "{" << arr[i].key << ", " << arr[i].value << "} ";
  }
  std::cout << '\n';
}