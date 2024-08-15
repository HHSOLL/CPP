#include <iostream>

#include "../shared/Stack.h"

constexpr int kNumRows = 10;
constexpr int kNumCols = 9;

struct Pos {
  int row;
  int col;

  friend std::ostream& operator<<(std::ostream& os, const Pos& pos) {
    std::cout << "(" << pos.row << " , " << pos.col << ")" << std::flush;
    return os;
  }
};

char maze[kNumRows][kNumCols] = {
    {'1', '1', '1', '1', '1', '1', '1', '1', '1'},
    {'1', 'S', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '0', '1', '0', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '0', '1', '1', '1', '1', '1', '1', '1'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '1'},
    {'1', '1', '1', '1', '1', '0', '1', '1', '1'},
    {'1', '1', '1', '0', '0', '0', '1', '0', '1'},
    {'1', '0', '0', '0', '0', '0', '0', 'G', '1'},  // <- 'G'를 만나면 종료
    {'1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

void PrintMaze() {
  for (int i = 0; i < kNumRows; i++) {
    for (int j = 0; j < kNumCols; j++) {
      std::cout << maze[i][j] << " ";
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

// bool RecurMaze(Pos p) {
//   if (p.row < 0 || p.row >= kNumRows || p.col < 0 || p.col >= kNumCols)
//     return false;

//   const char mark = maze[p.row][p.col];

//   if (mark == 'G') {
//     std::cout << "Found" << '\n';
//     return true;
//   }

//   if (mark != '0' && mark != 'S') return false;

//   maze[p.row][p.col] = 'x';

//   PrintMaze();

//   int DRow[] = {1, -1, 0, 0};
//   int DCol[] = {0, 0, -1, 1};

//   for (int i = 0; i < 4; ++i) {
//     int New_Row = p.row + DRow[i];
//     int New_Col = p.col + DCol[i];
//     if (RecurMaze({New_Row, New_Col})) return true;
//   }

//   maze[p.row][p.col] = maze[p.row][p.col] == 'S' ? 'S' : '0';
//   return false;
// }

void StackMaze() {
  Stack<Pos> s;

  Pos start = {1, 1};

  s.Push(start);

  while (!s.IsEmpty()) {
    Pos p = s.Top();
    s.Pop();

    if (p.row < 0 || p.row >= kNumRows || p.col < 0 || p.col >= kNumCols)
      continue;

    std::cout << p << '\n';

    const char mark = maze[p.row][p.col];

    if (mark == 'G') {
      std::cout << "Found" << '\n';
      break;
    }

    if (mark != '0' && mark != 'S') {
      // s.Pop();
      // maze[p.row][p.col] = '0';
      continue;
    }
    maze[p.row][p.col] = 'x';

    s.Push({p.row - 1, p.col});
    s.Push({p.row, p.col - 1});
    s.Push({p.row + 1, p.col});
    s.Push({p.row, p.col + 1});
  }
}

int main(void) {
  PrintMaze();

  StackMaze();

  // RecurMaze({1, 1});

  PrintMaze();

  return 0;
}