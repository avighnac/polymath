#include <polymath.h>
#include <stdlib.h>

// Function: plm_from_unsigned_long_long
//   Converts an unsigned long long to a polymath number.
//
// Parameters:
//   n - The unsigned long long to convert.
//
// Returns:
//   struct plm_number - The polymath number.
struct plm_number plm_from_unsigned_long_long(unsigned long long n) {
  struct plm_number num;

  num.sign = 1;
  num.number_of_decimal_digits = 0;

  // Create space for one unsigned long long.
  num.contents = (unsigned long long *)malloc(sizeof(unsigned long long));

  // Set the value.
  num.contents[0] = (unsigned long long)n;
  num.contents_length = 1;

  return num;
}