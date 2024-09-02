#include <cassert>
#include <iostream>

#include "../shared/Queue.h"
#include "../shared/Stack.h"

template <typename T>
class AdjMatGraph {
 public:
  struct Vertex {
    T item = T();
  };

  AdjMatGraph(int max_vertices) {
    max_vertices_ = max_vertices;

    matrix_ = new int*[max_vertices_];
    for (int i = 0; i < max_vertices_; i++) {
      matrix_[i] = new int[max_vertices_];
      for (int j = 0; j < max_vertices_; j++) {
        matrix_[i][j] = 0;
      }
    }

    vertices_ = new Vertex[max_vertices_];

    n_ = 0;
  }

  ~AdjMatGraph() {
    delete[] vertices_;

    for (int i = 0; i < max_vertices_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    if (visited_) delete[] visited_;
  }

  void PrintMatrix() {
    if (!n_) {
      std::cout << "Empty" << '\n';
      return;
    }

    for (int i = 0; i < n_; i++) {
      for (int j = 0; j < n_; j++) {
        std::cout << matrix_[i][j] << " ";
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }

  void InsertVertex(T item) {
    vertices_[n_].item = item;
    n_++;
  }

  void InsertEdge(int u, int v) {
    assert(u < n_ && v < n_);

    matrix_[u][v] = 1;
  }

  int Capacity() { return max_vertices_; }

  void ResetVisited() {
    if (!visited_) visited_ = new bool[max_vertices_];

    for (int i = 0; i < max_vertices_; i++) {
      visited_[i] = false;
    }
  }

  void DFS() {
    ResetVisited();
    DFS(0);
    std::cout << '\n';
  }

  void DFS(int v) {
    visited_[v] = true;
    std::cout << vertices_[v].item << " ";
    for (int i = 0; i < n_; i++) {
      if (matrix_[v][i] && !visited_[i]) {
        DFS(i);
      }
    }
  }

  void InterDFS() {
    ResetVisited();
    Stack<int> s;
    s.Push(0);
    visited_[0] = true;

    while (!s.IsEmpty()) {
      int temp = s.Top();
      s.Pop();
      for (int i = n_ - 1; i >= 0; i--) {
        if (matrix_[temp][i] && !visited_[i]) {
          s.Push(i);
          visited_[i] = true;
        };
      }
      std::cout << temp << " Stack :";
      s.Print();
      continue;
    }
  }

  void BFS() {
    ResetVisited();
    Queue<int> q;
    q.Enqueue(0);
    visited_[0] = true;

    while (!q.IsEmpty()) {
      int temp = q.Front();
      q.Dequeue();
      for (int i = 0; i < n_; i++) {
        if (matrix_[temp][i] && !visited_[i]) {
          q.Enqueue(i);
          visited_[i] = true;
        }
      }
      std::cout << temp << " queue :";
      q.Print();
      continue;
    }
  }

 private:
  int** matrix_ = nullptr;
  Vertex* vertices_ = nullptr;
  int n_ = 0;             // size
  int max_vertices_ = 0;  // capacity

  bool* visited_ = nullptr;
};

int main(void) {
  // 정점(vertex), 간선(edge)

  AdjMatGraph<int> g(7);

  for (int i = 0; i < g.Capacity(); i++) g.InsertVertex(i);

  g.InsertEdge(0, 2);
  g.InsertEdge(2, 0);
  g.InsertEdge(0, 1);
  g.InsertEdge(1, 0);
  g.InsertEdge(1, 4);
  g.InsertEdge(4, 1);
  g.InsertEdge(1, 3);
  g.InsertEdge(3, 1);
  g.InsertEdge(2, 4);
  g.InsertEdge(4, 2);
  g.InsertEdge(3, 6);
  g.InsertEdge(6, 3);
  g.InsertEdge(4, 6);
  g.InsertEdge(6, 4);
  g.InsertEdge(5, 6);
  g.InsertEdge(6, 5);

  g.PrintMatrix();

  g.DFS();
  g.InterDFS();
  std::cout << '\n';
  g.BFS();
  return 0;
}