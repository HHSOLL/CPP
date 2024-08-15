#include <iostream>

#include "../shared/Stack.h"

Stack<char> tower[3];

int count = 0;

void PrintTower() {
  using namespace std;
  cout << "TOWERS" << '\n';
  cout << "0 : ";
  tower[0].Print();
  cout << "1 : ";
  tower[1].Print();
  cout << "2 : ";
  tower[2].Print();
}

void MoveDisk(int from, int to) {
  if (tower[from].IsEmpty()) {
    std::cout << "ERROR : TOWER IS EMPTY" << '\n';
    // return;
    exit(0);
  }

  auto disk = tower[from].Top();

  if (!tower[to].IsEmpty() && tower[to].Top() > disk) {
    std::cout << "ERROE : DISK IS TOO BIG" << '\n';
    exit(0);
  }

  tower[from].Pop();
  tower[to].Push(disk);
  count++;

  std::cout << "Move Disk From  " << from << "  to  " << to << '\n';
  PrintTower();
}

void RecurMoveDisk(int num_disks, int from, int temp, int to) {
  if (num_disks == 0) return;

  RecurMoveDisk(num_disks - 1, from, to, temp);
  MoveDisk(from, to);
  RecurMoveDisk(num_disks - 1, temp, from, to);
}

int main(void) {
  int num_disks;
  std::cout << "NUM_OF_DISKS : ";
  std::cin >> num_disks;

  for (int i = 0; i < num_disks; i++) {
    tower[0].Push('A' + i);
  }

  PrintTower();

  RecurMoveDisk(num_disks, 0, 1, 2);

  std::cout << "count : " << count << '\n';

  return 0;
}