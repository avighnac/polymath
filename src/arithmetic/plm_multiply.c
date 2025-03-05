#include <polymath.h>
#include <stddef.h>
#include <stdlib.h>

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
  a->number_of_decimal_digits = 0, b->number_of_decimal_digits = 0;
  struct plm_number *ans = plm_multiply_whole(a, b);
  a->number_of_decimal_digits = a_dd;
  b->number_of_decimal_digits = b_dd;
  if (!ans) {
    return ans;
  }
  ans->number_of_decimal_digits = a_dd + b_dd;
  return ans;
}
