#include <polymath.h>
#include <stddef.h>
#include <stdlib.h>

struct plm_number *plm_add(struct plm_number *a, struct plm_number *b) {
  if (a == NULL || b == NULL) {
    return NULL;
  }

  if (a->sign) {
    // -a + b ==> b - a
    a->sign = 0;
    struct plm_number *ans = plm_subtract(b, a);
    a->sign = 1;
    return ans;
  }
  if (b->sign) {
    // a + (-b) ==> a - b
    b->sign = 0;
    struct plm_number *ans = plm_subtract(a, b);
    b->sign = 1;
    return ans;
  }

  if (!a->number_of_decimal_digits && !b->number_of_decimal_digits) {
    return plm_add_whole(a, b);
  }

  uint64_t a_dd = a->number_of_decimal_digits, b_dd = b->number_of_decimal_digits;
  uint64_t shift = b_dd > a_dd ? b_dd : a_dd;
  struct plm_number *_a = plm_shl(a, shift);
  struct plm_number *_b = plm_shl(b, shift);
  struct plm_number *ans = plm_add_whole(_a, _b);
  ans->number_of_decimal_digits = shift;
  struct plm_number *_ans = plm_rtz(ans);
  plm_free(_a);
  plm_free(_b);
  plm_free(ans);
  return _ans;
}
