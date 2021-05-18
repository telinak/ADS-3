// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"
int priory (char ch) {
  switch (ch) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
    default: return -1;
  }
}
std::string infx2pstfx(std::string inf) {
  char t = 0;
  TStack <char> stack1;
  std::string strpst;
  for (int i = 0; i < inf.length(); i++) {
    int priory1;
    priory1 = priory(inf[i]);
    if (priory1 > -1) {
      if ((priory1 == 0 || priory1 > priory(t) ||
           stack1.isEmpty()) && inf[i] != ')') {
        if (stack1.isEmpty())
          t = inf[i];
        stack1.push(inf[i]);
      } else if (inf[i] == ')') {
        while (stack1.get() != '(') {
          strpst.push_back(stack1.get());
          strpst.push_back(' ');
          stack1.pop();
        }
        stack1.pop();
        if (stack1.isEmpty())
          t = 0;
      } else {
        while (!stack1.isEmpty() &&
               priory(stack1.get()) >= priory1) {
          strpst.push_back(stack1.get());
          strpst.push_back(' ');
          stack1.pop();
        }
        if (stack1.isEmpty())
          t = inf[i];
        stack1.push(inf[i]);
      }
    } else {
      strpst.push_back(inf[i]);
      strpst.push_back(' ');
    }
  }
  while (!stack1.isEmpty()) {
    strpst.push_back(stack1.get());
    strpst.push_back(' ');
    stack1.pop();
  }
  strpst.erase(strpst.end() - 1, strpst.end());
  return strpst;
}
int calc(int num1, int num2, char operation) {
  switch (operation) {
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case'*': return num1 * num2;
    case '/': return num1 / num2;
  }
}
int estimation(std::string pst) {
  TStack <int> stack2;
  int i = 0;
  int result = 0;
  char ch = pst[i];
  while (ch) {
    if (ch >= '0' && ch <= '9') {
      int a = 0;
      int b = 1;
      while (ch != ' ') {
        a += (ch - 48) * b;
        b *= 10;
        ch = pst[++i];
      }
      stack2.push(a);
    } else {
      char operation = ch;
      i++;
      int num2 = stack2.get();
      stack2.pop();
      int num1 = stack2.get();
      stack2.pop();
      int result = calc(num1, num2, operation);
      stack2.push(result);
    }
    if (i < pst.size())
      ch = pst[++i];
    else
      ch = 0;
  }
  result = stack2.get();
  stack2.pop();
  return result;
}
