#include <iostream>
#include <polymath.hpp>

int main() {
  using int_t = polymath::integer;
  int_t a = 2;
  for (int i = 0; i < 20; ++i) {
    a *= a;
  }
  std::cout << a << std::endl;
}