//
// Created by nikit on 11/24/2024.
//

#include <random>
#include <set>
#include "Field.h"
#include "logger/ConsoleLogger.h"
#include "npc/Thief.h"
#include "npc/Squirrel.h"
#include "npc/Elf.h"
#include "backup/BackupHandler.h"

constexpr double minX = 0, maxX = 500;
constexpr double minY = 0, maxY = 500;
constexpr double minRange = 0, maxRange = 250;

std::default_random_engine re;

std::uniform_real_distribution<double> xDistribution(minX,maxX);
std::uniform_real_distribution<double> yDistribution(minY,maxY);
std::uniform_real_distribution<double> rangeDistribution(minRange,maxRange);

namespace Field {
    Field::Field(const size_t count) : npcs() {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> typeDistribution(0,2);

        std::vector<std::shared_ptr<Logger::ILogger>> loggers {std::make_shared<Logger::ConsoleLogger>()};

        for (auto i = 0; i < count; ++i){
            auto pos = Utils::Point<double>(xDistribution(re), yDistribution(re));
            auto range = rangeDistribution(re);

            switch (typeDistribution(rng)){
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
        for (auto & npc1 : npcs){
            for (auto & npc2 : npcs){
                npc1->accept(npc2);
            }
        }
    }
} // Field