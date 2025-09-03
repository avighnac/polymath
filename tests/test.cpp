#include <iostream>
#include <polymath.hpp>

using decimal_t = polymath::decimal;

int main() {
  decimal_t a = "0.2";
  a <<= 2;
  std::cout << a << '\n';
}