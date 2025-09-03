#include <polymath.h>

// Returns -1 if `a < b`, 0 if `a == b` and 1 if `a > b`.
int plm_compare_whole(const struct plm_number *a, const struct plm_number *b) {
  if (a->sign != b->sign) {
    return a->sign ? -1 : 1;
  }
  int is_negative = a->sign;
  if (a->contents_length > b->contents_length) {
    return is_negative ? -1 : 1;
  } else if (a->contents_length < b->contents_length) {
    return is_negative ? 1 : -1;
  }
  for (unsigned long long i = 0; i < a->contents_length; ++i) {
    if (a->contents[i] > b->contents[i]) {
      return is_negative ? -1 : 1;
    } else if (a->contents[i] < b->contents[i]) {
      return is_negative ? 1 : -1;
    }
  }
  return 0;
}
