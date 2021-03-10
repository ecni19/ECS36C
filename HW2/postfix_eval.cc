#include <iostream>
#include <string>
#include <sstream>
#include "stack.h"

/* checking if string input is an operator */
bool IsOperator(std::string s) {
  if (s == "+" || s == "-" || s == "*" || s == "/")
    return true;

  return false;
}

/* doing the actual operation on two numbers */
double PerformOperation(const std::string &sign, Stack<double> &numbers) {
  double val1, val2, result;

  val2 = numbers.Top();
  numbers.Pop();

  val1 = numbers.Top();
  numbers.Pop();

  if (sign == "+") result = val1 + val2;
  else if (sign == "-") result = val1 - val2;
  else if (sign == "*") result = val1 * val2;
  else if (sign == "/") result = val1 / val2;

  return result;
}

int main() {
  while (!std::cin.eof()) {
    Stack<double> num_stack;
    bool state = true;
    double num;
    std::string token;

    do {
      std::cin >> token;

      /* check if number */
      if (std::stringstream(token) >> num) {
        num_stack.Push(num);
      } else if (IsOperator(token)) {
          if (num_stack.Size() >= 2) {
            num_stack.Push(PerformOperation(token, num_stack));
          } else {
              std::cerr << "Error: invalid expression" << std::endl;
              std::cin.ignore(256, '\n');
              state = false;
              continue;
          }
        } else {
            std::cerr << "Error: unknown symbol "
                      << "'" << token << "'" << std::endl;
            std::cin.ignore(256, '\n');
            state = false;
            continue;
          }

      char end = std::cin.get();
      /* pop the result */
      if (end == '\n' && num_stack.Size() == 1) {
        std::cout << num_stack.Top() << std::endl;
        num_stack.Pop();
      }
      if (end == '\n' && num_stack.Size() > 1) {
        std::cerr << "Error: invalid expression" << std::endl;
        state = false;
        continue;
      }
    } while (state);
  }
  std::cout << "Bye!" << std::endl;

  return 0;
}
