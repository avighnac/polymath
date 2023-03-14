#include <polymath.h>
#include <stdlib.h>
#include <string.h>

// Function: plm_from_base10_string
//   Creates a polymath number from a base 10 string.
//
// Parameters:
//   n - The string to convert.
//
// Returns:
//   A polymath number.
struct plm_number plm_from_base10_string(const char *n_in) {
  if (*n_in == '\0') {
    return plm_from_int(0);
  }

  // Copy the string, so that we can modify it.
  char *n = malloc(strlen(n_in) + 1);
  strcpy(n, n_in);

  // Remove leading zeroes.
  char *s_c = n;
  while (*s_c == '0') {
    ++s_c;
  }

  // Edge case: "00000"
  if (*s_c == 0) {
    return plm_from_int(0);
  }

  // Edge case: "000.1672"
  // i.e. whole part is 0
  if (*s_c == '.') {
    --s_c;
  }

  memmove(n, s_c, strlen(s_c) + 1);

  if (strchr(s_c, '.') != NULL) {
    // Remove trailing zeroes.
    s_c = n + strlen(n) - 1;

    while (*s_c == '0') {
      --s_c;
    }

    // Edge case: "1672.00000"
    // i.e. decimal part is 0
    if (*s_c == '.') {
      --s_c;
    }

    *(s_c + 1) = '\0';
  }

  // Declare the number, along with its default values.
  struct plm_number number;
  number.sign = 0;
  number.number_of_decimal_digits = 0;
  number.contents_length = 0;

  // Check for decimal digits.
  char *location_of_decimal_point = strchr(n, '.');
  if (location_of_decimal_point != NULL) {
    number.number_of_decimal_digits =
        strlen(n) - (location_of_decimal_point - n) - 1;
    // Remove decimal point
    memmove(location_of_decimal_point, location_of_decimal_point + 1,
            strlen(location_of_decimal_point));
  }

  // Deal with negative inputs.
  if (*n == '-') {
    number.sign = 1;
    memmove(n, n + 1, strlen(n));
  }

  // If the number is less than 20 characters, treat it like an unsigned
  // long long.
  if (strlen(n) < 20) {
    number.contents_length = 1;
    number.contents = malloc(sizeof(unsigned long long));
    number.contents[0] = strtoull(n, NULL, 10);
    free(n);
    return number;
  }

  // Partition into parts with 19 characters starting from the back.
  unsigned long long mod = strlen(n) % 19;
  unsigned long long number_parts = strlen(n) / 19;

  if (!mod) {
    number.contents_length = number_parts;
    number.contents = malloc(sizeof(unsigned long long) * number_parts);
    for (unsigned long long i = 0; i < number_parts; ++i) {
      // Let's hackily set the last character to \0, so that strtoull doesn't
      // convert the entire thing.
      char temp = n[19 * (i + 1)];
      n[19 * (i + 1)] = '\0';
      number.contents[i] = strtoull(n + i * 19, NULL, 10);
      n[19 * (i + 1)] = temp;
    }
    free(n);
    return number;
  }

  number.contents_length = number_parts + 1;
  number.contents = malloc(sizeof(unsigned long long) * (number_parts + 1));

  // First part
  char temp = n[mod];
  n[mod] = '\0';
  number.contents[0] = strtoull(n, NULL, 10);
  n[mod] = temp;

  // Note that the number of parts has technically increased by one.
  // But I haven't increased the variable number_parts, just to make the loop
  // more efficient.
  for (unsigned long long i = 0; i < number_parts; ++i) {
    temp = n[mod + 19 * (i + 1)];
    n[mod + 19 * (i + 1)] = '\0';
    number.contents[i + 1] = strtoull(n + mod + i * 19, NULL, 10);
    n[mod + 19 * (i + 1)] = temp;
  }

  free(n);
  return number;
}