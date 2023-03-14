#ifndef _polymath_h_
#define _polymath_h_

struct plm_number {
  int sign; // 0 for positive, 1 for negative.
  unsigned long long number_of_decimal_digits;

  // The number is stored as a vector of unsigned long longs.
  unsigned long long *contents;
  unsigned long long contents_length;
};

struct plm_number plm_from_int(int n);
struct plm_number plm_from_long(long n);
struct plm_number plm_from_long_long(long long n);
struct plm_number plm_from_unsigned_long_long(unsigned long long n);
struct plm_number plm_from_base10_string(const char *n);

/// @brief Frees the memory allocated to a polymath number.
/// @param n The polymath number to free, passed as a pointer.
/// @return Nothing.
void plm_free(struct plm_number *n);

/// @brief Convert a polymath number to a base-10 string.
/// @param n The polymath number to convert, passed as a pointer.
/// @return A base-10 string representation of the polymath number. Free this
/// once you're done with it.
char *plm_to_base10_string(struct plm_number *n);

struct plm_number *plm_add_whole(struct plm_number *a, struct plm_number *b);

#endif