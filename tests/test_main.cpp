#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, Inequality) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
}

TEST(HelloTest, Equality) {
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}