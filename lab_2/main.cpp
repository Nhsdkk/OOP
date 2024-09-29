#include <iostream>

#include "src/hex.h"

int main(int argc, char **argv) {
    const auto h2 = ::hex::Hex("101");
    ::hex::Hex h1 = ::hex::Hex("103");
    std::cout << (h1 + h2).get_value();
}
