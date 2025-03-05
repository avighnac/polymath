#include <gtest/gtest.h>
extern "C" {
#include <polymath.h>
}

TEST(add_tests, test_1) {
  plm_number *a = plm_from_base10_string("0.2");
  plm_number *b = plm_from_base10_string("0.2");
  struct plm_number *result = plm_add(a, b);
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->contents_length, 1);
  ASSERT_EQ(result->contents[0], 4);
  ASSERT_EQ(result->number_of_decimal_digits, 1);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}

TEST(add_tests, test_2) {
  plm_number *a = plm_from_base10_string("0.2");
  plm_number *b = plm_from_base10_string("0.21");
  struct plm_number *result = plm_add(a, b);
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->contents_length, 1);
  ASSERT_EQ(result->contents[0], 41);
  ASSERT_EQ(result->number_of_decimal_digits, 2);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}