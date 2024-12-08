//
// Created by nikit on 11/29/2024.
//

#ifndef OOP_LAB_6_SRC_CONSOLELOGGER_H_
#define OOP_LAB_6_SRC_CONSOLELOGGER_H_

#include <iostream>
#include "ILogger.h"
namespace Logger {
    class ConsoleLogger : public ILogger {
        public:
            ConsoleLogger() : ILogger() {};
            ConsoleLogger(const ConsoleLogger& other) = default;
            ConsoleLogger(ConsoleLogger&& other) noexcept = default;
            ConsoleLogger& operator=(const ConsoleLogger& other) = delete;
            ConsoleLogger& operator=(ConsoleLogger&& other) noexcept = delete;
            explicit ConsoleLogger(std::ostream& ostream, std::string name) : ILogger(std::move(name), ostream){};
            ~ConsoleLogger() override = default;
    };

} // ILogger

#endif //OOP_LAB_6_SRC_CONSOLELOGGER_H_
