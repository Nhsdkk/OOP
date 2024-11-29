//
// Created by nikit on 11/29/2024.
//

#ifndef OOP_LAB_6_SRC_LOGGER_H_
#define OOP_LAB_6_SRC_LOGGER_H_

#include <string>
#include <stdexcept>
namespace Logger {

class ILogger {
    public:
        ILogger() {}
        //TODO: Use custom exception
        virtual void log(const std::string& data) const { throw std::invalid_argument("Can't use logger interface"); }


};

} // ILogger

#endif //OOP_LAB_6_SRC_LOGGER_H_
