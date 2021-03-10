#include <gtest/gtest.h>
#include <vector>

#include "multimap.h"

// Test one key
TEST(Multimap, OneKey) {
  Multimap<int, int> mmap;
  std::vector<int> keys{2};

  for (auto i : keys) {
    mmap.Insert(i, i);
  }

  EXPECT_EQ(mmap.Contains(2), true);
  EXPECT_EQ(mmap.Get(2), keys[0]);
}

// Test multiple keys
TEST(Multimap, MultipleKeys) {
  Multimap<int, int> mmap;
  std::vector<int> keys{2, 18, 42, 43};

  // Insert a bunch of keys
  for (auto i : keys) {
    mmap.Insert(i, i);
  }

  // Check that every key is contained
  std::random_shuffle(keys.begin(), keys.end());
  for (auto i : keys) {
    EXPECT_EQ(mmap.Contains(i), true);
    EXPECT_EQ(mmap.Get(i), i);
  }
}

// testing duplicate inserts.
TEST(Multimap, DuplicateInserts) {
    Multimap<int, int> mmap;
    std::vector<int> keys {2, 2, 42, 42};

    for (auto i : keys) {
      mmap.Insert(i, i);
    }

    std::random_shuffle(keys.begin(), keys.end());
    for (auto i : keys) {
      EXPECT_EQ(mmap.Contains(i), true);
      EXPECT_EQ(mmap.Get(i), i);
    }
    std::cout << "Printing all key/value pairs: ";
    mmap.Print();
}

// test removal of duplicate keys as well as single keys
TEST(Multimap, Remove) {
    Multimap<int, int> mmap;

    mmap.Insert(1, 3);
    mmap.Insert(7, 4);  // three duplicate keys
    mmap.Insert(7, 5);
    mmap.Insert(7, 6);
    mmap.Insert(8, 1);
    mmap.Insert(9, 2);
    mmap.Insert(4, 3);

    std::cout << "Before removal: ";
    mmap.Print();

    EXPECT_EQ(mmap.Get(1), 3);
    EXPECT_EQ(mmap.Get(7), 4);
    EXPECT_EQ(mmap.Get(8), 1);

    mmap.Remove(7);  // should remove the first value, 4
    mmap.Remove(8);  // should delete the node

    std::cout << "After removal: ";
    mmap.Print();

    EXPECT_EQ(mmap.Get(7), 5);
    EXPECT_EQ(mmap.Contains(7), true);  // key 7 still exists

    EXPECT_THROW(mmap.Get(8), std::runtime_error);
    EXPECT_EQ(mmap.Contains(8), false);  // key 5 d.n.e
}

// testing insertion of characters
TEST(Multimap, Chars) {
  Multimap<char, int> mmap;

  mmap.Insert('a', 1);
  mmap.Insert('b', 2);
  mmap.Insert('c', 3);
  mmap.Insert('d', 4);
  mmap.Insert('e', 5);
  mmap.Insert('e', 6);

  EXPECT_EQ(mmap.Size(), 6);

  EXPECT_EQ(mmap.Get('e'), 5);
  EXPECT_EQ(mmap.Get('d'), 4);
  EXPECT_EQ(mmap.Get('c'), 3);

  std::cout << "Before removal: ";
  mmap.Print();

  mmap.Remove('e');
  mmap.Remove('a');

  std::cout << "After removal: ";
  mmap.Print();

  EXPECT_EQ(mmap.Size(), 4);

  EXPECT_EQ(mmap.Get('e'), 6);
  EXPECT_THROW(mmap.Get('a'), std::runtime_error);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
