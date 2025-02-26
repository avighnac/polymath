#include <gtest/gtest.h>
extern "C" {
#include <polymath.h>
}

// Test case 1: 9+10
TEST(add_whole_tests, nine_plus_ten) {
  plm_number *a = plm_from_base10_string("9");
  plm_number *b = plm_from_base10_string("10");
  struct plm_number *result = plm_add_whole(a, b);
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->contents_length, 1);
  ASSERT_EQ(result->contents[0], 19);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}

TEST(add_whole_tests, two_plus_two) {
  plm_number *a = plm_from_base10_string("2");
  plm_number *b = plm_from_base10_string("2");
  struct plm_number *result = plm_add_whole(a, b);
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->contents_length, 1);
  ASSERT_EQ(result->contents[0], 4);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}

TEST(add_whole_tests, basic_carry_test) {
  // 2222222222222222222+9999999999999999999=1 2222222222222222221
  plm_number *a = plm_from_base10_string("2222222222222222222");
  plm_number *b = plm_from_base10_string("9999999999999999999");
  struct plm_number *result = plm_add_whole(a, b);
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->contents_length, 3);
  ASSERT_EQ(result->contents[0], 12);
  ASSERT_EQ(result->contents[1], 222222222);
  ASSERT_EQ(result->contents[2], 222222221);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}

TEST(add_whole_tests, max_19_digit) {
  // 9999999999999999999
  plm_number *a = plm_from_base10_string("9999999999999999999");
  plm_number *b = plm_from_base10_string("9999999999999999999");
  struct plm_number *result = plm_add_whole(a, b);
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->contents_length, 3);
  ASSERT_EQ(result->contents[0], 19);
  ASSERT_EQ(result->contents[1], 999999999);
  ASSERT_EQ(result->contents[2], 999999998);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}

TEST(add_whole_tests, big_test_1) {
  // 129834691234671264213672349123648645796826625189741789647632197469182735
  plm_number *a =
      plm_from_base10_string("1298346912346712642136723491236486457968266251897"
                             "41789647632197469182735");
  plm_number *b =
      plm_from_base10_string("871639874618247921657462786786123876984264");
  struct plm_number *result = plm_add_whole(a, b);
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->contents_length, 8);
  ASSERT_EQ(result->contents[0], 129834691);
  ASSERT_EQ(result->contents[1], 234671264);
  ASSERT_EQ(result->contents[2], 213672349);
  ASSERT_EQ(result->contents[3], 124520285);
  ASSERT_EQ(result->contents[4], 671444873);
  ASSERT_EQ(result->contents[5], 111399252);
  ASSERT_EQ(result->contents[6], 434418321);
  ASSERT_EQ(result->contents[7], 346166999);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}