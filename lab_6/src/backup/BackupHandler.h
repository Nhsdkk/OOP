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

        static std::shared_ptr<NPC::BaseNpc> getObject(const std::string& type, const std::string& values) {
            switch (fromString(type)) {
                case Elf : {
                        std::shared_ptr<NPC::Elf> elfObj;
                        elfObj->Deserialize(values);
                        return elfObj;
                    }
                case Bear: {
                    std::shared_ptr<NPC::Bear> bearObj;
                    bearObj->Deserialize(values);
                    return bearObj;
                }
                case Squirrel: {
                    std::shared_ptr<NPC::Squirrel> squirrelObj;
                    squirrelObj->Deserialize(values);
                    return squirrelObj;
                }
            }
        }


        public:
            BackupHandler() : filename("backup.txt") {};
            explicit BackupHandler(std::string& file) : filename(file) {};

            void Backup(const std::vector<std::shared_ptr<NPC::BaseNpc>>& objects) const {
                std::ofstream file;
                file.open(filename);
                if (!file.good()) throw std::invalid_argument("Can't load current state, because file can't be opened");

                file << "Count=" << objects.size() << std::endl;
                file << std::endl;

                for (const auto& object: objects){
                    file << "{" << std::endl;
                    file << "Type=" << object->getType() << std::endl;
                    file << "Object=" << object->Serialize() << std::endl;
                    file << "}" << std::endl;
                    file << std::endl;
                }

                file.close();
            }

            std::vector<std::shared_ptr<NPC::BaseNpc>> Load() const {
                std::ifstream file;
                file.open(filename);
                if (!file.good()) throw std::invalid_argument("Can't load current state, because file can't be opened");

                std::string buffer;
                std::getline(file, buffer);

                size_t size = std::stoull(Utils::getValue(buffer).value());
                std::vector<std::shared_ptr<NPC::BaseNpc>> result;

                std::getline(file, buffer);

                for (auto i = 0; i < size; ++i){
                    std::getline(file, buffer);
                    std::string stringObject;

                    while (!buffer.empty()){
                        stringObject += buffer + '\n';
                        std::getline(file, buffer);
                    }

                    auto m = Utils::toMap(buffer);

                    if (m.contains("Type")) throw std::invalid_argument("Can't determine object type from string");
                    std::shared_ptr<NPC::BaseNpc> object = getObject(m.at("Type"), m.at("Object"));
                    result.push_back(object);
                }

                file.close();
                return result;
            }



    };

} // Backup

#endif //OOP_LAB_6_SRC_BACKUPHANDLER_H_
