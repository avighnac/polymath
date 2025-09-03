#ifndef _polymath_h_
#define _polymath_h_

#ifdef __cplusplus
extern "C" {
#endif

struct plm_number {
  int sign; // 0 for positive, 1 for negative.
  unsigned long long number_of_decimal_digits;

  // The number is stored as a vector of long longs.
  long long *contents;
  unsigned long long contents_length;
};

struct plm_number *plm_from_int(int n);
struct plm_number *plm_from_long(long n);
struct plm_number *plm_from_long_long(long long n);
struct plm_number *plm_from_unsigned_long_long(unsigned long long n);
struct plm_number *plm_from_base10_string(const char *n);
struct plm_number *plm_from_plm(const struct plm_number *n);

/// @brief Frees the memory allocated to a polymath number.
/// @param n The polymath number to free, passed as a pointer.
/// @return Nothing.
void plm_free(struct plm_number *n);

/// @brief Convert a polymath number to a base-10 string.
/// @param n The polymath number to convert, passed as a pointer.
/// @return A base-10 string representation of the polymath number. Free this
/// once you're done with it.
char *plm_to_base10_string(struct plm_number *n);

/// @brief Adds two whole polymath numbers and returns the result as a pointer
/// to a polymath number.
/// @param a The first polymath number to add.
/// @param b The second polymath number to add.
struct plm_number *plm_add_whole(struct plm_number *a, struct plm_number *b);

/// @brief Subtracts two whole polymath numbers and returns the result as a
/// pointer to a polymath number.
/// @param a The first polymath number to subtract.
/// @param b The second polymath number to subtract.
struct plm_number *plm_subtract_whole(struct plm_number *a,
                                      struct plm_number *b);

/// @brief Multiplies two whole polymath numbers and returns the result as a
/// pointer to a polymath number.
/// @param a The first polymath number to multiply.
/// @param b The second polymath number to multiply.
struct plm_number *plm_multiply_whole(struct plm_number *a,
                                      struct plm_number *b);

/// @brief Adds two polymath numbers and returns the result as a pointer
/// to a polymath number.
/// @param a The first polymath number to add.
/// @param b The second polymath number to add.
struct plm_number *plm_add(struct plm_number *a, struct plm_number *b);

/// @brief Subtracts two polymath numbers and returns the result as a pointer
/// to a polymath number.
/// @param a The first polymath number to subtract.
/// @param b The second polymath number to subtract.
struct plm_number *plm_subtract(struct plm_number *a, struct plm_number *b);

/// @brief Multiplies two polymath numbers and returns the result as a
/// pointer to a polymath number.
/// @param a The first polymath number to multiply.
/// @param b The second polymath number to multiply.
struct plm_number *plm_multiply(struct plm_number *a, struct plm_number *b);

/// @brief Shifts `x` to the left in base 10 by `y` places. In other words, performs `x` ==> `x * 10^y`.
/// @param x Returns the shifted number.
struct plm_number *plm_shl(struct plm_number *x, long long y);

/// @brief Shifts `x` to the right in base 10 by `y` places. In other words, performs `x` ==> `floor(x / 10^y)`.
/// @param x Returns the shifted number.
struct plm_number *plm_shr(struct plm_number *x, long long y);

/// @brief Removes trailing zeroes from a polymath number: so, for example, `10.0` ==> `10`.
struct plm_number *plm_rtz(struct plm_number *x);

#ifdef __cplusplus
}
#endif

#endif
