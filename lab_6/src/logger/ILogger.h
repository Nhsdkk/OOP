//
// Created by nikit on 11/29/2024.
//

#ifndef OOP_LAB_6_SRC_LOGGER_H_
#define OOP_LAB_6_SRC_LOGGER_H_

#include <string>
#include <stdexcept>
#include <utility>
namespace Logger {

class ILogger {
    std::string name;
    public:
        ILogger() : name("Logger") {}
        explicit ILogger(std::string  name) : name(std::move(name)) {}
        virtual void log(const std::string& data) const = 0;
        virtual ~ILogger() = default;

};

} // ILogger

#endif //OOP_LAB_6_SRC_LOGGER_H_
