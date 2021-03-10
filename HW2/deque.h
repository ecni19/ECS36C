#ifndef DEQUE_H_
#define DEQUE_H_

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <cassert>
#include <utility>

template <typename T>
class Deque {
 public:
  //
  // @@@ The class's public API below should NOT be modified @@@
  //

  // Constructor
  Deque();
  // Destructor
  ~Deque();

  //
  // Capacity
  //

  // Return true if empty, false otherwise
  // Complexity: O(1)
  bool Empty() const noexcept;
  // Return number of items in deque
  // Complexity: O(1)
  size_t Size() const noexcept;
  // Resize internal data structure to fit precisely the number of items and
  // free unused memory
  // Complexity: O(N)
  void ShrinkToFit();

  //
  // Element access
  //

  // Return item at pos @pos
  // Complexity: O(1)
  T& operator[](size_t pos);
  // Return item at front of deque
  // Complexity: O(1)
  T& Front();
  // Return item at back of deque
  // Complexity: O(1)
  T& Back();

  //
  // Modifiers
  //

  // Clear contents of deque (make it empty)
  // Complexity: O(1)
  void Clear(void) noexcept;
  // Push item @value at front of deque
  // Complexity: O(1) amortized
  void PushFront(const T &value);
  // Push item @value at back of deque
  // Complexity: O(1) amortized
  void PushBack(const T &value);
  // Remove item at front of deque
  // Complexity: O(1) amortized
  void PopFront();
  // Remove item at back of deque
  // Complexity: O(1) amortized
  void PopBack();

 private:
  //
  // @@@ The class's internal members below can be modified @@@
  //

  // Private member variables
  // ...To be completed...
  unsigned int max_cap = 5;
  std::unique_ptr<T[]> items;
  unsigned int cur_size = 0;

  int head = -1;
  int tail = -1;

  // Private constants
  // ...To be completed (if any)...

  // Private methods
  // ...To be completed (if any)...

  // Additional private function for resizing the deque
  void Resize(unsigned int new_cap) {
    assert(new_cap && new_cap >= cur_size);

    std::unique_ptr<T[]>new_items(new T[new_cap]);
    if (head > tail) {
      std::move(std::next(items.get(), head),  // copy from head to end of arr
                std::next(items.get(), max_cap),
                new_items.get());
      std::move(items.get(),  // this move copies items from arr[0] to tail
                std::next(items.get(), tail + 1),
                std::next(new_items.get(), max_cap - head));
    } else {
        std::move(items.get(),  // default copy; copy from head to tail
                  std::next(items.get(), cur_size),
                  new_items.get());
    }
    std::swap(items, new_items);
    max_cap = new_cap;
    head = 0;
    tail = cur_size - 1;
  }
};
//
// Your implementation of the class should be located below
//
template <typename T>
Deque<T>::Deque() : items(std::unique_ptr<T[]>(new T[max_cap])) { }

template <typename T>
Deque<T>::~Deque() = default;

// capacity
template <typename T>
bool Deque<T>::Empty() const noexcept {
  if (cur_size == 0)
    return true;
  return false;
}

template <typename T>
size_t Deque<T>::Size() const noexcept {
  return cur_size;
}

template <typename T>
void Deque<T>::ShrinkToFit() {
  Resize(cur_size);
}

// element access
template <typename T>
T& Deque<T>::operator[](size_t pos) {
  if (pos > cur_size - 1 || pos < 0)
    throw std::out_of_range("Error: position out of range");
  if ((pos + head) >= max_cap)
    return items[(head + pos) - max_cap];
  else
    return items[pos + head];
}

template <typename T>
T& Deque<T>::Front() {
  if (Empty())
    throw std::underflow_error("Error: empty deque");
  return items[head];
}

template <typename T>
T& Deque<T>::Back() {
  if (Empty())
    throw std::underflow_error("Error: empty deque");

  return items[tail];
}

// modifiers
template <typename T>
void Deque<T>::Clear(void) noexcept {
  head = -1;
  tail = 0;
  cur_size = 0;
}

template <typename T>
void Deque<T>::PushFront(const T &value) {
  if (cur_size == max_cap)  // if arr full
    Resize(2 * max_cap);

  if (head == -1) {  // if empty
    head = 0;
    tail = 0;
  } else if (head == 0) {  // if head @ beginning of arr
      head = max_cap - 1;
  } else {
      head = head - 1;
  }

  items[head] = value;
  cur_size++;
}

template <typename T>
void Deque<T>::PushBack(const T &value) {
  if (cur_size == max_cap)  // if arr full
    Resize(2 * max_cap);

  if (head == -1) {  // if empty
    head = 0;
    tail = 0;
  } else if (tail == static_cast<int>(max_cap - 1)) {  // if tail @ end of arr
      tail = 0;
  } else {
      tail = tail + 1;
  }

  items[tail] = value;
  cur_size++;
}

template <typename T>
void Deque<T>::PopFront() {
  if (cur_size == 0)  // empty arr
    throw std::underflow_error("Error: empty deque");  // right exception?

  if (head == static_cast<int>(max_cap - 1)) {  // if head @ end of arr
    head = 0;
    cur_size--;
  } else if (head == tail) {  // one element, reset to original head/tail value
      head = -1;
      tail = 0;
      cur_size--;
  } else {
      head++;
      cur_size--;
  }

  if (cur_size <= max_cap / 4)
    Resize(max_cap / 2);
}

template <typename T>
void Deque<T>::PopBack() {
  if (cur_size == 0)  // empty arr
    throw std::underflow_error("Error: empty deque");

  if (tail == 0) {  // tail @ beginning of arr
    tail = cur_size - 1;
    cur_size--;
  } else if (head == tail) {  // one element, reset to original head/tail value
      head = -1;
      tail = 0;
      cur_size = 0;
  } else {
      tail--;
      cur_size--;
  }

  if (cur_size <= max_cap / 4)
    Resize(max_cap / 2);
}

#endif  // DEQUE_H_
