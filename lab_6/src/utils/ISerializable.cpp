//
// Created by nikit on 11/24/2024.
//

#include "ISerializable.h"

namespace Utils {
    std::string read(std::istream &file) {
        std::string buff;
        std::string result;

        while (std::getline(file, buff))
            result += buff + '\n';

        return result;
    }
} // Utils