#ifndef _plm_from_int_h_
#define _plm_from_int_h_

#include <polymath.h>
#include <stdlib.h>

// Function: plm_from_int
//   Converts an integer to a polymath number.
//
// Parameters:
//   n - The integer to convert.
//
// Returns:
//   struct plm_number - The polymath number.
struct plm_number plm_from_int(int n) {
  struct plm_number num;

  num.sign = 1;
  num.number_of_decimal_digits = 0;

  if (n < 0) {
    num.sign = 0;
    n = -n;
  }

  // Create space for one unsigned long long.
  num.contents = (unsigned long long *)malloc(sizeof(unsigned long long));

  // Set the value.
  num.contents[0] = (unsigned long long)n;
  num.contents_length = 1;

  return num;
}

// Function: plm_from_long
//   Converts a long to a polymath number.
//
// Parameters:
//   n - The long to convert.
//
// Returns:
//   struct plm_number - The polymath number.
struct plm_number plm_from_long(long n) {
  struct plm_number num;

  num.sign = 1;
  num.number_of_decimal_digits = 0;

  if (n < 0) {
    num.sign = 0;
    n = -n;
  }

  // Create space for one unsigned long long.
  num.contents = (unsigned long long *)malloc(sizeof(unsigned long long));

  // Set the value.
  num.contents[0] = (unsigned long long)n;
  num.contents_length = 1;

  return num;
}


// Function: plm_from_long_long
//   Converts a long long to a polymath number.
//
// Parameters:
//   n - The long long to convert.
//
// Returns:
//   struct plm_number - The polymath number.
struct plm_number plm_from_long_long(long long n) {
  struct plm_number num;

  num.sign = 1;
  num.number_of_decimal_digits = 0;

  if (n < 0) {
    num.sign = 0;
    n = -n;
  }

  // Create space for one unsigned long long.
  num.contents = (unsigned long long *)malloc(sizeof(unsigned long long));

  // Set the value.
  num.contents[0] = (unsigned long long)n;
  num.contents_length = 1;

  return num;
}

// Function: plm_from_unsigned_long_long
//   Converts an unsigned long long to a polymath number.
//
// Parameters:
//   n - The unsigned long long to convert.
//
// Returns:
//   struct plm_number - The polymath number.
struct plm_number plm_from_unsigned_long_long(unsigned long long n) {
  struct plm_number num;

  num.sign = 1;
  num.number_of_decimal_digits = 0;

  // Create space for one unsigned long long.
  num.contents = (unsigned long long *)malloc(sizeof(unsigned long long));

  // Set the value.
  num.contents[0] = (unsigned long long)n;
  num.contents_length = 1;

  return num;
}


#endif