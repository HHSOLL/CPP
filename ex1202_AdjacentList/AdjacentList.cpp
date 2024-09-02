#include <cassert>
#include <iostream>

#include "../shared/Queue.h"
#include "../shared/Stack.h"

template <typename T>
class AdjListGraph {
 public:
  struct Vertex {
    T item = T();
  };

  struct Node {
    int vertex = -1;
    Node* next = nullptr;
  };

  AdjListGraph(int max_vertices) {
    max_vertices_ = max_vertices;
    vertices_ = new Vertex[max_vertices_];
    list_ = new Node*[max_vertices_];

    for (int i = 0; i < max_vertices_; i++) {
      list_[i] = nullptr;
    }
    n_ = 0;
  }

  ~AdjListGraph() {
    delete[] list_;
    delete[] vertices_;
    if (visited_) delete[] visited_;
  }

  void InsertVertex(T item) {
    vertices_[n_].item = item;
    n_++;
  }

  void InsertEdge(int u, int v) {
    assert(u < n_ && v < n_);

    Node* temp = new Node{v, list_[u]};
    list_[u] = temp;
  }

  int Capacity() { return max_vertices_; }

  void Print() {
    using namespace std;
    for (int v = 0; v < n_; v++) {
      cout << vertices_[v].item << " : ";

      Node* current = list_[v];
      while (current) {
        cout << vertices_[current->vertex].item << " ";
        current = current->next;
      }
      cout << endl;
    }

    cout << endl;
  }

  void DFS() {
    ResetVisited();
    DFS(0);
    std::cout << '\n';
  }

  void DFS(int v) {
    visited_[v] = true;
    std::cout << vertices_[v].item << " ";

    Node* current = list_[v];
    while (current) {
      int w = current->vertex;
      if (!visited_[w]) {
        DFS(w);
      }
      current = current->next;
    }
  }

  void IterDFS() {
    ResetVisited();

    Stack<int> s;
    s.Push(0);
    visited_[0] = true;

    while (!s.IsEmpty()) {
      int temp = s.Top();
      s.Pop();

      Node* curr = list_[temp];
      while (curr) {
        int w = curr->vertex;
        if (!visited_[w]) {
          s.Push(w);
          visited_[w] = true;
        }
        curr = curr->next;
      }
      std::cout << vertices_[temp].item << " ";
      std::cout << "Stack :";
      s.Print();
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
      Node* curr = list_[temp];
      while (curr) {
        int w = curr->vertex;
        if (!visited_[w]) {
          visited_[w] = true;
          q.Enqueue(w);
        }
        curr = curr->next;
      }
      std::cout << vertices_[temp].item << " Queue :";
      q.Print();
      std::cout << '\n';
    }
  }

  void ResetVisited() {
    if (!visited_) visited_ = new bool[max_vertices_];
    for (int i = 0; i < max_vertices_; i++) visited_[i] = false;  // 초기화
  }

 private:
  Vertex* vertices_ = nullptr;
  Node** list_ = nullptr;
  int n_ = 0;
  int max_vertices_ = 0;

  bool* visited_ = nullptr;
};
int main(void) {
  AdjListGraph<int> g(7);

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

  g.Print();

  g.DFS();
  std::cout << '\n';

  g.IterDFS();

  g.BFS();
  return 0;
}