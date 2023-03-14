#pragma once

#include <gtest/gtest.h>
extern "C" {
#include <polymath.h>
}

TEST(to_base10_string_tests, less_than_20_digits) {
  plm_number input = plm_from_base10_string("123");
  char *result = plm_to_base10_string(&input);
  ASSERT_STREQ(result, "123");
  free(result);
  plm_free(&input);
}

TEST(to_base10_string_tests, long_only_zeroes) {
  plm_number input = plm_from_base10_string(
      "000000000000000000000000000000000000000000000000000000000000000000");
  char *result = plm_to_base10_string(&input);
  ASSERT_STREQ(result, "0");
  free(result);
  plm_free(&input);
}

TEST(to_base10_string_tests, long_leading_zeroes) {
  plm_number input = plm_from_base10_string(
      "000000000000000000000000000000000000000000000000000000000000000001");
  char *result = plm_to_base10_string(&input);
  ASSERT_STREQ(result, "1");
  free(result);
  plm_free(&input);
}

TEST(to_base10_string_tests, long_middle_zeroes) {
  plm_number input = plm_from_base10_string(
      "1000000000000000000000000000000000000000000000000000000000000000001");
  char *result = plm_to_base10_string(&input);
  ASSERT_STREQ(
      result,
      "1000000000000000000000000000000000000000000000000000000000000000001");
  free(result);
  plm_free(&input);
}