#include <iostream>

#include "../shared/Queue.h"
#include "../shared/Stack.h"

int Prec(char c);
void InfixToPostfix(Queue<char>& q, Queue<char>& output);
int EvalPostfix(Queue<char>& postfix);

int main() {
  const char infix[] = "1+(1*2+3)*4";

  const int size = sizeof(infix) / sizeof(char) - 1;

  Queue<char> q;
  for (int i = 0; i < size; i++) {
    q.Enqueue(infix[i]);
  }

  Queue<char> postfix;

  std::cout << "Infix : ";
  q.Print();
  std::cout << '\n';

  InfixToPostfix(q, postfix);

  std::cout << "Postfix : ";
  postfix.Print();
  std::cout << '\n';

  std::cout << "Evaluated : " << EvalPostfix(postfix) << '\n';

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

  output.SetDebugFlag(false);

  while (!q.IsEmpty()) {
    char c = q.Front();
    q.Dequeue();

    std::cout << c << '\n';

    if (c >= '0' && c <= '9') {
      output.Enqueue(c);
    } else if (c == '(') {
      s.Push(c);
    } else if (c == ')') {
      while (!(s.Top() == '(')) {
        output.Enqueue(s.Top());
        s.Pop();
      }
      s.Pop();

    } else {
      if (!s.IsEmpty()) {
        if (s.Top() == '*' || s.Top() == '%') {
          output.Enqueue(s.Top());
          s.Pop();
        }
      }
      s.Push(c);
    }
  }
  while (!s.IsEmpty()) {
    output.Enqueue(s.Top());
    s.Pop();
  }
}

int EvalPostfix(Queue<char>& postfix) {
  Stack<int> s;

  while (!postfix.IsEmpty()) {
    int n, a, b;
    char c = postfix.Front();
    postfix.Dequeue();
    // std::cout << c << '\n';

    if (c >= '0' && c <= '9') {
      n = int(c - '0');
      s.Push(n);
    } else {
      if (c == '+') {
        b = s.Top();
        s.Pop();
        a = s.Top();
        s.Pop();
        s.Push(a + b);
      } else if (c == '-') {
        a = s.Top();
        s.Pop();
        b = s.Top();
        s.Pop();
        s.Push(a - b);
      } else if (c == '*') {
        a = s.Top();
        s.Pop();
        b = s.Top();
        s.Pop();
        s.Push(a * b);
      } else if (c == '/') {
        a = s.Top();
        s.Pop();
        b = s.Top();
        s.Pop();
        s.Push(a / b);
      } else {
        std::cout << "Wrong Operator." << '\n';
        exit(-1);
      }
    }
  }
  //   std::cout << "STACK : ";
  //   s.Print();

  return s.Top();
}