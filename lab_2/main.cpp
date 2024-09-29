#include <iostream>

#include "src/hex.h"

int main(int argc, char **argv) {
    auto h1 = ::hex::Hex("CD");
    const auto h2 = ::hex::Hex("AB");
    h1 -= h2;
    std::cout << h1.get_value();
}
