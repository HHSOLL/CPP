#include <iostream>

struct Element {
  int key;
  char value;
};

void BubbleSort(int* arr, int size);
void PrintArr(int* arr, int size);

void E_BubbleSort(Element* arr, int size);
void E_PrintArr(Element* arr, int size);

int main(void) {
  //   {
  //     int arr[] = {5, 1, 4, 2, 3};
  //     int size = sizeof(arr) / sizeof(int);

  //     BubbleSort(arr, size);
  //   }

  {
    Element Earr[] = {{3, 'a'}, {2, 'a'}, {2, 'c'}, {3, 'c'}, {4, 'd'}};
    int size = sizeof(Earr) / sizeof(Earr[0]);
    E_BubbleSort(Earr, size);
  }

  // best case
  //   {
  //     int arr2[] = {1, 2, 3, 4, 5};
  //     int size = sizeof(arr2) / sizeof(int);

  //     for (int i = 0; i < size - 1; i++) {
  //       int count = 0;
  //       for (int j = 0; j < size - 1; j++) {
  //         if (arr2[i] > arr2[j]) {
  //           count++;
  //           std::swap(arr2[i], arr2[j]);
  //         }
  //       }
  //       if (count == 0) {
  //         PrintArr(arr2, size);
  //         break;
  //       }
  //     }
  //   }
  return 0;
}

void BubbleSort(int* arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = i + 1; j < size; j++) {
      if (arr[i] > arr[j]) {
        std::swap(arr[i], arr[j]);
      }
    }
    PrintArr(arr, size);
  }
}

void PrintArr(int* arr, int size) {
  for (int i = 0; i < size; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << '\n';
}

void E_BubbleSort(Element* arr, int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = i + 1; j < size; j++) {
      if (arr[i].key > arr[j].key) {
        std::swap(arr[i], arr[j]);
      }
    }
    E_PrintArr(arr, size);
  }
}

void E_PrintArr(Element* arr, int size) {
  for (int i = 0; i < size; i++) {
    std::cout << arr[i].key << " , " << arr[i].value << "\n";
  }
  std::cout << '\n';
}