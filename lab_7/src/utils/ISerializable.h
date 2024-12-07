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
    std::string read(std::istream& file);

    class ISerializable {
        public:
            ISerializable() = default;
            virtual std::string serialize() const = 0;
            virtual void deserialize(const Json::JsonObject& jsonObject) = 0;
            virtual ~ISerializable() = default;
    };

} // Utils

#endif //OOP_LAB_6_SRC_ISERIALIZABLE_H_
