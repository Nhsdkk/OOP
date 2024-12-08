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
        std::ofstream ofstream;

        public:
            FileLogger() : ILogger(), filename("logs.txt") {}
            FileLogger(const std::string& filename, std::string name) : ofstream(std::ofstream(filename, std::ios::app)), ILogger(std::move(name), ofstream), filename(filename) {}
            FileLogger(const FileLogger& other) = delete;
            FileLogger(FileLogger&& other) noexcept = delete;
            FileLogger& operator=(const FileLogger& other) = delete;
            FileLogger& operator=(FileLogger&& other) noexcept = delete;
            ~FileLogger() override = default;
    };

} // ILogger

#endif //OOP_LAB_6_SRC_FILELOGGER_H_
