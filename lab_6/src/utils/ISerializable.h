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

namespace Utils {
    const std::regex valRegex("=\\S*");
    const std::regex fieldNameRegex("\\S*=");
    const std::regex objectRegex("\\S*=");
    //const std::regex objectRegex("\={([\s\S]*)\}\n");

    template<class T>
    T getOrThrow(const std::string& str) {
        T data;
        std::stringstream iss(str);
        iss >> data;

        if (iss.fail()) throw std::invalid_argument("Failed to parse data");
        return data;
    }

    std::optional<std::string> getValue(std::string& buffer){
        std::smatch match;
        std::regex_search(buffer, match, valRegex);
        if (match.size() == 0) return std::nullopt;
        auto res = match[0].str();
        return res.substr(1,res.size());
    }

    std::optional<std::string> getObject(std::string& buffer){
        std::smatch match;
        std::regex_search(buffer, match, objectRegex);
        if (match.size() == 0) return std::nullopt;
        auto res = match[0].str();
        return res.substr(1,res.size());
    }

    std::string getFieldName(std::string& buffer){
        std::smatch match;
        std::regex_search(buffer, match, fieldNameRegex);
        auto res = match[0].str();
        return res.substr(0,res.size() - 1);
    }

    std::map<std::string, std::string> toMap(const std::string& str){
        std::istringstream iss(str.substr(3, str.size() - 1));
        std::string buffer;

        std::getline(iss, buffer);
        std::map<std::string, std::string> values;

        while (!buffer.empty()){
            auto key = getFieldName(buffer);
            auto valueOpt = getObject(buffer);
            auto value = valueOpt.has_value() ? valueOpt.value() : getValue(buffer).value();
            values.emplace(key, value);
            std::getline(iss, buffer);
        }

        return values;
    }

    class ISerializable {
        public:
            ISerializable() = default;
            virtual std::string Serialize() const { return {}; };
            virtual void Deserialize(const std::string& value) { };
            virtual ~ISerializable() = default;
    };

} // Utils

#endif //OOP_LAB_6_SRC_ISERIALIZABLE_H_
