#include "../shared/Deque.h"

#include <iostream>

int main() {
  // Double Ended Queue (덱)
  Deque<char> d(8);

  //   d.SetDebugFlag(true);

  //   d.PrintDebug();

  d.Print();

  d.PushFront('A');
  d.Print();
  //   d.PrintDebug();

  d.PushFront('B');
  d.Print();
  //   d.PrintDebug();

  d.PushBack('C');
  d.Print();
  //   d.PrintDebug();

  d.PushBack('D');
  d.Print();
  //   d.PrintDebug();

  d.PopFront();
  d.Print();
  //   d.PrintDebug();

  d.PopBack();
  d.Print();
  //   d.PrintDebug();

  return 0;
}