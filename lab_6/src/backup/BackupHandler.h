#ifndef OOP_LAB_6_SRC_BACKUPHANDLER_H_
#define OOP_LAB_6_SRC_BACKUPHANDLER_H_

#include <utility>
#include <vector>
#include <fstream>
#include <iostream>
#include <ranges>
#include <regex>
#include "../utils/ISerializable.h"

#include "../npc/BaseNpc.h"
#include "../npc/Elf.h"
#include "../npc/Thief.h"
#include "../npc/Squirrel.h"
#include "../utils/JsonObject.h"

namespace Backup {
    class BackupHandler {
        std::string filename;

        public:
            BackupHandler() : filename("backup.txt") {};
            explicit BackupHandler(std::string  file) : filename(std::move(file)) {};
            BackupHandler(const BackupHandler& other) = default;
            BackupHandler(BackupHandler&& other) noexcept = default;

            BackupHandler &operator=(const BackupHandler &other) = default;
            BackupHandler &operator=(BackupHandler&& other) noexcept;

            void Backup(const std::vector<std::shared_ptr<NPC::BaseNpc>>& objects) const;

            std::vector<std::shared_ptr<NPC::BaseNpc>> Load() const;
            ~BackupHandler() = default;
    };

} // Backup

#endif //OOP_LAB_6_SRC_BACKUPHANDLER_H_
