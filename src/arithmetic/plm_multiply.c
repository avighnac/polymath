#include <polymath.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

struct plm_number *plm_multiply(struct plm_number *a, struct plm_number *b) {
  if (a == NULL || b == NULL) {
    return NULL;
  }

  if (a->sign) {
    a->sign = 0;
    struct plm_number *ans = plm_multiply(a, b);
    a->sign = 1;
    if (!ans) {
      return ans;
    }
    ans->sign = !ans->sign;
    return ans;
  }
  if (b->sign) {
    b->sign = 0;
    struct plm_number *ans = plm_multiply(a, b);
    b->sign = 1;
    if (!ans) {
      return ans;
    }
    ans->sign = !ans->sign;
    return ans;
  }

  uint64_t a_dd = a->number_of_decimal_digits,
           b_dd = b->number_of_decimal_digits;
  uint64_t ans_dd = a_dd + b_dd;
  a->number_of_decimal_digits = 0, b->number_of_decimal_digits = 0;
  struct plm_number *ans = plm_multiply_whole(a, b);
  a->number_of_decimal_digits = a_dd;
  b->number_of_decimal_digits = b_dd;
  if (!ans) {
    return ans;
  }
  uint64_t expected_parts = (ans_dd / 9) + (ans_dd % 9 > 0);
  if (ans->contents_length < expected_parts) {
    uint64_t diff = expected_parts - ans->contents_length;
    ans->contents_length = expected_parts;
    ans->contents = realloc(ans->contents, expected_parts * sizeof(long long));
    for (uint64_t i = ans->contents_length - diff - 1; i + 1 > 0; --i) {
      ans->contents[i + diff] = ans->contents[i];
    }
    for (uint64_t i = 0; i < diff; ++i) {
      ans->contents[i] = 0;
    }
  }
  ans->number_of_decimal_digits = ans_dd;
  return ans;
}
