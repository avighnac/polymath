#include <polymath.h>
#include <stddef.h>
#include <stdlib.h>

#define ull unsigned long long

// Function: plm_subtract_whole
// Subtracts two whole numbers
// Parameters:
//  a - The first number to subtract
//  b - The second number to subtract
// Returns:
//  A pointer to a new <struct plm_number> containing the result of the
//  subtraction or NULL if the numbers are not whole numbers / are NULL / are
//  negative
struct plm_number *plm_subtract_whole(struct plm_number *a,
                                      struct plm_number *b) {
  if (a == NULL || b == NULL || a->number_of_decimal_digits ||
      b->number_of_decimal_digits || a->sign || b->sign)
    return NULL;

  // We immediately know a < b, so do b - a and negate the result
  if (b->contents_length > a->contents_length) {
    struct plm_number *ans = plm_subtract_whole(b, a);
    ans->sign = 1;
    return ans;
  }

  // Allocate a new number to hold the result.
  ull result_contents_length = (a->contents_length);
  struct plm_number *result = malloc(sizeof(struct plm_number));
  result->contents = malloc(sizeof(long long) * result_contents_length);
  result->contents_length = result_contents_length;
  result->number_of_decimal_digits = 0;
  result->sign = 0;

  // If the allocation failed, return NULL
  if (result == NULL)
    return NULL;

  size_t a_index = a->contents_length - 1;
  size_t b_index = b->contents_length - 1;
  size_t result_index = result_contents_length - 1;
  long long carry = 0;

  // First perform subtraction for the common parts
  for (ull i = 0; i < b->contents_length;
       ++i, --a_index, --b_index, --result_index) {
    result->contents[result_index] =
        a->contents[a_index] - b->contents[b_index] + carry;

    if (result->contents[result_index] < 0 && a_index != 0) {
      carry = -1;
      result->contents[result_index] += 1000000000LL;
    } else {
      carry = 0;
    }
  }

  // Do the remaning digits
  for (ull i = 0; i < a->contents_length - b->contents_length;
       ++i, --a_index, --b_index, --result_index) {
    result->contents[result_index] = a->contents[a_index] + carry;

    if (result->contents[result_index] < 0 && a_index != 0) {
      carry = -1;
      result->contents[result_index] += 1000000000LL;
    } else {
      carry = 0;
    }
  }

  if (result->contents[0] >= 0) {
    return result;
  }

  result->sign = 1;
  for (ull i = result->contents_length - 1; i + 1 > 0; --i) {
    result->contents[i] = -result->contents[i] + carry;
    if (result->contents[i] < 0) {
      carry = -1;
      result->contents[i] += 1000000000LL;
    } else {
      carry = 0;
    }
  }
  return result;
}
