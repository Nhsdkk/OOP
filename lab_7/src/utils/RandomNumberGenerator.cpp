//
// Created by nikit on 12/7/2024.
//

#include "RandomNumberGenerator.h"

namespace Utils {
    int RandomNumberGenerator::generateInt(int min, int max) {
        std::uniform_int_distribution<int> distribution(min,max);
        return distribution(rng);
    }
} // Utils