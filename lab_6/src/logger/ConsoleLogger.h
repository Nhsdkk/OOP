//
// Created by nikit on 11/29/2024.
//

#ifndef OOP_LAB_6_SRC_CONSOLELOGGER_H_
#define OOP_LAB_6_SRC_CONSOLELOGGER_H_

#include <iostream>
#include "ILogger.h"
namespace Logger {
    class ConsoleLogger : public ILogger {
        std::ostream& os;
        public:
            ConsoleLogger() : os(std::cout) {};
            explicit ConsoleLogger(std::ostream& ostr, std::string name) : ILogger(std::move(name)), os(ostr) {};
            void log(const std::string& str) const override {
                os << str << std::endl;
            }
    };

} // ILogger

#endif //OOP_LAB_6_SRC_CONSOLELOGGER_H_
