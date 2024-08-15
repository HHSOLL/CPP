#include <cassert>
#include <iostream>

bool CheckSorted(int* arr, int size);  // 정렬되었는지 확인할 함수
void PrintArr(int* arr, int size);     // 배열을 출력하는 함수

int main(void) {
  int arr[] = {8, 3, 2, 5, 1, 1, 2, 5, 8, 9};
  int size = sizeof(arr) / sizeof(int);
  assert(size > 0);  // 배열의 크기가 1보다 작으면 오류 발생하도록.

  int min_num = 1000;
  int min_index = 0;

  int index = 0;
  while (!CheckSorted(arr, size)) {  // 배열이 정렬될 때까지 반복
    for (int i = index; i < size; i++) {
      if (arr[i] <= min_num) {
        min_num = std::min(arr[i], min_num);
        min_index = i;
      }
    }
    std::swap(arr[index], arr[min_index]);  // 최솟값을 찾아 swap

    PrintArr(arr, size);  // 과정마다 출력하여 정렬되었는지 확인
    std::cout << std::boolalpha;
    std::cout << " -> " << CheckSorted(arr, size) << '\n';
    index++;
    min_num = arr[index];
  }

  return 0;
}

bool CheckSorted(int* arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    if (arr[i] > arr[i + 1]) return false;
  }
  return true;
}

void PrintArr(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << '\n';
}