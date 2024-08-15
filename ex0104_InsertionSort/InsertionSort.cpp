#include <iostream>
void InsertionSort(int* arr, int size);
void Print(int* arr, int size);

int main(void) {
  int arr[] = {8, 1, 1, 3, 2, 5, 1, 2, 1, 1};
  int size = sizeof(arr) / sizeof(arr[0]);

  InsertionSort(arr, size);

  return 0;
}

void InsertionSort(int* arr, int size) {
  for (int i = 1; i < size; i++) {
    int key = arr[i];
    int j = i;

    for (; j > 0 && arr[j - 1] > key; j--) {
      arr[j] = arr[j - 1];
    }
    arr[j] = key;
  }
  Print(arr, size);
}

void Print(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << '\n';
}
