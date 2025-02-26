#include <gtest/gtest.h>
extern "C" {
#include <polymath.h>
}

TEST(from_unsigned_long_long_tests, trivial_test) {
  plm_number *a = plm_from_unsigned_long_long(69);
  ASSERT_EQ(a->sign, 0);
  ASSERT_EQ(a->contents_length, 1);
  ASSERT_EQ(a->contents[0], 69);
  ASSERT_EQ(a->number_of_decimal_digits, 0);
  plm_free(a);
}

TEST(from_unsigned_long_long_tests, big_test) {
  plm_number *a = plm_from_unsigned_long_long(9999999999999999999ULL);
  ASSERT_EQ(a->sign, 0);
  ASSERT_EQ(a->contents_length, 2);
  ASSERT_EQ(a->contents[0], 9);
  ASSERT_EQ(a->contents[1], 999999999999999999);
  ASSERT_EQ(a->number_of_decimal_digits, 0);
  plm_free(a);
}