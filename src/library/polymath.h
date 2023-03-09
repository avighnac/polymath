#ifndef _polymath_h_
#define _polymath_h_

struct plm_number {
  int sign, number_of_decimal_digits;

  // The number is stored as a vector of unsigned long longs.
  unsigned long long *contents;
  unsigned long long contents_length;
};

struct plm_number plm_from_int(int n);
struct plm_number plm_from_long(long n);
struct plm_number plm_from_long_long(long long n);
struct plm_number plm_from_unsigned_long_long(unsigned long long n);
struct plm_number plm_from_string(const char *n);

void plm_free(struct plm_number *n);

#endif