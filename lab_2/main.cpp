

#include <iostream>

#include "src/hex.h"

int main(int argc, char **argv) {
    const auto h2 = ::hex::Hex();
    const auto h1 = ::hex::Hex("11010");
    std::cout << (h1 + h2).get_value();
}
