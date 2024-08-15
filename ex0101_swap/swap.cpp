#include <iostream>

void MySwap(int* a, int* b);
void MySwapRef(int& a, int& b);
bool CheckSorted(int a, int b);

int main(void) {
  // swap
  {
    //   int a = 2;
    //   int b = 3;

    //   std::cout << a << " " << b << '\n';

    //   //   int temp = a;
    //   //   a = b;
    //   //   b = temp;

    //   //   MySwap(&a, &b);
    //   MySwapRef(a, b);

    //   std::cout << a << " " << b << '\n';
  }

  // sort
  {
    int arr[2] = {0};
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        arr[0] = j;
        arr[1] = i;

        if (arr[0] > arr[1]) {
          //   std::swap(arr[0], arr[1]);
          MySwapRef(arr[0], arr[1]);
        }

        std::cout << std::boolalpha;
        std::cout << arr[0] << " " << arr[1];
        std::cout << " " << (CheckSorted(arr[0], arr[1])) << '\n';
      }
    }
  }

  return 0;
}

void MySwap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void MySwapRef(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

bool CheckSorted(int a, int b) {
  return (a <= b);
  //   if (a <= b)
  //     return true;
  //   else
  //     return false;
}
