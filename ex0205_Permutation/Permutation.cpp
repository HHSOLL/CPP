#include <algorithm>
#include <cassert>
#include <iostream>

void RecurPermutations(char* arr, int left, int right);

int main(void) {
  char arr[] = "abcd";

  RecurPermutations(arr, 0, 0);
  std::cout << '\n';
  RecurPermutations(arr, 0, 1);
  std::cout << '\n';
  RecurPermutations(arr, 0, 2);
  std::cout << '\n';
  RecurPermutations(arr, 0, 3);
  std::cout << '\n';

  return 0;
}

void RecurPermutations(char* arr, int left, int right) {
  if (left == right) {
    for (int i = 0; i <= right; i++) std::cout << arr[i] << " ";
    std::cout << '\n';
  } else {
    int i;
    for (i = left; i <= right; i++) {
      std::swap(arr[left], arr[i]);
      RecurPermutations(arr, left + 1, right);
      std::swap(arr[left], arr[i]);
    }
  }
}
