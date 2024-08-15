#include <iomanip>
#include <iostream>

bool CheckSorted(int* arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    if (arr[i] > arr[i + 1]) return false;
  }
  return true;
}

void Print(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << '\n';
}

void Print(int* arr, int size, int start, int gap) {
  for (int i = 0; i < size; i++) {
    if ((i - start) % gap == 0)
      std::cout << std::setw(3) << arr[i] << " ";
    else
      std::cout << "    ";
  }
  std::cout << '\n';
}

void InsertionSort(int arr[], int n) {
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i;

    for (; j > arr[j - 1] > key && j > 0; j--) {
      arr[j] = arr[j - 1];
    }
    arr[j] = key;
  }
}

void InsertionSort(int arr[], int n, int gap) {
  std::cout << "gap = " << gap << '\n';

  for (int i = gap; i < n; i += 1) {
    std::cout << "Before : ";
    Print(arr, n, i, gap);

    int key = arr[i];
    int j = i;
    for (; j >= gap && arr[j - gap] > key; j -= gap) arr[j] = arr[j - gap];
    arr[j] = key;

    std::cout << " After : ";
    Print(arr, n, i, gap);
  }
}

void ShellSort(int arr[], int n) {
  for (int gap = n / 2; gap > 0; gap /= 2) {
    std::cout << "        ";
    Print(arr, n);

    InsertionSort(arr, n, gap);
  }

  std::cout << "        ";
  Print(arr, n);
  std::cout << '\n';
}

int main(void) {
  int arr[] = {99, 83, 18, 66, 7, 54, 95, 86, 47, 69, 25, 28};
  int n = sizeof(arr) / sizeof(arr[0]);

  ShellSort(arr, n);
}