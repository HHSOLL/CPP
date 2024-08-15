#include <fstream>
#include <iostream>

int main(void) {
  std::ofstream ofile("pr.txt");
  for (int size = 1; size < 10000; size++) {
    int count = 0;
    int* arr = new int[size];

    int min_num = 1000;
    int min_index = 0;

    for (int i = 0; i < size - 1; i++) {
      for (int j = i + 1; j < size; j++) {
        count++;
        if (arr[j] < arr[min_index]) {
          min_index = j;
        }
      }
      std::swap(arr[i], arr[min_index]);
    }
    ofile << size << " , " << count << '\n';

    delete[] arr;
  }
  ofile.close();
  return 0;
}
