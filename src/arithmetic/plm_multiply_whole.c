#include <polymath.h>
#include <stddef.h>
#include <stdlib.h>

struct plm_number *plm_multiply_whole(struct plm_number *a,
                                      struct plm_number *b) {
  if (a == NULL || b == NULL || a->number_of_decimal_digits ||
      b->number_of_decimal_digits || a->sign || b->sign)
    return NULL;

  // Allocate a new number to hold the result.
  uint64_t result_contents_length = a->contents_length + b->contents_length;
  struct plm_number *result = malloc(sizeof(struct plm_number));
  result->contents = malloc(sizeof(long long) * result_contents_length);
  result->contents_length = result_contents_length;
  result->number_of_decimal_digits = 0;
  result->sign = 0;

  // If the allocation failed, return NULL
  if (result == NULL)
    return NULL;

  for (uint64_t k = 0; k < result->contents_length; ++k) {
    for (uint64_t i = 0; i < a->contents_length; ++i) {
      if (k < i || k >= b->contents_length + i) {
        continue;
      }
      uint64_t res = a->contents[a->contents_length - i - 1] *
                     b->contents[b->contents_length - (k - i) - 1];
      result->contents[k] += res % 1000000000;
      if (k != result->contents_length - 1) {
        result->contents[k + 1] += res / 1000000000;
      }
    }
  }
  for (uint64_t k = 0, carry = 0; k < result->contents_length; ++k) {
    result->contents[k] += carry;
    carry = result->contents[k] / 1000000000;
    result->contents[k] %= 1000000000;
  }
  while (result->contents_length > 0 && result->contents[result->contents_length - 1] == 0) {
    result->contents_length--;
  }
  if (result_contents_length != result->contents_length) {
    result->contents = realloc(result->contents, sizeof(long long) * result->contents_length);
  }
  for (uint64_t i = 0; i < result->contents_length / 2; ++i) {
    long long t = result->contents[i];
    result->contents[i] = result->contents[result->contents_length - i - 1];
    result->contents[result->contents_length - i - 1] = t;
  }
  return result;
}
