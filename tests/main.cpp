#include <gtest/gtest.h>
// Run all the tests that were declared with TEST() or TEST_F()
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
