#include <gtest/gtest.h>
extern "C" {
#include <polymath.h>
}

static void expect_plm(const plm_number *n,
                       int sign,
                       unsigned long long len,
                       unsigned long long scale,
                       std::initializer_list<long long> limbs) {
  ASSERT_EQ(n->sign, sign);
  ASSERT_EQ(n->contents_length, len);
  ASSERT_EQ(n->number_of_decimal_digits, scale);
  ASSERT_EQ(len, limbs.size());
  size_t i = 0;
  for (auto v : limbs) {
    ASSERT_EQ(n->contents[i++], v);
  }
}

// 5.25 - 2.75 = 2.5
TEST(subtract_tests, pos_minus_pos_simple) {
  plm_number *a = plm_from_base10_string("5.25");
  plm_number *b = plm_from_base10_string("2.75");
  plm_number *r = plm_subtract(a, b);
  expect_plm(r, 0, 1, 1, {25});
  plm_free(a);
  plm_free(b);
  plm_free(r);
}

// 2.75 - 5.25 = -2.5
TEST(subtract_tests, smaller_minus_larger) {
  plm_number *a = plm_from_base10_string("2.75");
  plm_number *b = plm_from_base10_string("5.25");
  plm_number *r = plm_subtract(a, b);
  expect_plm(r, 1, 1, 1, {25});
  plm_free(a);
  plm_free(b);
  plm_free(r);
}

// -5.25 - 2.75 = -8
TEST(subtract_tests, neg_minus_pos) {
  plm_number *a = plm_from_base10_string("-5.25");
  plm_number *b = plm_from_base10_string("2.75");
  plm_number *r = plm_subtract(a, b);
  expect_plm(r, 1, 1, 0, {8});
  plm_free(a);
  plm_free(b);
  plm_free(r);
}

// 5.25 - (-2.75) = 8
TEST(subtract_tests, pos_minus_neg) {
  plm_number *a = plm_from_base10_string("5.25");
  plm_number *b = plm_from_base10_string("-2.75");
  plm_number *r = plm_subtract(a, b);
  expect_plm(r, 0, 1, 0, {8});
  plm_free(a);
  plm_free(b);
  plm_free(r);
}

// 123.45 - 0.0067 = 123.4433
TEST(subtract_tests, alignment_mismatch) {
  plm_number *a = plm_from_base10_string("123.45");
  plm_number *b = plm_from_base10_string("0.0067");
  plm_number *r = plm_subtract(a, b);
  expect_plm(r, 0, 1, 4, {1234433});
  plm_free(a);
  plm_free(b);
  plm_free(r);
}

// 0.999 - 0.001 = 0.998
TEST(subtract_tests, borrow_across_decimal) {
  plm_number *a = plm_from_base10_string("0.999");
  plm_number *b = plm_from_base10_string("0.001");
  plm_number *r = plm_subtract(a, b);
  expect_plm(r, 0, 1, 3, {998});
  plm_free(a);
  plm_free(b);
  plm_free(r);
}

// 1.0000000000001 - 0.0000000000001 = 1
TEST(subtract_tests, cancels_to_integer) {
  plm_number *a = plm_from_base10_string("1.0000000000001");
  plm_number *b = plm_from_base10_string("0.0000000000001");
  plm_number *r = plm_subtract(a, b);
  expect_plm(r, 0, 1, 0, {1});
  plm_free(a);
  plm_free(b);
  plm_free(r);
}

// -2.75 - (-5.25) = 2.5
TEST(subtract_tests, neg_minus_neg) {
  plm_number *a = plm_from_base10_string("-2.75");
  plm_number *b = plm_from_base10_string("-5.25");
  plm_number *r = plm_subtract(a, b);
  expect_plm(r, 0, 1, 1, {25});
  plm_free(a);
  plm_free(b);
  plm_free(r);
}