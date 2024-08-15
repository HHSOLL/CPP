#include <iostream>

int RecurBinarySearch(int* arr, int size, int left, int right, int target);
int main(void) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int size = sizeof(arr) / sizeof(arr[0]);
  int left = 0;
  int right = size - 1;

  std::cout << RecurBinarySearch(arr, size, left, right, -2) << '\n';

  return 0;
}

int RecurBinarySearch(int* arr, int size, int left, int right, int target) {
  int middle = (left + right) / 2;

  if (left > right) {
    return -1;
  } else if (target == arr[middle]) {
    return middle;
  } else if (target > arr[middle]) {
    return RecurBinarySearch(arr, size, middle + 1, right, target);
  } else {
    return RecurBinarySearch(arr, size, left, middle - 1, target);
  }
  return 0;
}
