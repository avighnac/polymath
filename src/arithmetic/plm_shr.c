#include <polymath.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

struct plm_number *plm_shr(struct plm_number *x, uint64_t y) {
  if (!x) {
    return NULL;
  }
  if (y < 0) {
    return plm_shl(x, -y);
  }
  // todo!!!
  assert(0);
}
