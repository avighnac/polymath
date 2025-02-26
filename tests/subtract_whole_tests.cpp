#include <gtest/gtest.h>
extern "C" {
#include <polymath.h>
}

TEST(subtract_whole_tests, ten_minus_nine) {
  plm_number *a = plm_from_base10_string("10");
  plm_number *b = plm_from_base10_string("9");
  struct plm_number *result = plm_subtract_whole(a, b);
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->contents_length, 1);
  ASSERT_EQ(result->contents[0], 1);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}

TEST(subtract_whole_tests, nine_minus_ten) {
  plm_number *a = plm_from_base10_string("9");
  plm_number *b = plm_from_base10_string("10");
  struct plm_number *result = plm_subtract_whole(a, b);
  ASSERT_EQ(result->sign, 1);
  ASSERT_EQ(result->contents_length, 1);
  ASSERT_EQ(result->contents[0], 1);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}

TEST(subtract_whole_tests, big_test_1) {
  plm_number *a =
      plm_from_base10_string("1098470982730470198374908170934798217491");
  plm_number *b = plm_from_base10_string("129437927398479827394");
  struct plm_number *result = plm_subtract_whole(a, b);
  ASSERT_EQ(result->sign, 0);
  ASSERT_EQ(result->contents_length, 3);
  ASSERT_EQ(result->contents[0], 1098);
  ASSERT_EQ(result->contents[1], 470982730470198245);
  ASSERT_EQ(result->contents[2], 470243536318390097);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}

TEST(subtract_whole_tests, big_test_2) {
  plm_number *a = plm_from_base10_string("129437927398479827394");
  plm_number *b =
      plm_from_base10_string("1098470982730470198374908170934798217491");
  struct plm_number *result = plm_subtract_whole(a, b);
  ASSERT_EQ(result->sign, 1);
  ASSERT_EQ(result->contents_length, 3);
  ASSERT_EQ(result->contents[0], 1098);
  ASSERT_EQ(result->contents[1], 470982730470198245);
  ASSERT_EQ(result->contents[2], 470243536318390097);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}

TEST(subtract_whole_tests, big_test_3) {
  plm_number *a =
      plm_from_base10_string("78502734982317498079841273094872134980");
  plm_number *b =
      plm_from_base10_string("99999999999999999991923847981237049289");
  struct plm_number *result = plm_subtract_whole(a, b);
  ASSERT_EQ(result->sign, 1);
  ASSERT_EQ(result->contents_length, 3);
  ASSERT_EQ(result->contents[0], 21);
  ASSERT_EQ(result->contents[1], 497265017682501912);
  ASSERT_EQ(result->contents[2], 82574886364914309);
  ASSERT_EQ(result->number_of_decimal_digits, 0);
  plm_free(a);
  plm_free(b);
  plm_free(result);
}