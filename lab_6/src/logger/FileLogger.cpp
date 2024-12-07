//
// Created by nikit on 11/29/2024.
//

#include "FileLogger.h"

namespace Logger {
    void FileLogger::log(const std::string &str) const {
        getOstream() << str << std::endl;
    }
} // ILogger