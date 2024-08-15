#include <iomanip>
#include <iostream>

int Fibonacci(int n);
int RecurFibonacci(int n);

int main(void) {
  std::cout << RecurFibonacci(10) << '\n';
  std::cout << Fibonacci(10) << '\n';
  return 0;
}

int Fibonacci(int n) {
  int a = 0;
  int b = 1;
  int c;
  for (int i = n; i > 1; i--) {
    c = a + b;
    a = b;
    b = c;
  }
  return c;
}

int RecurFibonacci(int n) {
  if (n == 0)
    return 0;
  else if (n == 1)
    return 1;
  else {
    return RecurFibonacci(n - 1) + RecurFibonacci(n - 2);
  }
}