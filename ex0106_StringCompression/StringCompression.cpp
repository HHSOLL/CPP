#include <iostream>

void InsertionSort(char* arr, int size);
void Print(char* arr, int size);

int main(void) {
  char arr[] = "asdifojsadklnfsdaklg";
  int table[26] = {0};
  int size = sizeof(arr) - 1;

  {  // table 을 이용한 문자열압축
    for (int i = 0; i < size; i++) {
      table[arr[i] - 97]++;
    }
    std::cout << "using table" << '\n';
    for (int i = 0; i < 26; i++) {
      if (table[i] != 0) std::cout << char(i + 97) << " : " << table[i] << '\n';
    }
  }

  {  // table 없이 문자열 압축
    std::cout << "not using table" << '\n';
    InsertionSort(arr, size);
    // Print(arr, size);
    int count = 0;
    for (int i = 0; i < size; i++) {
      count++;
      if (arr[i] != arr[i + 1]) {
        std::cout << arr[i] << " : " << count << '\n';
        count = 0;
      }
    }
  }
  return 0;
}

void InsertionSort(char* arr, int size) {
  for (int i = 1; i < size; i++) {
    int j = i;
    int key = arr[i];

    for (; j > 0 && arr[j - 1] > key; j--) {
      arr[j] = arr[j - 1];
    }
    arr[j] = key;
  }
}
void Print(char* arr, int size) {
  for (int i = 0; i < size; i++) {
    std::cout << arr[i];
  }
  std::cout << '\n';
}