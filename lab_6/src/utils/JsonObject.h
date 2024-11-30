//
// Created by Anton on 11/30/2024.
//

#ifndef OOP_LAB_6_SRC_UTILS_JSONOBJECT_H_
#define OOP_LAB_6_SRC_UTILS_JSONOBJECT_H_

#include <string>
#include <map>
#include <optional>

namespace Json {

enum JsonType {
  Map,
  String
};

class JsonObject {
    std::optional<std::string> valueString;
    std::optional<std::map<std::string, JsonObject>> valueMap;
    JsonType type;


    public:
        JsonObject() : valueString(std::nullopt), valueMap(std::nullopt) {}
        JsonObject(const std::string &str, const std::shared_ptr<size_t>& currentIdx);

        std::string getValue() const {
            if (valueString.has_value()) return valueString.value();
            throw std::invalid_argument("Null dereference");
        }

        std::map<std::string, JsonObject> getObject() const {
            if (valueMap.has_value()) return valueMap.value();
            throw std::invalid_argument("Null dereference");
        }

        JsonType getType() const { return type; }
};

} // Json

#endif //OOP_LAB_6_SRC_UTILS_JSONOBJECT_H_
