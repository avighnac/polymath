#include <math.h>
#include <polymath.h>
#include <stdlib.h>
#include <string.h>

#define ull unsigned long long

char *plm_to_base10_string(struct plm_number *n) {
  if (!n->contents_length || (n->contents_length == 1 && n->contents[0] == 0)) {
    char *str = (char *)malloc(2);
    str[0] = '0';
    str[1] = '\0';
    return str;
  }

  // Calculate the number of digits in the number.
  size_t len_all_digits_combined =
      floor(1 + log10(n->contents[0])) + 9 * (n->contents_length - 1);
  size_t buffer_len = len_all_digits_combined + n->sign +
                      (n->number_of_decimal_digits > 0) +
                      (n->number_of_decimal_digits == len_all_digits_combined);
  char *str = (char *)malloc(buffer_len + 1);
  size_t ptr = buffer_len - 1;

  size_t temp = 0;
  // Deal with the sign.
  if (n->sign) {
    str[temp++] = '-';
  }

  // Edge case: "0.[digits]" will become ".[digits]" instead.
  // Example: 0.125 --> .125
  if (n->number_of_decimal_digits == len_all_digits_combined) {
    str[temp++] = '0';
  }

  // Deal with the decimal digits.
  ull decimal_parts =
      n->number_of_decimal_digits / 9 + (n->number_of_decimal_digits % 9 > 0);
  ull decimal_digits = n->number_of_decimal_digits;
  long long part = 0;
  ull part_i = 0;
  int count = 0;
  for (ull i = 0; i < decimal_parts; ++i) {
    count = 0;
    part_i = n->contents_length - i - 1;
    part = n->contents[part_i];
    if (part_i) {
      while (count < 9 && decimal_digits--) {
        str[ptr--] = '0' + part % 10;
        part /= 10;
        ++count;
      }
    } else {
      while (decimal_digits--) {
        str[ptr--] = '0' + part % 10;
        part /= 10;
        ++count;
      }
    }
  }

  // Now add the decimal point if necessary.
  if (n->number_of_decimal_digits > 0) {
    str[ptr--] = '.';
  }

  // Deal with the remaining digits of the remaining part.
  if (decimal_parts) {
    if (!part_i) {
      while (part) {
        str[ptr--] = '0' + part % 10;
        part /= 10;
      }
    } else {
      for (int i = 0; i < 9 - count; ++i) {
        str[ptr--] = '0' + part % 10;
        part /= 10;
      }
    }
  }

  // Add the rest of the digits.
  for (ull i = decimal_parts; i < n->contents_length; i++) {
    ull index = n->contents_length - i - 1;
    part = n->contents[index];
    if (index) {
      for (int i = 0; i < 9; ++i) {
        str[ptr--] = '0' + part % 10;
        part /= 10;
      }
    } else {
      while (part) {
        str[ptr--] = '0' + part % 10;
        part /= 10;
      }
    }
  }

  // Add the null terminator.
  str[buffer_len] = '\0';

  return str;
}
