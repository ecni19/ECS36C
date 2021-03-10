#ifndef MULTISET_H_
#define MULTISET_H_

#include <cstddef>
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <utility>

template <typename K>
class Multiset {
 public:
  //
  // Public API
  //

  // * Capacity
  // Returns number of items in multiset --O(1)
  size_t Size();
  // Returns true if multiset is empty --O(1)
  bool Empty();

  // * Modifiers
  // Inserts an item corresponding to @key in multiset --O(log N) on average
  void Insert(const K &key);
  // Removes an item corresponding to @key from multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  void Remove(const K &key);

  // * Lookup
  // Return whether @key is found in multiset --O(log N) on average
  bool Contains(const K& key);
  // Returns number of items matching @key in multiset --O(log N) on average
  //  Throws exception if key doesn't exist
  size_t Count(const K& key);

  // Return greatest key less than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no floor exists for key
  const K& Floor(const K &key);
  // Return least key greater than or equal to @key --O(log N) on average
  //  Throws exception if multiset is empty or no ceil exists for key
  const K& Ceil(const K &key);

  // Return max key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K& Max();
  // Return min key in multiset --O(log N) on average
  //  Throws exception if multiset is empty
  const K& Min();

 private:
  //
  // @@@ The class's internal members below can be modified @@@
  //

  // Private member variables
  // ...To be completed...
  struct Node {
    K key;
    unsigned int counter;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };
  std::unique_ptr<Node> root;
  size_t cur_size = 0;
  // Private constants
  // ...To be completed (if any)...

  // Private methods
  // ...To be completed (if any)...
  void Remove(std::unique_ptr<Node> &n, const K &key);
  void Insert(std::unique_ptr<Node> &n, const K &key);
  Node* Min(Node *n);
  Node* Max(Node *n);
};

//
// Your implementation of the class should be located below
//

// ...To be completed...

template <typename K>
size_t Multiset<K>::Size() {
  return cur_size;
}

template <typename K>
bool Multiset<K>::Empty() {
  if (!Size())
    return true;

  return false;
}

template <typename K>
void Multiset<K>::Insert(const K &key) {
  Insert(root, key);
  cur_size++;
}

template <typename K>
void Multiset<K>::Insert(std::unique_ptr<Node> &n, const K &key) {
  if (!n) {
    n = std::unique_ptr<Node>(new Node{key, 1});
  } else if (key < n->key) {
      Insert(n->left, key);
  } else if (key > n->key) {
      Insert(n->right, key);
  } else if (key == n->key) {
      // if key already exists, just increment the node's counter
      (n->counter)++;
  }
}

template <typename K>
void Multiset<K>::Remove(const K &key) {
  Remove(root, key);
  cur_size--;
}

template <typename K>
void Multiset<K>::Remove(std::unique_ptr<Node> &n, const K& key) {
  if (Empty())
    throw std::underflow_error("Error: empty multiset");
  if (!Contains(key))
    throw std::invalid_argument("Error: key not in multiset");

  if (!n) return;

  if (key < n->key) {
    Remove(n->left, key);
  } else if (key > n->key) {
      Remove(n->right, key);
  } else {
      // decrement count if duplicates exist.
      if (n->counter > 1) {
        (n->counter)--;
      } else if (n->left && n->right) {
          n->key = Min(n->right.get())->key;
          // need to update count in addition to the key
          n->counter = Min(n->right.get())->counter;
          Remove(n->right, n->key);
      } else {
          n = std::move((n->left) ? n->left : n->right);
      }
    }
}

template <typename K>
bool Multiset<K>::Contains(const K& key) {
  if (Empty())
    throw std::underflow_error("Error: empty multiset");

  Node *n = root.get();

  while (n) {
    if (key == n->key) {
      return true;
    } else if (key < n->key) {
        n = n->left.get();
    } else {
        n = n->right.get();
    }
  }
  return false;
}

template <typename K>
size_t Multiset<K>::Count(const K& key) {
  if (Empty())
    throw std::underflow_error("Error: empty multiset");
  if (!Contains(key))
    throw std::invalid_argument("Error: key not in multiset");

  Node *n = root.get();
  size_t node_count = 0;

  while (n) {
    if (key == n->key) {
      node_count = n->counter;
      break;
    } else if (key < n->key) {
        n = n->left.get();
    } else {
        n = n->right.get();
    }
  }
  return node_count;
}

template <typename K>
const K& Multiset<K>::Floor(const K &key) {
  // checking for errors
  if (Empty())
    throw std::underflow_error("Error: empty multiset");
  if (key < Min())
    throw std::invalid_argument("Error: key cannot be smaller than min");

  // using two Nodes to represent current (n) and prev (prev)
  Node *n = root.get();
  Node *prev;

  // normal tree traversal.
  while (n) {
    // just return n->key if key is in tree
    if (key == n->key) {
      return n->key;
    } else if (key < n->key) {
        // reached end of tree
        if (n->left.get() == nullptr)
          break;
        prev = n;
        n = n->left.get();
    } else {
        if (n->right.get() == nullptr)
          break;
        prev = n;
        n = n->right.get();
    }
  }
  // compare key with current node (n) and previous node (prev)
  if (key > n->key)
    return n->key;
  else
    return prev->key;
}

template <typename K>
const K& Multiset<K>::Ceil(const K &key) {
  if (Empty())
    throw std::underflow_error("Error: empty multiset");
  if (key > Max())
    throw std::invalid_argument("Error: key cannot be greater than max");

  Node *n = root.get();
  Node *prev;

  while (n) {
    if (key == n->key) {
      return n->key;
    } else if (key > n->key) {
        if (n->right.get() == nullptr)
          break;
        prev = n;
        n = n->right.get();
    } else {
        if (n->left.get() == nullptr)
          break;
        prev = n;
        n = n->left.get();
    }
  }

  if (key < n->key)
    return n->key;
  else
    return prev->key;
}

template <typename K>
const K& Multiset<K>::Max(void) {
  return Max(root.get())->key;
}

template <typename K>
typename Multiset<K>::Node* Multiset<K>::Max(Node *n) {
  if (Empty())
    throw std::underflow_error("Error: empty multiset");

  if (n->right) {
    return Max(n->right.get());
  } else {
      return n;
  }
}

template <typename K>
const K& Multiset<K>::Min(void) {
  return Min(root.get())->key;
}

template <typename K>
typename Multiset<K>::Node* Multiset<K>::Min(Node *n) {
  if (Empty())
    throw std::underflow_error("Error: empty multiset");

  if (n->left) {
    return Min(n->left.get());
  } else {
     return n;
  }
}

#endif  // MULTISET_H_
