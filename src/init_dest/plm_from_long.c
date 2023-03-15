#include <polymath.h>
#include <stdlib.h>

// Function: plm_from_long
//   Converts a long to a polymath number.
//
// Parameters:
//   n - The long to convert.
//
// Returns:
//   struct plm_number - The polymath number.
struct plm_number *plm_from_long(long n) {
  struct plm_number *num = malloc(sizeof(struct plm_number));

  num->sign = 0;
  num->number_of_decimal_digits = 0;

  if (n < 0) {
    num->sign = 1;
    n = -n;
  }

  // Create space for one unsigned long long.
  num->contents = (unsigned long long *)malloc(sizeof(unsigned long long));

  // Set the value.
  num->contents[0] = (unsigned long long)n;
  num->contents_length = 1;

  return num;
}