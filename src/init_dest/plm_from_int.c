#include <polymath.h>
#include <stdlib.h>

// Function: plm_from_int
//   Converts an integer to a polymath number.
//
// Parameters:
//   n - The integer to convert.
//
// Returns:
//   struct plm_number - The polymath number.
struct plm_number *plm_from_int(int n) {
  struct plm_number *num = malloc(sizeof(struct plm_number));

  num->sign = 0;
  num->number_of_decimal_digits = 0;

  if (n < 0) {
    num->sign = 1;
    n = -n;
  }

  if (n <= 999999999) {
    num->contents = (long long *)malloc(sizeof(long long));
    num->contents_length = 1;
    num->contents[0] = (long long)n;
  } else {
    num->contents = (long long *)malloc(sizeof(long long) * 2);
    num->contents_length = 2;
    num->contents[0] = (long long)(n / 1000000000);
    num->contents[1] = (long long)(n % 1000000000);
  }

  return num;
}
