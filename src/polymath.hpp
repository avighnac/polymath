#pragma once

#include <concepts>
#include <ostream>
#include <polymath.h>
#include <string>
#include <type_traits>

namespace polymath {
class whole {
private:
  plm_number *_x;

  whole() : _x(nullptr) {}

public:
  template <std::unsigned_integral T>
  whole(T n) {
    _x = plm_from_unsigned_long_long(static_cast<unsigned long long>(n));
  }
  template <std::signed_integral T>
  whole(T) = delete;
  whole(const char *n) { _x = plm_from_base10_string(n); }
  whole(const std::string &n) { _x = plm_from_base10_string(n.c_str()); }
  whole(const whole &x) { _x = plm_from_plm(x._x); }
  whole(whole &&x) noexcept : _x(x._x) { x._x = nullptr; }

  ~whole() { plm_free(_x); }

  whole &operator=(const whole &other) {
    if (this != &other) {
      plm_free(_x);
      _x = plm_from_plm(other._x);
    }
    return *this;
  }
  whole &operator=(whole &&other) {
    std::swap(_x, other._x);
    return *this;
  }

  whole operator+(const whole &other) const {
    whole ans;
    ans._x = plm_add_whole(_x, other._x);
    return ans;
  }
  whole operator-(const whole &other) const {
    whole ans;
    ans._x = plm_subtract_whole(_x, other._x);
    return ans;
  }
  whole operator*(const whole &other) const {
    whole ans;
    ans._x = plm_multiply_whole(_x, other._x);
    return ans;
  }

  whole &operator+=(const whole &other) {
    plm_number *temp = plm_add_whole(_x, other._x);
    plm_free(_x);
    _x = temp;
    return *this;
  }
  whole &operator-=(const whole &other) {
    plm_number *temp = plm_subtract_whole(_x, other._x);
    plm_free(_x);
    _x = temp;
    return *this;
  }
  whole &operator*=(const whole &other) {
    plm_number *temp = plm_multiply_whole(_x, other._x);
    plm_free(_x);
    _x = temp;
    return *this;
  }

  bool operator==(const whole &other) const { return plm_compare_whole(_x, other._x) == 0; }
  bool operator<(const whole &other) const { return plm_compare_whole(_x, other._x) == -1; }
  bool operator!=(const whole &other) const { return !(*this == other); }
  bool operator>(const whole &other) const { return other < *this; }
  bool operator<=(const whole &other) const { return !(*this > other); }
  bool operator>=(const whole &other) const { return !(*this < other); }

  whole &operator++() {
    *this += whole(1u);
    return *this;
  }
  whole operator++(int) {
    whole old = *this;
    ++(*this);
    return old;
  }
  whole &operator--() {
    *this -= whole(1u);
    return *this;
  }
  whole operator--(int) {
    whole old = *this;
    --(*this);
    return old;
  }

  whole operator<<(long long y) {
    whole ans;
    ans._x = plm_shl(plm_from_plm(_x), y);
    return ans;
  }
  whole &operator<<=(long long y) {
    plm_number *tmp = plm_shl(_x, y);
    plm_free(_x);
    _x = tmp;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const whole &x) {
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
  decimal operator-(const decimal &other) const {
    decimal ans;
    ans._x = plm_subtract(_x, other._x);
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
  decimal &operator-=(const decimal &other) {
    plm_number *temp = plm_subtract(_x, other._x);
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
  decimal &operator--() {
    *this -= decimal(1);
    return *this;
  }
  decimal operator--(int) {
    decimal old = *this;
    --(*this);
    return old;
  }

  decimal operator<<(long long y) {
    decimal ans;
    ans._x = plm_shl(plm_from_plm(_x), y);
    return ans;
  }
  decimal &operator<<=(long long y) {
    plm_number *tmp = plm_shl(_x, y);
    plm_free(_x);
    _x = tmp;
    return *this;
  }
  decimal operator>>(long long y) {
    decimal ans;
    ans._x = plm_shr(plm_from_plm(_x), y);
    return ans;
  }
  decimal &operator>>=(long long y) {
    plm_number *tmp = plm_shr(_x, y);
    plm_free(_x);
    _x = tmp;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &os, const decimal &x) {
    char *s = plm_to_base10_string(x._x);
    os << s;
    free(s);
    return os;
  }
};
} // namespace polymath