#include <iomanip>
#include <iostream>

bool CheckSorted(int* arr, int size);
void Print(int* arr, int left, int right);
void Merge(int init[], int merged[], int left, int mid, int right);
void MergeSort(int arr[], int merged[], int left, int right);

int main(void) {
  int arr[] = {38, 27, 43, 3, 9, 82, 10};
  int n = sizeof(arr) / sizeof(int);

  int* merged = new int[n];

  Print(arr, 0, n - 1);
  std::cout << '\n';

  MergeSort(arr, merged, 0, n - 1);

  Print(merged, 0, n - 1);
  std::cout << '\n';

  delete[] merged;

  return 0;
}

bool CheckSorted(int* arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    if (arr[i] > arr[i + 1]) return false;
  }
  return true;
}

void Print(int* arr, int left, int right) {
  for (int i = left; i <= right; i++) {
    std::cout << std::setw(3) << arr[i] << " ";
  }
  std::cout << '\n';
}

void Merge(int init[], int merged[], int left, int mid, int right) {
  int i, j, k, l;
  i = left;
  j = mid + 1;
  k = left;

  std::cout << "left : ";
  Print(init, left, mid);
  std::cout << "right : ";
  Print(init, mid + 1, right);

  while (i <= mid && j <= right) {
    if (init[i] < init[j]) {
      merged[k++] = init[i++];
    } else {
      merged[k++] = init[j++];
    }
  }

  if (i > mid)
    for (int x = j; x <= right; x++) merged[k++] = init[x];
  else
    for (int x = i; x <= mid; x++) merged[k++] = init[x];

  for (l = left; l <= right; l++) {
    init[l] = merged[l];
  }

  std::cout << "merged : ";
  Print(init, left, right);
  std::cout << '\n';
}

void MergeSort(int arr[], int merged[], int left, int right) {
  int mid;
  if (left < right) {
    mid = (left + right) / 2;

    MergeSort(arr, merged, left, mid);
    MergeSort(arr, merged, mid + 1, right);

    Merge(arr, merged, left, mid, right);
  }
}
