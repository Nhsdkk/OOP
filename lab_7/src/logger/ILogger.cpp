//
// Created by nikit on 11/29/2024.
//

#include "ILogger.h"

namespace Logger {
    bool ILogger::operator==(const ILogger &other) const {
        return name == other.name;
    }

    ILogger &ILogger::operator<<(std::ostream &(*fun)(std::ostream &)) {
        std::shared_lock lock(sharedMutex);
        os << std::endl;
        return *this;
    }

    void ILogger::log(const std::string &data) const {
        std::shared_lock lock(sharedMutex);
        getOstream() << data << std::endl;
    }
} // ILogger