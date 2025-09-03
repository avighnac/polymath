#include <polymath.h>
#include <stdlib.h>
#include <string.h>

// Function: plm_from_plm
//   Copies an already existing polymath number.
//
// Parameters:
//   n - The polymath number to copy.
//
// Returns:
//   struct plm_number - An exact copy of the polymath number passed in.
struct plm_number *plm_from_plm(const struct plm_number *n) {
  struct plm_number *num = malloc(sizeof(struct plm_number));
  num->sign = n->sign;
  num->number_of_decimal_digits = n->number_of_decimal_digits;
  num->contents = malloc(n->contents_length * sizeof(long long));
  memcpy(num->contents, n->contents, n->contents_length * sizeof(long long));
  num->contents_length = n->contents_length;
  return num;
}