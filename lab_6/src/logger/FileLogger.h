//
// Created by nikit on 11/29/2024.
//

#ifndef OOP_LAB_6_SRC_FILELOGGER_H_
#define OOP_LAB_6_SRC_FILELOGGER_H_

#include <fstream>
#include <utility>
#include "ILogger.h"
namespace Logger {

    class FileLogger : public ILogger {
        std::string filename;

        public:
            FileLogger() : ILogger(), filename("logs.txt") {}
            FileLogger(std::string  filename, std::string name) : ILogger(std::move(name)), filename(std::move(filename)) {}
            void log(const std::string& str) const override {
                std::ofstream file;
                file.open(filename, std::ios_base::app);
                if (!file.good()) throw std::invalid_argument("Can't load current state, because file can't be opened");

                file << str << std::endl;
                file.close();
            }

    };

} // ILogger

#endif //OOP_LAB_6_SRC_FILELOGGER_H_
