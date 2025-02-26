#include <gtest/gtest.h>
extern "C" {
#include <polymath.h>
}

TEST(multiply_whole_tests, two_times_two) {
  plm_number *a = plm_from_base10_string("2");
  plm_number *b = plm_from_base10_string("2");
  struct plm_number *result = plm_multiply_whole(a, b);
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->contents_length, 1);
  ASSERT_EQ(result->contents[0], 4);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}

TEST(multiply_whole_tests, basic_test) {
  plm_number *a = plm_from_base10_string("219823");
  plm_number *b = plm_from_base10_string("59812");
  struct plm_number *result = plm_multiply_whole(a, b);
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->contents_length, 2);
  ASSERT_EQ(result->contents[0], 13);
  ASSERT_EQ(result->contents[1], 148053276);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}

TEST(multiply_whole_tests, all_nines) {
  plm_number *a = plm_from_base10_string("999999999999999999");
  plm_number *b = plm_from_base10_string("999999999999999999");
  struct plm_number *result = plm_multiply_whole(a, b);
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->contents_length, 4);
  ASSERT_EQ(result->contents[0], 999999999);
  ASSERT_EQ(result->contents[1], 999999998);
  ASSERT_EQ(result->contents[2], 000000000);
  ASSERT_EQ(result->contents[3], 000000001);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}