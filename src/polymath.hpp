#pragma once

#include <ostream>
#include <polymath.h>
#include <string>

namespace polymath {
class integer {
private:
  plm_number *_x;

  integer() : _x(nullptr) {}

public:
  integer(int n) { _x = plm_from_int(n); }
  integer(long n) { _x = plm_from_long(n); }
  integer(long long n) { _x = plm_from_long_long(n); }
  integer(unsigned long long n) { _x = plm_from_unsigned_long_long(n); }
  integer(const char *n) { _x = plm_from_base10_string(n); }
  integer(const std::string &n) { _x = plm_from_base10_string(n.c_str()); }
  integer(const integer &x) { _x = plm_from_plm(x._x); }
  integer(integer &&x) noexcept : _x(x._x) { x._x = nullptr; }

  ~integer() { plm_free(_x); }

  integer &operator=(const integer &other) {
    if (this != &other) {
      plm_free(_x);
      _x = plm_from_plm(other._x);
    }
    return *this;
  }
  integer &operator=(integer &&other) {
    std::swap(_x, other._x);
    return *this;
  }

  integer operator+(const integer &other) const {
    integer ans;
    ans._x = plm_add_whole(_x, other._x);
    return ans;
  }
  integer operator*(const integer &other) const {
    integer ans;
    ans._x = plm_multiply_whole(_x, other._x);
    return ans;
  }

  integer &operator+=(const integer &other) {
    plm_number *temp = plm_add_whole(_x, other._x);
    plm_free(_x);
    _x = temp;
    return *this;
  }
  integer &operator*=(const integer &other) {
    plm_number *temp = plm_multiply_whole(_x, other._x);
    plm_free(_x);
    _x = temp;
    return *this;
  }

  integer &operator++() {
    *this += integer(1);
    return *this;
  }
  integer operator++(int) {
    integer old = *this;
    ++(*this);
    return old;
  }

  friend std::ostream &operator<<(std::ostream &os, const integer &x) {
    char *s = plm_to_base10_string(x._x);
    os << s;
    free(s);
    return os;
  }
};

class decimal {
private:
  plm_number *_x;

  decimal() : _x(nullptr) {}

public:
  decimal(int n) { _x = plm_from_int(n); }
  decimal(long n) { _x = plm_from_long(n); }
  decimal(long long n) { _x = plm_from_long_long(n); }
  decimal(unsigned long long n) { _x = plm_from_unsigned_long_long(n); }
  decimal(const char *n) { _x = plm_from_base10_string(n); }
  decimal(const std::string &n) { _x = plm_from_base10_string(n.c_str()); }
  decimal(const plm_number *n) { _x = plm_from_plm(n); }
  decimal(const decimal &x) { _x = plm_from_plm(x._x); }
  decimal(decimal &&x) noexcept : _x(x._x) { x._x = nullptr; }

  ~decimal() { plm_free(_x); }

  decimal &operator=(const decimal &other) {
    if (this != &other) {
      plm_free(_x);
      _x = plm_from_plm(other._x);
    }
    return *this;
  }
  decimal &operator=(decimal &&other) {
    std::swap(_x, other._x);
    return *this;
  }

  decimal operator+(const decimal &other) const {
    decimal ans;
    ans._x = plm_add(_x, other._x);
    return ans;
  }
  decimal operator*(const decimal &other) const {
    decimal ans;
    ans._x = plm_multiply(_x, other._x);
    return ans;
  }

  decimal &operator+=(const decimal &other) {
    plm_number *temp = plm_add(_x, other._x);
    plm_free(_x);
    _x = temp;
    return *this;
  }
  decimal &operator*=(const decimal &other) {
    plm_number *temp = plm_multiply(_x, other._x);
    plm_free(_x);
    _x = temp;
    return *this;
  }

  decimal &operator++() {
    *this += decimal(1);
    return *this;
  }
  decimal operator++(int) {
    decimal old = *this;
    ++(*this);
    return old;
  }

  friend std::ostream &operator<<(std::ostream &os, const decimal &x) {
    char *s = plm_to_base10_string(x._x);
    os << s;
    free(s);
    return os;
  }
};
} // namespace polymath