#include <iostream>

#include "./src/gcd.h"

int main() {
  int rval, lval;
  std::cin >> rval >> lval;
  std::cout << gcd(rval, lval) << std::endl;
}
