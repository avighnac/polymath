#include <polymath.h>
#include <stddef.h>
#include <stdlib.h>

struct plm_number *plm_rtz(struct plm_number *x) {
  if (!x) {
    return NULL;
  }
  if (x->contents_length == 1 && x->contents[0] == 0) {
    struct plm_number *ans = malloc(sizeof(struct plm_number));
    ans->sign = 0;
    ans->number_of_decimal_digits = 0;
    ans->contents_length = 1;
    ans->contents = malloc(sizeof(long long));
    ans->contents[0] = 0;
    return ans;
  }

  uint64_t len = x->contents_length, pow = 1, decimals_removed = 0;
  for (int64_t i = (int64_t)len - 1, j = 0;
       i >= 0 && j < (x->number_of_decimal_digits + 8) / 9; --i, ++j) {
    if (x->contents[i] == 0) {
      len--;
      decimals_removed += 9;
      continue;
    }
    int64_t d = x->contents[i];
    while (d > 0 && d % 10 == 0) {
      pow *= 10;
      decimals_removed++;
      d /= 10;
    }
    break;
  }

  if (len == 1 && x->contents[0] / pow == 0) {
    struct plm_number *ans = malloc(sizeof(struct plm_number));
    ans->sign = 0;
    ans->number_of_decimal_digits = 0;
    ans->contents_length = 1;
    ans->contents = malloc(sizeof(long long));
    ans->contents[0] = 0;
    return ans;
  }

  int64_t ten_pow_9 = 1;
  for (int i = 0; i < 9; ++i) {
    ten_pow_9 *= 10;
  }

  uint64_t ans_len = len - (x->contents[0] / pow == 0);
  struct plm_number *ans = malloc(sizeof(struct plm_number));
  ans->sign = x->sign;
  ans->number_of_decimal_digits = x->number_of_decimal_digits - decimals_removed;
  ans->contents_length = ans_len;
  ans->contents = malloc(sizeof(long long) * ans_len);
  // shift each part by pow
  for (uint64_t i = len - 1; i > 0; --i) {
    ans->contents[ans_len - (len - i)] = (x->contents[i - 1] * ten_pow_9 + x->contents[i]) / pow;
  }
  if (x->contents[0] / pow != 0) {
    ans->contents[0] = x->contents[0] / pow;
  }
  return ans;
}