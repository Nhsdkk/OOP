//
// Created by nikit on 11/24/2024.
//

#ifndef OOP_LAB_6_SRC_ISERIALIZABLE_H_
#define OOP_LAB_6_SRC_ISERIALIZABLE_H_

#include <string>
#include <map>
#include <sstream>
#include <regex>
#include "optional"
#include "JsonObject.h"

namespace Utils {
    const std::regex valRegex("=\\S*");
    const std::regex fieldNameRegex("\\S*=");

    std::string read(std::istream& file){
        std::string buff;
        std::string result;

        while (std::getline(file, buff))
            result += buff + '\n';

        return result;
    }

    template<class T>
    T getOrThrow(const Json::JsonObject& obj) {
        if (obj.getType() != Json::String) throw std::invalid_argument("Can't convert object to value");
        T data;
        std::stringstream iss(obj.getValue());
        iss >> data;

        if (iss.fail()) throw std::invalid_argument("Failed to parse data");
        return data;
    }

    class ISerializable {
        public:
            ISerializable() = default;
            virtual std::string Serialize() const = 0;
            virtual void Deserialize(const Json::JsonObject& jsonObject) = 0;
            virtual ~ISerializable() = default;
    };

} // Utils

#endif //OOP_LAB_6_SRC_ISERIALIZABLE_H_
