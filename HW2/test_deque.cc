#include <gtest/gtest.h>
#include "deque.h"

int debug_new = 0;

void *operator new(size_t size) {
  if (debug_new)
    std::cout << "new allocates " << size << " bytes" << std::endl;

  return malloc(size);
}

TEST(Deque, Empty) {
  Deque<int> dq;

  /* Should be fully empty */
  EXPECT_EQ(dq.Empty(), true);
  EXPECT_EQ(dq.Size(), 0);
  EXPECT_THROW(dq.PopFront(), std::exception);
  EXPECT_THROW(dq.PopBack(), std::exception);
}

TEST(Deque, DoubleInsertionBack) {
  Deque<int> dq;

  /* Test some insertions at back */
  dq.PushBack(23);
  dq.PushBack(42);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 2);
  EXPECT_EQ(dq[0], 23);
  EXPECT_EQ(dq[1], 42);
  EXPECT_EQ(dq.Back(), 42);
}

TEST(Deque, DoubleInsertionBackFront) {
  Deque<int> dq;

  /* Test some insertions at back and front */
  dq.PushBack(23);
  dq.PushFront(42);
  EXPECT_EQ(dq.Empty(), false);
  EXPECT_EQ(dq.Size(), 2);
  EXPECT_EQ(dq[0], 42);
  EXPECT_EQ(dq[1], 23);
  EXPECT_EQ(dq.Back(), 23);
}

TEST(Deque, GrowShrink) {  // test automatic growth/shrinkage, ShrinkToFit()
  debug_new = 1;

  Deque<int> dq;  // default size of 5: 20 bytes allocated

  dq.PushBack(1);
  dq.PushBack(2);
  dq.PushBack(3);
  dq.PushBack(4);
  dq.PushBack(5);

  EXPECT_EQ(dq.Size(), 5);

  dq.PushFront(6);  // resize to 10: 40 bytes allocated
  dq.PushFront(7);
  dq.PushFront(8);
  dq.PushFront(9);
  dq.PushFront(10);

  EXPECT_EQ(dq.Size(), 10);

  dq.PopBack();
  dq.PopBack();
  dq.PopBack();
  dq.PopBack();
  dq.PopFront();
  dq.PopFront();
  dq.PopFront();
  dq.PopFront();  // resize back to 5: 20 bytes allocated

  // resize to 2: 8 bytes allocated
  dq.ShrinkToFit();
  debug_new = 0;
}

TEST(Deque, RandomAccess) {
  Deque<int> dq;

  EXPECT_THROW(dq.Front(), std::underflow_error);
  EXPECT_THROW(dq.Back(), std::underflow_error);

  dq.PushBack(1);
  dq.PushBack(2);
  dq.PushBack(3);
  dq.PushBack(4);
  dq.PushBack(5);

  EXPECT_EQ(dq.Front(), 1);
  EXPECT_EQ(dq.Back(), 5);

  // testing random access
  EXPECT_EQ(dq[0], 1);
  EXPECT_EQ(dq[1], 2);
  EXPECT_EQ(dq[2], 3);
  EXPECT_EQ(dq[3], 4);
  EXPECT_EQ(dq[4], 5);

  // testing out of range indices
  EXPECT_THROW(dq[-1], std::out_of_range);
  EXPECT_THROW(dq[5], std::out_of_range);
}

TEST(Deque, ClearDeque) {  // test Clear() function
  Deque<int> dq;

  dq.PushBack(1);
  dq.PushBack(2);
  dq.PushBack(3);
  dq.PushBack(4);
  dq.PushBack(5);

  dq.Clear();
  EXPECT_EQ(dq.Size(), 0);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

