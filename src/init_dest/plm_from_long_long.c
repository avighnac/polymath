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

  if (n <= 999999999) {
    num->contents = (long long *)malloc(sizeof(long long));
    num->contents_length = 1;
    num->contents[0] = (long long)n;
  } else if (n <= 999999999999999999) {
    num->contents = (long long *)malloc(sizeof(long long) * 2);
    num->contents_length = 2;
    num->contents[1] = (long long)(n % 1000000000);
    num->contents[0] = (long long)(n / 1000000000);
  } else {
    num->contents = (long long *)malloc(sizeof(long long) * 3);
    num->contents_length = 3;
    num->contents[2] = (long long)(n % 1000000000);
    n /= 1000000000;
    num->contents[1] = (long long)(n % 1000000000);
    num->contents[0] = (long long)(n / 1000000000); 
  }

  return num;
}
