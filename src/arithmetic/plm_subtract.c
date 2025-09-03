#include <polymath.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

struct plm_number *plm_subtract(struct plm_number *a, struct plm_number *b) {
  if (a == NULL || b == NULL) {
    return NULL;
  }

  if (a->sign && b->sign) {
    // (-a) - (-b) = b - a
    a->sign = 0, b->sign = 0;
    struct plm_number *ans = plm_subtract(b, a);
    a->sign = 1, b->sign = 1;
    return ans;
  }
  if (a->sign) {
    // (-a) - (+b) = -(a + b)
    a->sign = 0;
    struct plm_number *ans = plm_add(a, b);
    a->sign = 1;
    ans->sign = 1;
    return ans;
  }
  if (b->sign) {
    // (+a) - (-b) = a + b
    b->sign = 0;
    struct plm_number *ans = plm_add(a, b);
    b->sign = 1;
    return ans;
  }

  if (!a->number_of_decimal_digits && !b->number_of_decimal_digits) {
    return plm_subtract_whole(a, b);
  }

  uint64_t a_dd = a->number_of_decimal_digits, b_dd = b->number_of_decimal_digits;
  uint64_t shift = b_dd > a_dd ? b_dd : a_dd;
  struct plm_number *_a = plm_shl(a, shift);
  struct plm_number *_b = plm_shl(b, shift);
  struct plm_number *ans = plm_subtract_whole(_a, _b);
  ans->number_of_decimal_digits = shift;
  struct plm_number *_ans = plm_rtz(ans);
  if (_ans->contents_length == 1 && _ans->contents[0] == 0) {
    _ans->sign = 0;
  }
  plm_free(_a);
  plm_free(_b);
  plm_free(ans);
  return _ans;
}
