#ifndef OOP_LAB_6_SRC_BACKUPHANDLER_H_
#define OOP_LAB_6_SRC_BACKUPHANDLER_H_

#include <vector>
#include <fstream>
#include <iostream>
#include <ranges>
#include <regex>
#include "../utils/ISerializable.h"

#include "../npc/BaseNpc.h"
#include "../npc/Elf.h"
#include "../npc/Bear.h"
#include "../npc/Squirrel.h"
#include "../utils/JsonObject.h"

enum ObjectType {
    Elf,
    Bear,
    Squirrel
};

const inline std::map<std::string, ObjectType> objectTypeMapper{
    {"Elf", Elf},
    {"Bear", Bear},
    {"Squirrel", Squirrel},
};

ObjectType fromString(const std::string& str) {
    return objectTypeMapper.at(str);
}

namespace Backup {
    class BackupHandler {
        std::string filename;

        static std::shared_ptr<NPC::BaseNpc> getObject(const std::string& type, const Json::JsonObject& jsonObject) {
            switch (fromString(type)) {
                case Elf : {
                        std::shared_ptr<NPC::Elf> elfObj = std::make_shared<NPC::Elf>();
                        elfObj->Deserialize(jsonObject);
                        return elfObj;
                    }
                case Bear: {
                    std::shared_ptr<NPC::Bear> bearObj = std::make_shared<NPC::Bear>();
                    bearObj->Deserialize(jsonObject);
                    return bearObj;
                }
                case Squirrel: {
                    std::shared_ptr<NPC::Squirrel> squirrelObj = std::make_shared<NPC::Squirrel>();
                    squirrelObj->Deserialize(jsonObject);
                    return squirrelObj;
                }
            }
            throw std::invalid_argument("Unknown type");
        }


        public:
            BackupHandler() : filename("backup.txt") {};
            explicit BackupHandler(std::string& file) : filename(file) {};

            void Backup(const std::vector<std::shared_ptr<NPC::BaseNpc>>& objects) const {
                std::ofstream file;
                file.open(filename);
                if (!file.good()) throw std::invalid_argument("Can't load current state, because file can't be opened");

                file << "{" << std::endl;
                file << "Count=" << objects.size() << ";" << std::endl;

                auto idx = 0;
                for (const auto& object: objects){
                    file << "Obj" << idx << "={" << std::endl;
                    file << "Type=" << object->getType() << ";" << std::endl;
                    file << "Object=" << object->Serialize() << ";" << std::endl;
                    file << "};" << std::endl;
                    ++idx;
                }

                file << "}";
            }

            std::vector<std::shared_ptr<NPC::BaseNpc>> Load() const {
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
                    result.push_back(getObject(obj1.at("Type").getValue(), obj1.at("Object")));
                }

                return result;
            }



    };

} // Backup

#endif //OOP_LAB_6_SRC_BACKUPHANDLER_H_
