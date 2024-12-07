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
#include "utils/ScopedThread.h"
#include "utils/RandomNumberGenerator.h"

constexpr int minX = 0, maxX = 10;
constexpr int minY = 0, maxY = 10;


namespace Field {
    Field::Field(const size_t count) : npcs() {
        std::vector<std::shared_ptr<Logger::ILogger>> loggers {std::make_shared<Logger::ConsoleLogger>()};

        std::random_device dev;
        Utils::RandomNumberGenerator rng(dev);

        for (auto i = 0; i < count; ++i){
            auto pos = Utils::Point<int>(rng.generateInt(minX, maxX), rng.generateInt(minY, maxY));

            switch (rng.generateInt(0, 2)){
                case 0:
                    npcs.emplace_back(std::make_shared<NPC::Elf>(pos, std::format("Elf{}", i), true, loggers));
                    break;
                case 1:
                    npcs.emplace_back(std::make_shared<NPC::Squirrel>(pos, std::format("Squirrel{}", i), true, loggers));
                    break;
                case 2:
                    npcs.emplace_back(std::make_shared<NPC::Thief>(pos, std::format("Thief{}", i), true, loggers));
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
        auto start = std::chrono::steady_clock::now();
        auto duration_limit = std::chrono::seconds(3);
        Logger::ConsoleLogger logger;

        auto st = Utils::ScopedThread([&logger,this, start, duration_limit] (){
            logger << "Starting game!" << std::endl;
            while (std::chrono::steady_clock::now() - start < duration_limit){
                printCurrentStatus();
                logger << "Moving..." << std::endl;
                moveNpcs();
                logger << "Finished moving" << std::endl;
                logger << "Fighting..." << std::endl;
                fight();
                logger << "Finished fighting" << std::endl;
            }
            logger << "Finished game!" << std::endl;
        });

    }

    void Field::printCurrentStatus() const {
        Logger::ConsoleLogger logger;

        std::vector<std::vector<char>> board(maxY + 1, std::vector<char>(maxX + 1, ' '));

        for (auto& npc: npcs){
            auto pos = npc->getPos();
            board[pos.getY()][pos.getX()] = npc->getIsAlive() ? npc->getShortType() : 'X';
        }

        for (const auto& row : board){
            for (const auto& cell: row){
                logger << "[" << cell << "]";
            }
            logger << std::endl;
        }

    }

    void Field::moveNpcs() {
        std::random_device dev;
        Utils::RandomNumberGenerator rng(dev);

        for (auto & npc : npcs){
            if (!npc->getIsAlive()) continue;
            auto md = npc->getMoveDistance();
            auto pos = npc->getPos();

            auto range = rng.generateInt(0, std::floor(md));
            auto dx = rng.generateInt(0, std::floor(std::sqrt(range)));
            auto dy = static_cast<int>(std::floor(std::sqrt(range * range - dx * dx)));

            if (pos.getX() + dx > maxX) dx = maxX - pos.getX();
            if (pos.getY() + dy > maxY) dy = maxY - pos.getY();

            *npc += Utils::Vec2D<int>(dx, dy);
        }
    }

    void Field::fight() {
        for (auto & npc1 : npcs){
            for (auto & npc2 : npcs){
                npc1->accept(npc2);
            }
        }
    }

}