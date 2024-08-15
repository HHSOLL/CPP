#include <iostream>

#include "../shared/Queue.h"

using namespace std;

int main() {
  int n, k;
  std::cout << "n , k : ";
  std::cin >> n >> k;

  Queue<int> q(n + 1);

  for (int i = 1; i <= n; i++) {
    q.Enqueue(i);
  }
  q.Print();

  while (q.Size() != 1) {
    for (int i = 0; i < k - 1; i++) {
      int temp = q.Front();
      q.Dequeue();
      q.Enqueue(temp);
    }
    q.Dequeue();
  }
  std::cout << "survivor : " << q.Front() << '\n';

  return 0;
}