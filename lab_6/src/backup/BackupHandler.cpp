//
// Created by nikit on 11/24/2024.
//

#include "BackupHandler.h"

enum ObjectType {
    Elf,
    Thief,
    Squirrel
};

const inline std::map<std::string, ObjectType> objectTypeMapper{
    {"Elf", Elf},
    {"Thief", Thief},
    {"Squirrel", Squirrel},
};

ObjectType fromString(const std::string& str) {
    return objectTypeMapper.at(str);
}

static std::shared_ptr<NPC::BaseNpc> getObject(const std::string& type, const Json::JsonObject& jsonObject) {
    switch (fromString(type)) {
        case Elf : {
            std::shared_ptr<NPC::Elf> elfObj = std::make_shared<NPC::Elf>();
            elfObj->deserialize(jsonObject);
            return elfObj;
        }
        case Thief: {
            std::shared_ptr<NPC::Thief> bearObj = std::make_shared<NPC::Thief>();
            bearObj->deserialize(jsonObject);
            return bearObj;
        }
        case Squirrel: {
            std::shared_ptr<NPC::Squirrel> squirrelObj = std::make_shared<NPC::Squirrel>();
            squirrelObj->deserialize(jsonObject);
            return squirrelObj;
        }
    }
    throw std::invalid_argument("Unknown type");
}

namespace Backup {
    std::vector<std::shared_ptr<NPC::BaseNpc>> BackupHandler::Load() const {
        std::ifstream file;
        file.open(filename);
        if (!file.good()) throw std::invalid_argument("Can't load current state, because file can't be opened");

        std::string buffer = Utils::read(file);
        buffer.erase(
            std::remove_if(
                buffer.begin(),
                buffer.end(),
                [](auto c) {
                  return std::isspace(c);
                }
            ),
            buffer.end()
        );

        std::vector<std::shared_ptr<NPC::BaseNpc>> result;

        auto idx = std::make_shared<size_t>(0);
        auto m = Json::JsonObject(buffer, idx);

        for (auto& v : m.getObject()){
            if (v.first == "Count") continue;
            auto obj = v.second;
            if (obj.getType() != Json::Map) throw std::invalid_argument("Data is malformed");
            auto obj1 = obj.getObject();
            result.push_back(getObject(obj1.at("Type").getValue<std::string>(), obj1.at("Object")));
        }

        return result;
    }

    void BackupHandler::Backup(const std::vector<std::shared_ptr<NPC::BaseNpc>> &objects) const {
        std::ofstream file;
        file.open(filename);
        if (!file.good()) throw std::invalid_argument("Can't load current state, because file can't be opened");

        file << "{" << std::endl;
        file << "Count=" << objects.size() << ";" << std::endl;

        auto idx = 0;
        for (const auto& object: objects){
            file << "Obj" << idx << "={" << std::endl;
            file << "Type=" << object->getType() << ";" << std::endl;
            file << "Object=" << object->serialize() << ";" << std::endl;
            file << "};" << std::endl;
            ++idx;
        }

        file << "}";
    }

    BackupHandler &BackupHandler::operator=(BackupHandler &&other) noexcept {
        filename = std::move(other.filename);
        return *this;
    }

} // Backup