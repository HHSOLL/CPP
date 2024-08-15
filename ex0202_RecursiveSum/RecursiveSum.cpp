#include <iostream>

int sum = 0;
int RecursiveSum(int* arr, int size);
int RecursiveSum2(int* arr, int size);

int main(void) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int size = sizeof(arr) / sizeof(arr[0]);

  std::cout << RecursiveSum2(arr, size) << '\n';

  return 0;
}

int RecursiveSum(int* arr, int size) {
  sum += arr[size - 1];
  if (size == 0) {
    return sum;
  } else {
    return RecursiveSum(arr, size - 1);
  }
  return 0;
}

int RecursiveSum2(int* arr, int size) {
  if (size == 0) {
    return 0;
  } else {
    return RecursiveSum2(arr, size - 1) + arr[size - 1];
  }
}