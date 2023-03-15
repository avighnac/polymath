#include <polymath.h>
#include <stdlib.h>

// Function: plm_free
//   Frees the memory allocated to a polymath number.
//
// Parameters:
//   n - The polymath number to free.
//
// Returns:
//   Nothing.
void plm_free(struct plm_number *n) {
  free(n->contents);
  free(n);
}