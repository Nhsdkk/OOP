//
// Created by Anton on 11/30/2024.
//

#include <memory>
#include <sstream>
#include "JsonObject.h"

namespace Json {
    std::string DeserializeAsStringValue(const std::string &str, const std::shared_ptr<size_t>& currentIdx){
        std::string result;
        while(str[*currentIdx] != ';'){
            result += str[*currentIdx];
            ++(*currentIdx);
        }
        --(*currentIdx);
        return result;
    }

    JsonObject::JsonObject(const std::string &str, const std::shared_ptr<size_t>& currentIdx) {
        if (str[*currentIdx] != '{') {
            valueString = DeserializeAsStringValue(str, currentIdx);
            type = String;
            return;
        }

        ++(*currentIdx);

        std::string buffer;

        std::string keyBuffer;

        std::string valueBuffer;
        std::map<std::string, JsonObject> dict;


        while (str[*currentIdx] != '}'){
            if (str[*currentIdx] == '=') {
                keyBuffer = buffer;
                buffer.clear();
                ++(*currentIdx);
                auto val = JsonObject(str, currentIdx);
                dict.emplace(keyBuffer, val);
                *currentIdx += 2;
                continue;
            }

            buffer += str[*currentIdx];
            ++(*currentIdx);
        }

        valueMap = std::move(dict);
        type = Map;
    }

    std::map<std::string, JsonObject> JsonObject::getObject() const {
        if (valueMap.has_value()) return valueMap.value();
        throw std::invalid_argument("Null dereference");
    }

    JsonObject &JsonObject::operator=(JsonObject &&other) noexcept {
        type = other.type;
        valueString = std::move(valueString);
        valueMap = std::move(valueMap);
        return *this;
    }

} // Json