#include <polymath.h>
#include <stddef.h>

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

  // TODO: Implement.
}