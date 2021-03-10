#include <gtest/gtest.h>
#include "multiset.h"

TEST(Multiset, Empty) {
  Multiset <int> mset;

  /* Should be fully empty */
  EXPECT_EQ(mset.Empty(), true);
  EXPECT_EQ(mset.Size(), 0);
  EXPECT_THROW(mset.Count(42), std::exception);
}

TEST(Multiset, OneKey) {
  Multiset <int> mset;
  /* various tests for empty multiset */
  EXPECT_THROW(mset.Count(42), std::underflow_error);
  EXPECT_THROW(mset.Remove(42), std::underflow_error);
  EXPECT_THROW(mset.Max(), std::underflow_error);
  EXPECT_THROW(mset.Min(), std::underflow_error);

  /* Test some insertion */
  mset.Insert(23);
  mset.Insert(42);
  mset.Insert(42);

  EXPECT_EQ(mset.Empty(), false);
  EXPECT_EQ(mset.Size(), 3);
  EXPECT_EQ(mset.Min(), 23);
  EXPECT_EQ(mset.Max(), 42);
  EXPECT_EQ(mset.Count(42), 2);

  EXPECT_THROW(mset.Remove(38), std::invalid_argument);
  EXPECT_THROW(mset.Count(53), std::invalid_argument);
}

// test Ceil() functionality and error checking
TEST(Multiset, Ceil) {
  Multiset <int> mset;

  EXPECT_THROW(mset.Ceil(30), std::underflow_error);

  // random insertions
  mset.Insert(7);
  mset.Insert(5);
  mset.Insert(12);
  mset.Insert(3);
  mset.Insert(6);
  mset.Insert(9);
  // Ceil() for current insertions
  EXPECT_EQ(mset.Ceil(1), 3);
  EXPECT_EQ(mset.Ceil(8), 9);
  EXPECT_EQ(mset.Ceil(10), 12);
  EXPECT_THROW(mset.Ceil(20), std::invalid_argument);
  // do some more insertions
  mset.Insert(15);
  mset.Insert(1);
  mset.Insert(4);
  mset.Insert(8);
  mset.Insert(10);
  mset.Insert(13);
  mset.Insert(17);
  // Ceil() for new insertions
  EXPECT_EQ(mset.Ceil(2), 3);
  EXPECT_EQ(mset.Ceil(16), 17);
  EXPECT_EQ(mset.Ceil(14), 15);

  EXPECT_EQ(mset.Ceil(4), 4);
  EXPECT_EQ(mset.Ceil(7), 7);

  EXPECT_THROW(mset.Ceil(30), std::invalid_argument);
}

// test Floor() functionality and error checking
TEST(Multiset, Floor) {
  Multiset <int> mset;

  EXPECT_THROW(mset.Floor(20), std::underflow_error);

  mset.Insert(13);
  mset.Insert(15);
  mset.Insert(14);
  mset.Insert(8);
  mset.Insert(10);
  mset.Insert(18);
  mset.Insert(7);

  EXPECT_EQ(mset.Floor(9), 8);
  EXPECT_EQ(mset.Floor(19), 18);
  EXPECT_EQ(mset.Floor(17), 15);
  EXPECT_THROW(mset.Floor(0), std::invalid_argument);

  mset.Insert(17);
  mset.Insert(23);
  mset.Insert(13);
  mset.Insert(8);
  mset.Insert(28);
  mset.Insert(25);
  mset.Insert(16);

  EXPECT_THROW(mset.Floor(0), std::invalid_argument);

  EXPECT_EQ(mset.Floor(27), 25);
  EXPECT_EQ(mset.Floor(29), 28);
  EXPECT_EQ(mset.Floor(20), 18);

  EXPECT_EQ(mset.Floor(10), 10);
  EXPECT_EQ(mset.Floor(13), 13);
}

// following Contains() test example professor provided
// in testing guidelines
TEST(Multiset, Contains) {
  Multiset <int> mset;
  // check for empty mset
  EXPECT_THROW(mset.Contains(30), std::underflow_error);
  // insert one element
  mset.Insert(7);
  // check that one element is contained in mset
  EXPECT_EQ(mset.Contains(7), true);
  // many insertions
  mset.Insert(5);
  mset.Insert(12);
  mset.Insert(3);
  mset.Insert(6);
  mset.Insert(9);
  mset.Insert(15);
  // check they are all in mset
  EXPECT_EQ(mset.Contains(12), true);
  EXPECT_EQ(mset.Contains(6), true);
  EXPECT_EQ(mset.Contains(3), true);
  EXPECT_EQ(mset.Contains(15), true);
  EXPECT_EQ(mset.Contains(9), true);
  EXPECT_EQ(mset.Contains(5), true);

  mset.Insert(10);
  // check for elements not in mset
  EXPECT_EQ(mset.Contains(30), false);
  EXPECT_EQ(mset.Contains(-2), false);
}

// make sure mset can handle duplicates
// as well as make sure operations return the right numbers
TEST(Multiset, Duplicates) {
  Multiset <int> mset;

  mset.Insert(1);
  mset.Insert(5);
  mset.Insert(12);
  mset.Insert(3);
  mset.Insert(6);
  mset.Insert(9);
  mset.Insert(9);
  mset.Insert(9);
  mset.Insert(6);
  // check to see if duplicates addded correctly
  EXPECT_EQ(mset.Count(9), 3);
  EXPECT_EQ(mset.Count(6), 2);
  // test ceiling and floor functionality with duplicates
  EXPECT_EQ(mset.Ceil(9), 9);
  EXPECT_EQ(mset.Floor(6), 6);

  mset.Remove(9);
  mset.Remove(6);
  // check if Remove() only removes 1 duplicate
  EXPECT_EQ(mset.Count(6), 1);
  EXPECT_EQ(mset.Count(9), 2);
  EXPECT_EQ(mset.Size(), 7);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

