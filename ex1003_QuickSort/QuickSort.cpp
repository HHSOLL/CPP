#include <math.h>

#include <iomanip>
#include <iostream>

bool CheckSorted(int* arr, int size) {
  for (int i = 0; i < size - 1; i++)
    if (arr[i] > arr[i + 1]) return false;

  return true;
}

void Print(int* arr, int low, int high, int n) {
  for (int i = 0; i < n; i++) {
    if (i >= low && i <= high)
      std::cout << std::setw(3) << arr[i] << " ";
    else
      std::cout << "    ";
  }
  std::cout << '\n';
}

int Partition(int* arr, int low, int high, int n) {
  int pivot = arr[size_t(floorf((high - low) / 2.0f)) + low];
  int i = low;
  int j = high;

  std::cout << "pivot=" << pivot << std::endl;
  std::cout << "         ";
  Print(arr, low, high, n);

  while (true) {
    while (arr[i] < pivot) i++;
    while (arr[j] > pivot) j--;

    if (i >= j) return j;

    std::swap(arr[i], arr[j]);

    std::cout << "i=" << i << ", j=" << j << std::endl;
    std::cout << "         ";
    Print(arr, low, high, n);
  }
}

void QuickSort(int* arr, int low, int high, int n) {
  if (low >= 0 && high >= 0 && low < high) {
    int p = Partition(arr, low, high, n);

    QuickSort(arr, low, p, n);
    QuickSort(arr, p + 1, high, n);
  }
}

int main(void) {
  int arr[] = {4, 17, 2, 9, 7, 5, 8, 1, 14, 6};
  int n = sizeof(arr) / sizeof(int);

  std::cout << "       ";
  Print(arr, 0, n - 1, n);
  std::cout << '\n';

  QuickSort(arr, 0, n - 1, n);

  std::cout << "       ";
  Print(arr, 0, n - 1, n);
  std::cout << '\n';
}