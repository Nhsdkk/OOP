//
// Created by nikit on 11/29/2024.
//

#include "ConsoleLogger.h"

namespace Logger {
    void ConsoleLogger::log(const std::string &str) const {
        getOstream() << str << std::endl;
    }
} // ILogger