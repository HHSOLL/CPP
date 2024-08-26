#include <iostream>
using namespace std;

int rec_count = 0;

int InterpolationSearch(int* arr, int low, int high, int n) {
  rec_count++;

  if (low <= high && n >= arr[low] && n <= arr[high]) {
    int pos = int(
        low + float(((high - low) * (n - arr[low])) / (arr[high] - arr[low])));

    if (arr[pos] == n) return pos;

    if (arr[pos] > n) return InterpolationSearch(arr, pos + 1, high, n);

    if (arr[pos] < n) return InterpolationSearch(arr, low, pos - 1, n);
  }

  return -1;
}

int main() {
  int arr[] = {10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47};
  int n = sizeof(arr) / sizeof(arr[0]);

  for (auto x : {10, 18, 33, 47, -1, 99}) {
    rec_count = 0;

    int index = InterpolationSearch(arr, 0, n - 1, x);

    if (index != -1) {
      std::cout << x << "was fount at index" << index << '\n';
    } else {
      std::cout << x << "was not found" << '\n';
    }

    std::cout << "rec_count = " << rec_count << '\n';
    std::cout << '\n';
  }

  return 0;
}