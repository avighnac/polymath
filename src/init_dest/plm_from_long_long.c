#include <polymath.h>
#include <stdlib.h>

// Function: plm_from_long_long
//   Converts a long long to a polymath number.
//
// Parameters:
//   n - The long long to convert.
//
// Returns:
//   struct plm_number - The polymath number.
struct plm_number *plm_from_long_long(long long n) {
  struct plm_number *num = malloc(sizeof(struct plm_number));

  num->sign = 0;
  num->number_of_decimal_digits = 0;

  if (n < 0) {
    num->sign = 1;
    n = -n;
  }

  // Create space for one long long.
  num->contents = (long long *)malloc(sizeof(long long));

  // Set the value.
  num->contents[0] = (long long)n;
  num->contents_length = 1;

  return num;
}
