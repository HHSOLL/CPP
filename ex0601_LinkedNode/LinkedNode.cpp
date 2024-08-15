#include <iostream>
using namespace std;

struct Node {
  int item = 0;
  Node* next = nullptr;

  friend std::ostream& operator<<(std::ostream& os, const Node& n) {
    std::cout << '[' << &n << " , " << n.item << "  ,   " << n.next
              << std::flush;
    return os;
  }
};

void RecurPrint(Node* node) {
  std::cout << node->item << '\n';
  if (node->next == nullptr) return;
  RecurPrint(node->next);
}

void IterPrint(Node* node) {
  while (1) {
    std::cout << node->item << '\n';

    if (node->next == nullptr) break;
    node = node->next;
  }
}

int main(void) {
  Node* first = nullptr;
  first = new Node;
  first->item = 1;
  first->next = nullptr;

  Node* second = nullptr;
  second = new Node;
  second->item = 2;
  second->next = nullptr;

  Node* third = nullptr;
  third = new Node;
  third->item = 3;
  third->next = nullptr;

  Node* fourth = nullptr;
  fourth = new Node;
  fourth->item = 4;
  fourth->next = nullptr;

  Node* fifth = nullptr;
  fifth = new Node;
  fifth->item = 5;
  fifth->next = nullptr;

  cout << *first << endl;
  cout << *second << endl;
  cout << *third << endl;
  cout << *fourth << endl;
  cout << *fifth << endl;
  cout << endl;

  first->next = second;
  second->next = third;
  third->next = fourth;
  fourth->next = fifth;

  cout << *first << '\n';
  cout << *(first->next) << '\n';
  cout << *(first->next->next) << '\n';
  cout << *(first->next->next->next) << '\n';
  cout << *(first->next->next->next->next) << '\n';
  //   cout << *(first->next->next->next->next->next) << '\n';
  cout << '\n';

  Node* current = first;
  cout << *current << endl;

  current = current->next;
  cout << *current << endl;

  current = current->next;
  cout << *current << endl;

  current = current->next;
  cout << *current << endl;

  current = current->next;
  cout << *current << endl;

  RecurPrint(first);
  cout << endl;

  IterPrint(first);
  cout << endl;

  Node* temp = first;
  while (temp) {
    Node* current = temp;
    temp = temp->next;
    delete current;
  }
}