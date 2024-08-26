#include <iostream>

#include "../shared/Queue.h"

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

int GetMax(int* arr, int size) {
  int max = arr[0];
  for (int i = 1; i < size; i++) {
    if (arr[i] > max) max = arr[i];
  }
  return max;
}

int main(void) {
  int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
  int size = sizeof(arr) / sizeof(arr[0]);

  Print(arr, size);

  Queue<int> queues[10];

  int m = GetMax(arr, size);

  for (int exp = 1; m / exp > 0; exp *= 10) {
    for (int i = 0; i < size; i++) {
      queues[arr[i] / exp % 10].Enqueue(arr[i]);
    }

    int count = 0;
    for (int i = 0; i < 10; i++) {
      while (!queues[i].IsEmpty()) {
        arr[count] = queues[i].Front();
        queues[i].Dequeue();
        count++;
      }
    }
    Print(arr, size);
  }

  return 0;
}