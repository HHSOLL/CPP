#include <cassert>
#include <iomanip>
#include <iostream>

void BinarySearch(int* arr, int size, int num);
void PrintHelper(int* arr, int size, int right, int left);

int main(void) {
  int arr[] = {1, 2, 3, 4, 5, 11, 22, 44, 55, 66};
  int size = sizeof(arr) / sizeof(arr[0]);
  BinarySearch(arr, size, -2);
  return 0;
}

void BinarySearch(int* arr, int size, int num) {
  int left = 0;
  int right = size - 1;
  int middle;

  while (left <= right) {
    PrintHelper(arr, size, right, left);

    middle = (right + left) / 2;
    std::cout << "middle : " << middle << '\n';

    if (arr[middle] == num) {
      std::cout << "find " << num << '\n' << "index : " << middle << '\n';
      break;
    } else if (num > arr[middle]) {
      left = middle + 1;
      continue;
    } else {
      right = middle - 1;
      continue;
    }
  }
  if (left > right) std::cout << "cannot found " << num << '\n';
}

void PrintHelper(int* arr, int size, int right, int left) {
  std::cout << "[ " << left << " , " << right << " ]" << '\n';
  for (int i = 0; i < size; i++) {
    std::cout << std::setw(2) << i << " ";
  }
  std::cout << '\n';
  for (int i = 0; i < size; i++) {
    std::cout << std::setw(2) << arr[i] << " ";
  }
  std::cout << '\n';
}