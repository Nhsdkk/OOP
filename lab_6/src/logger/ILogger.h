//
// Created by nikit on 11/29/2024.
//

#ifndef OOP_LAB_6_SRC_LOGGER_H_
#define OOP_LAB_6_SRC_LOGGER_H_

#include <string>
#include <stdexcept>
#include <utility>
#include <iostream>
namespace Logger {

class ILogger {
    std::string name;
    std::ostream& os;

    protected:
        std::ostream& getOstream() const { return os; }

    public:
        ILogger() : name("Logger"), os(std::cout) {}
        explicit ILogger(std::string name, std::ostream& ostream) : name(std::move(name)), os(ostream){}
        virtual void log(const std::string& data) const = 0;

        std::string getName() const { return name; }

        bool operator==(const ILogger& other) const {
            return name == other.name;
        }

        template<class T>
        ILogger& operator<<(const T& data){
            os << data;
            return *this;
        }

        ILogger& operator<<(std::ostream& (*fun)(std::ostream&)) {
            os << std::endl;
            return *this;
        }

        virtual ~ILogger() = default;

};

} // ILogger

#endif //OOP_LAB_6_SRC_LOGGER_H_
