//
// Created by nikit on 9/8/2024.
//

#include "gcd.h"
#include <cmath>

int gcd(int a, int b) {
  a = abs(a);
  b = abs(b);

  while (a != 0 && b != 0){
    if (a > b) a %= b;
    else b %= a;
  }

  return a != 0 ? a : b;
}