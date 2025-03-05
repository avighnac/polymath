#include <polymath.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

struct plm_number *plm_shl(struct plm_number *x, unsigned long long y) {
  if (!x) {
    return NULL;
  }
  if (y < 0) {
    return plm_shr(x, -y);
  }
  if (x->number_of_decimal_digits) {
    uint64_t x_dd = x->number_of_decimal_digits;
    uint64_t sub = x_dd < y ? x_dd : y;
    x->number_of_decimal_digits -= sub;
    struct plm_number *ans = plm_shl(x, y - sub);
    x->number_of_decimal_digits += sub;
    return ans;
  }
  if (y >= 9) {
    uint64_t add = y / 9;
    struct plm_number *ans = malloc(sizeof(struct plm_number));
    ans->sign = x->sign;
    ans->number_of_decimal_digits = 0;
    ans->contents_length = x->contents_length + add;
    ans->contents = malloc(sizeof(long long) * ans->contents_length);
    for (uint64_t i = 0; i < x->contents_length; ++i) {
      ans->contents[i] = x->contents[i];
    }
    for (uint64_t i = x->contents_length; i < ans->contents_length; ++i) {
      ans->contents[i] = 0;
    }
    struct plm_number *_ans = plm_shl(ans, y % 9);
    plm_free(ans);
    return _ans;
  }

  int pow = 1;
  for (uint64_t i = 0; i < y; ++i) {
    pow *= 10;
  }
  struct plm_number *_pow = plm_from_int(pow);
  struct plm_number *ans = plm_multiply_whole(x, _pow);
  plm_free(_pow);
  return ans;
}
