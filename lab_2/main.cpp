#include <iostream>

#include "src/hex.h"

int main(int argc, char **argv) {
    std::string v1, v2;

    std::cout << "Enter first number" << std::endl;
    std::cin >> v1;
    std::cout << "Enter second number" << std::endl;
    std::cin >> v2;

    auto h1 = ::hex::Hex(v1);
    const auto h2 = ::hex::Hex(v2);

    std::cout << (h1 + h2).get_value();
}
