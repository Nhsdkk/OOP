//
// Created by nikit on 11/24/2024.
//

#include <random>
#include <set>
#include <chrono>
#include "Field.h"
#include "logger/ConsoleLogger.h"
#include "npc/Thief.h"
#include "npc/Squirrel.h"
#include "npc/Elf.h"
#include "backup/BackupHandler.h"
#include "utils/RandomNumberGenerator.h"

constexpr double minX = 0, maxX = 500;
constexpr double minY = 0, maxY = 500;
constexpr double minRange = 10, maxRange = 250;

namespace Field {
Field::Field(const size_t count) : npcs() {
    std::vector<std::shared_ptr<Logger::ILogger>> loggers {std::make_shared<Logger::ConsoleLogger>()};

    std::random_device dev;
    Utils::RandomNumberGenerator rng(dev);

    for (auto i = 0; i < count; ++i){
        auto pos = Utils::Point<double>(rng.generateInt(minX, maxX), rng.generateInt(minY, maxY));
        auto range = rng.generateInt(minRange, maxRange);
        switch (rng.generateInt(0, 2)){
            case 0:
                npcs.emplace_back(std::make_shared<NPC::Elf>(pos, range, std::format("Elf{}", i), true, loggers));
                break;
            case 1:
                npcs.emplace_back(std::make_shared<NPC::Squirrel>(pos, range, std::format("Squirrel{}", i), true, loggers));
                break;
            case 2:
                npcs.emplace_back(std::make_shared<NPC::Thief>(pos, range, std::format("Thief{}", i), true, loggers));
                break;
            default:
                throw std::invalid_argument("Invalid type");
        }
    }
}

    void Field::backup() const {
        Backup::BackupHandler handler;
        handler.Backup(npcs);
    }

    void Field::load(const std::vector<std::shared_ptr<Logger::ILogger>>& loggers) {
        Backup::BackupHandler handler;
        npcs = handler.Load();
        for (auto & npc : npcs){
            npc->attachLoggers(loggers);
        }
    }

    Field &Field::operator=(Field &&other) noexcept {
        npcs = std::move(other.npcs);
        return *this;
    }

    void Field::play() {
        Logger::ConsoleLogger logger;

        logger << "Starting game!" << std::endl;
        logger << "Fighting..." << std::endl;
        fight();
        logger << "Finished fighting" << std::endl;
        logger << "Finished game!" << std::endl;

    }

    void Field::fight() {
        for (auto & npc1 : npcs){
            for (auto & npc2 : npcs){
                npc1->accept(npc2);
            }
        }
    }
} // Field