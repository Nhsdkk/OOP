//
// Created by Anton on 11/30/2024.
//

#ifndef OOP_LAB_6_SRC_UTILS_JSONOBJECT_H_
#define OOP_LAB_6_SRC_UTILS_JSONOBJECT_H_

#include <string>
#include <map>
#include <optional>

template<class T>
T getOrThrow(const std::string& strVal) {
    T data;
    std::stringstream iss(strVal);
    iss >> data;

    if (iss.fail()) throw std::invalid_argument("Failed to parse data");
    return data;
}

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
        JsonObject() : valueString(std::nullopt), valueMap(std::nullopt), type(String) {}
        JsonObject(const std::string &str, const std::shared_ptr<size_t>& currentIdx);
        JsonObject(const JsonObject& other) = default;
        JsonObject(JsonObject&& other) noexcept = default;

        JsonObject& operator=(const JsonObject& other) = default;
        JsonObject& operator=(JsonObject&& other) noexcept;

        template<class T>
        T getValue() const {
            if (valueString.has_value()) return getOrThrow<T>(valueString.value());
            throw std::invalid_argument("Null dereference");
        }
        std::map<std::string, JsonObject> getObject() const;
        JsonType getType() const { return type; }

        ~JsonObject() = default;
};

} // Json

#endif //OOP_LAB_6_SRC_UTILS_JSONOBJECT_H_
