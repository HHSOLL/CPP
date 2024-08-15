#include <iostream>

#include "BinaryTree.h"

int Prec(char c);
void InfixToPostfix(Queue<char>& q, Queue<char>& output);
int EvalPostfix(Queue<char>& q);

class ExpressionTree : public BinaryTree<char> {
 public:
  typedef BinaryTree<char> Base;
  ExpressionTree(Node* root) : Base(root) {}

  bool IsDigit(char c) {
    if ('0' <= c && c <= '9')
      return true;
    else
      return false;
  }

  int Evaluate() { return Evaluate(Base::root_); }
  int Evaluate(Node* node) {
    if (!node) return 0;

    char temp = node->item;
    if ('0' <= temp && temp <= '9') {
      return node->item - '0';
    } else if (temp == '+') {
      return Evaluate(node->left) + Evaluate(node->right);
    } else if (temp == '-') {
      return Evaluate(node->left) - Evaluate(node->right);
    } else if (temp == '*') {
      return Evaluate(node->left) * Evaluate(node->right);
    } else if (temp == '/') {
      return Evaluate(node->left) / Evaluate(node->right);
    }
    return 0;
  }

  void Infix() {
    Infix(root_);
    std::cout << '\n';
  }
  void Infix(Node* node) {
    if (!node) return;

    char temp = node->item;
    if ('0' <= temp && temp <= '9') {
      std::cout << temp;
    } else {
      std::cout << "(";
      Infix(node->left);
      std::cout << node->item;
      Infix(node->right);
      std::cout << ")";
    }
  }

  void Postfix() {
    Postfix(root_);
    std::cout << '\n';
  }
  void Postfix(Node* node) {
    if (!node) return;

    char temp = node->item;
    if ('0' <= temp && temp <= '9') {
      std::cout << temp;
    } else {
      Postfix(node->left);
      Postfix(node->right);
      std::cout << node->item;
    }
  }

  // Infix -> postfix -> expression tree
  ExpressionTree(const char* infix) {
    // Infix -> Postfix (예제 재사용)
    // const char infix[] = "(5+((3-2)*4))";
    Queue<char> q;
    for (int i = 0; infix[i] != '\0'; i++) q.Enqueue(infix[i]);
    std::cout << "  Infix: ";

    q.Print();
    Queue<char> postfix;
    InfixToPostfix(q, postfix);
    std::cout << "Postfix: ";
    postfix.Print();

    // Postfix -> Expression tree

    Stack<Node*> s;

    while (!postfix.IsEmpty()) {
      char c = postfix.Front();
      postfix.Dequeue();

      Node* new_node = new Node;
      new_node->item = c;
      if (c >= '0' && c <= '9') {
        s.Push(new_node);
      } else {
        new_node->right = s.Top();
        s.Pop();
        new_node->left = s.Top();
        s.Pop();
        s.Push(new_node);
      }
    }
    root_ = s.Top();
  }
};

int main(void) {
  using Node = ExpressionTree::Node;

  // 5 + (3 - 2) * 4
  //
  //      +
  //	/   \
	// 5     *
  //	    / \
	//	   -   4
  //	  / \
	//	 3   2

  Node* n1 = new Node{'5', nullptr, nullptr};
  Node* n2 = new Node{'+', nullptr, nullptr};
  Node* n3 = new Node{'3', nullptr, nullptr};
  Node* n4 = new Node{'-', nullptr, nullptr};
  Node* n5 = new Node{'2', nullptr, nullptr};
  Node* n6 = new Node{'*', nullptr, nullptr};
  Node* n7 = new Node{'4', nullptr, nullptr};

  // +
  n2->left = n1;   // 5
  n2->right = n6;  // *

  // *
  n6->left = n4;   // -
  n6->right = n7;  // 4

  // -
  n4->left = n3;   // 3
  n4->right = n5;  // 2

  ExpressionTree tree(n2);

  tree.Print2D();

  // 수식 트리에 저장되어 있는 수식을 실제로 계산해서 그 결과를 출력합니다.
  std::cout << "Evaluated = " << tree.Evaluate() << '\n';  // Evaluated = 9

  // 수식 트리에 저장되어 있는 수식을 Infix 방식으로 출력합니다.
  std::cout << "  Infix: ";
  tree.Infix();  // (5+((3-2)*4)) <- 출력 예시

  // 수식 트리에 저장되어 있는 수식을 Postfix 방식으로 출력합니다.
  std::cout << "Postfix: ";
  tree.Postfix();  // 532-4*+ <- 출력 예시

  std::cout << '\n';

  // Infix -> Postfix -> Expression Tree
  {
    // const char infix[] = "1+(1*2+3)*4";
    const char infix[] = "(5+((3-2)*4))";

    // 생성자에서 문자열로 입력받은 수식을 내부적으로 Infix->Postfix 과정을
    // 거쳐 트리로 저장합니다.
    ExpressionTree tree(infix);

    tree.Print2D();

    // 수식 트리에 저장되어 있는 수식을 실제로 계산해서 그 결과를 출력합니다.
    std::cout << "Evaluated = " << tree.Evaluate() << '\n';  // Evaluated = 9
  }

  return 0;
}

int Prec(char c) {
  if (c == '/' || c == '*')
    return 2;
  else if (c == '+' || c == '-')
    return 1;
  else
    return -1;
}
void InfixToPostfix(Queue<char>& q, Queue<char>& output) {
  Stack<char> s;

  while (!q.IsEmpty()) {
    char c = q.Front();
    q.Dequeue();

    if ('0' <= c && c <= '9') {
      output.Enqueue(c);
    } else if (c == '(') {
      s.Push(c);
    } else if (c == ')') {
      while (s.Top() != '(') {
        output.Enqueue(s.Top());
        s.Pop();
      }
      s.Pop();
    } else {
      while (!s.IsEmpty() && Prec(c) <= Prec(s.Top())) {
        output.Enqueue(s.Top());
        s.Pop();
      }
      s.Push(c);
    }
  }
  while (!s.IsEmpty()) {
    output.Enqueue(s.Top());
    s.Pop();
  }
}
int EvalPostfix(Queue<char>& q) {
  Stack<int> s;

  while (!q.IsEmpty()) {
    char c = q.Front();
    q.Dequeue();

    // cout << c << endl;

    if (c != '+' && c != '-' && c != '*' && c != '/') {
      s.Push(c - '0');  // 입력이 연산자가 아니면 일단 저장
    } else {
      // cout << "Operator: " << c << endl;

      // 입력이 연산자이면 스택에서 꺼내서 연산에 사용
      int op2 = s.Top();  // op1, op2 순서 주의
      s.Pop();
      int op1 = s.Top();
      s.Pop();

      if (c == '+') {
        s.Push(op1 + op2);
      } else if (c == '-') {
        s.Push(op1 - op2);
      } else if (c == '*') {
        s.Push(op1 * op2);
      } else if (c == '/') {
        s.Push(op1 / op2);
      } else {
        std::cout << "Wrong operator" << '\n';
        exit(-1);  // 강제 종료
      }
    }

    // cout << "Stack: ";
    // s.Print();
  }

  return s.Top();
}