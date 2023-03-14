#include <gtest/gtest.h>

// Include the header files for all the test cases
#include "from_base10_string_tests.hpp"
#include "to_base10_string_tests.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  // Add all the test suites
  ::testing::AddGlobalTestEnvironment(new from_base10_string_tests);
  ::testing::AddGlobalTestEnvironment(new to_base10_string_tests);

  return RUN_ALL_TESTS();
}