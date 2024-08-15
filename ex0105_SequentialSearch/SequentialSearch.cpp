#include <iostream>

int Count(int* arr, int size, int n);
int SequentialSearch(int* arr, int size, int n);
int SortedCount(int* arr, int size, int n);
int SortedCountHelper(int* arr, int size, int n, int start);
void Print(int* arr, int size);
void InsertionSort(int* arr, int size);

int main(void) {
  int arr[] = {8, 1, 1, 3, 2, 5, 1, 2, 1, 1};
  int size = sizeof(arr) / sizeof(arr[0]);

  std::cout << "Count 9 = " << Count(arr, size, 9) << '\n';
  std::cout << "Count 2 = " << Count(arr, size, 2) << '\n';
  std::cout << "Count 8 = " << Count(arr, size, 8) << '\n';
  std::cout << "Count 1 = " << Count(arr, size, 1) << '\n';
  std::cout << '\n';

  std::cout << "Search 2 = " << SequentialSearch(arr, size, 2) << '\n';
  std::cout << "Search 5 = " << SequentialSearch(arr, size, 5) << '\n';
  std::cout << "Search 9 = " << SequentialSearch(arr, size, 9) << '\n';

  InsertionSort(arr, size);

  Print(arr, size);

  std::cout << "Sorted Count 9 = " << SortedCount(arr, size, 9) << '\n';
  std::cout << "Sorted Count 2 = " << SortedCount(arr, size, 2) << '\n';
  std::cout << "Sorted Count 8 = " << SortedCount(arr, size, 8) << '\n';
  std::cout << "Sorted Count 1 = " << SortedCount(arr, size, 1) << '\n';
  std::cout << '\n';

  return 0;
}

int Count(int* arr, int size, int n) {
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] == n) count++;
  }
  return count;
}

// int SequentialSearch(int* arr, int size, int n) {
//   int index = -1;
//   for (int i = 0; i < size; i++) {
//     if (arr[i] == n) {
//       index = i;
//       break;
//     }
//   }
//   return index;
// }

int SequentialSearch(int* arr, int size, int n) {
  int i;
  for (i = 0; i < size && arr[i] != n; i++) { /*do nothing*/
  };
  if (i == n)
    return -1;
  else
    return i;
}

int SortedCount(int* arr, int size, int n) {
  int i = SequentialSearch(arr, size, n);

  if (i >= 0)
    return SortedCountHelper(arr, size, n, i + 1) + 1;
  else
    return 0;
}

int SortedCountHelper(int* arr, int size, int n, int start) {
  int count = 0;
  for (int i = start; i < size; i++) {
    if (arr[i] == n)
      count++;
    else  // 정렬되어있기에 조기종료 가능
      break;
  }
  return count;
}

void Print(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    std::cout << arr[i] << "  ";
  }
  std::cout << '\n';
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
}