#include <limits.h>
#include <polymath.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define ull unsigned long long

// Function: plm_add_whole
// Adds two whole numbers together
// Parameters:
//  a - The first number to add
//  b - The second number to add
// Returns:
//  A pointer to a new <struct plm_number> containing the result of the addition
//  or NULL if the numbers are not whole numbers / are NULL / are negative
struct plm_number *plm_add_whole(struct plm_number *a, struct plm_number *b) {
  if (a == NULL || b == NULL || a->number_of_decimal_digits ||
      b->number_of_decimal_digits || a->sign || b->sign)
    return NULL;

  // Make 'a' refer to the longer input
  if (b->contents_length > a->contents_length) {
    struct plm_number *temp = a;
    a = b;
    b = temp;
  }

  // Allocate a new number to hold the result.
  ull result_contents_length = (a->contents_length);
  struct plm_number *result = malloc(sizeof(struct plm_number));
  result->contents = malloc(sizeof(ull) * result_contents_length);
  result->contents_length = result_contents_length;
  result->number_of_decimal_digits = 0;
  result->sign = 0;

  // If the allocation failed, return NULL
  if (result == NULL)
    return NULL;

  size_t a_index = a->contents_length - 1;
  size_t b_index = b->contents_length - 1;
  size_t result_index = result_contents_length - 1;
  ull carry = 0;

  // First perform the addition for the common parts.
  for (ull i = 0; i < b->contents_length;
       ++i, --a_index, --b_index, --result_index) {
    result->contents[result_index] =
        a->contents[a_index] + b->contents[b_index] + carry;

    if (a->contents[a_index] > ULLONG_MAX - b->contents[b_index] - carry) {
      carry = 1;
      result->contents[result_index] -= 10000000000000000000ULL;
    } else {
      carry = 0;
    }

    if (result->contents[result_index] > 9999999999999999999ULL) {
      carry = 1;
      result->contents[result_index] -= 10000000000000000000ULL;
    }
  }

  // Now copy over the remaining digits taking carry into account.
  for (ull i = 0; i < a->contents_length - b->contents_length;
       ++i, --a_index, --b_index, --result_index) {
    result->contents[result_index] = a->contents[a_index] + carry;

    if (a->contents[a_index] > ULLONG_MAX - carry) {
      carry = 1;
      result->contents[result_index] -= 10000000000000000000ULL;
    } else {
      carry = 0;
    }

    if (result->contents[result_index] > 9999999999999999999ULL) {
      carry = 1;
      result->contents[result_index] -= 10000000000000000000ULL;
    }

    --a_index;
    --result_index;
  }

  // Check for a final carry, and also that we've not allocated too much / too
  // less.
  if (carry) {
    // It's realloc and memmove time!
    ++result->contents_length;
    result->contents =
        realloc(result->contents, result->contents_length * sizeof(ull));
    memmove(&result->contents[1], result->contents,
            (result->contents_length - 1) * sizeof(ull));
    result->contents[0] = carry;
  }

  return result;
}