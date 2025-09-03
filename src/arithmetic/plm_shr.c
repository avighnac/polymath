#include <polymath.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

struct plm_number *plm_shr(struct plm_number *x, long long y) {
  if (!x) {
    return NULL;
  }
  if (y < 0) {
    return plm_shl(x, -y);
  }
  // todo!!!
  assert(0);
}
