#ifndef STACK_H_
#define STACK_H_
#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
 private:
  std::vector<T> items;
 public:
  Stack() = default;
  ~Stack() = default;

  void Push(const T &item);
  void Pop();
  unsigned int Size();
  bool IsEmpty();
  T& Top();
};

template <typename T>
void Stack<T>::Push(const T &item) {
  items.push_back(item);
}

template <typename T>
bool Stack<T>::IsEmpty(void) {
  if (!items.size())
    return true;
  else
    return false;
}

template <typename T>
unsigned int Stack<T>::Size() {
  return items.size();
}

template <typename T>
T& Stack<T>::Top(void) {
  if (!items.size())
    throw std::underflow_error("Empty Stack!");
  return items.back();
}

template <typename T>
void Stack<T>::Pop(void) {
  if (!items.size())
    throw std::underflow_error("Empty Stack!");
  items.pop_back();
}

#endif  // STACK_H_
