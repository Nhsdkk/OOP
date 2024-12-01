//
// Created by nikit on 11/29/2024.
//

#include "FileLogger.h"

namespace Logger {
    void FileLogger::log(const std::string &str) const {
        std::ofstream file;
        file.open(filename, std::ios_base::app);
        if (!file.good()) throw std::invalid_argument("Can't load current state, because file can't be opened");

        file << str << std::endl;
        file.close();
    }

    FileLogger &FileLogger::operator=(FileLogger &&other) noexcept {
        filename = std::move(other.filename);
        return *this;
    }
} // ILogger