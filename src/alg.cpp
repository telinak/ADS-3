// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char ch) {
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
  char top = 0;
  TStack <char> stack1;
  std::string strpst;
  for (int i = 0; i < inf.length(); i++) {
    int prior;
    prior = priority(inf[i]);
    if (prior > -1) {
      if ((prior == 0 || prior > priority(top) ||
           stack1.isEmpty()) && inf[i] != ')') {
        if (stack1.isEmpty())
          top = inf[i];
        stack1.push(inf[i]);
      } else if (inf[i] == ')') {
        while (stack1.get() != '(') {
          strpst.push_back(stack1.get());
          strpst.push_back(' ');
          stack1.pop();
        }
        stack1.pop();
        if (stack1.isEmpty())
          top = 0;
      } else {
        while (!stack1.isEmpty() &&
               priority(stack1.get()) >= prior) {
          strpst.push_back(stack1.get());
          strpst.push_back(' ');
          stack1.pop();
        }
        if (stack1.isEmpty())
          top = inf[i];
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
int calculator(int num1, int num2, char operation) {
  switch (operation) {
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case'*': return num1 * num2;
    case '/': return num1 / num2;
  }
}
int eval(std::string pst) {
  TStack <int> stack2;
  int i = 0;
  int res = 0;
  char ch = pst[i];
  while (ch) {
    if (ch >= '0' && ch <= '9') {
      int chpst = 0;
      int dec = 1;
      while (ch != ' ') {
        chpst += (ch - 48) * dec;
        dec *= 10;
        ch = pst[++i];
      }
      stack2.push(chpst);
    } else {
      char operation = ch;
      i++;
      int num2 = stack2.get();
      stack2.pop();
      int num1 = stack2.get();
      stack2.pop();
      int res = calculator(num1, num2, operation);
      stack2.push(res);
    }
    if (i < pst.size())
      ch = pst[++i];
    else
      ch = 0;
  }
  res = stack2.get();
  stack2.pop();
  return res;
}
