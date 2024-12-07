//
// Created by nikit on 12/7/2024.
//

#ifndef OOP_LAB_7_SRC_UTILS_RANDOMNUMBERGENERATOR_H_
#define OOP_LAB_7_SRC_UTILS_RANDOMNUMBERGENERATOR_H_

#include <random>
namespace Utils {

    class RandomNumberGenerator {
        std::mt19937 rng;
        public:
            RandomNumberGenerator() : rng() {}
            explicit RandomNumberGenerator(std::random_device& rd) : rng(rd()) {}

            int generateInt(int min, int max);
    };

} // Utils

#endif //OOP_LAB_7_SRC_UTILS_RANDOMNUMBERGENERATOR_H_
