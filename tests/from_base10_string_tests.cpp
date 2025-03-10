#include <gtest/gtest.h>
extern "C" {
#include <polymath.h>
}

// Test case 1: Test with less than 20 digits
TEST(from_base10_string_tests, less_than_20_digits) {
  plm_number *result = plm_from_base10_string("123");
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  ASSERT_EQ(result->contents_length, 1);
  ASSERT_EQ(result->contents[0], 123);
  plm_free(result);
}

// Test case 2: Test with more than 20 digits
TEST(from_base10_string_tests, more_than_20_digits) {
  plm_number *result =
      plm_from_base10_string("316398127368712683612983619783612329871263");
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  ASSERT_EQ(result->contents_length, 5);
  ASSERT_EQ(result->contents[0], 316398);
  ASSERT_EQ(result->contents[1], 127368712);
  ASSERT_EQ(result->contents[2], 683612983);
  ASSERT_EQ(result->contents[3], 619783612);
  ASSERT_EQ(result->contents[4], 329871263);
  plm_free(result);
}

TEST(from_base10_string_tests, small_decimal) {
  plm_number *result = plm_from_base10_string("3.1415");
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->number_of_decimal_digits, 4);
  ASSERT_EQ(result->contents_length, 1);
  ASSERT_EQ(result->contents[0], 31415);
  plm_free(result);
}