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

void logMultiple(const std::string& message, const std::vector<std::shared_ptr<Logger::ILogger>>& loggers){
    for (auto& logger : loggers)
        logger->log(message);
}

namespace Field {
    Field::Field(
        size_t count,
        int minX,
        int maxX,
        int minY,
        int maxY
    ) : npcs(), loggers({std::make_shared<Logger::ConsoleLogger>()}), minX(minX), maxX(maxX), minY(minY), maxY(maxY) {
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

    void Field::load() {
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

    void Field::play(int sec) {
        auto start = std::chrono::steady_clock::now();
        auto duration_limit = std::chrono::seconds(sec);
        Logger::ConsoleLogger logger;

        auto st = Utils::ScopedThread([&logger,this, start, duration_limit] (){
            logger << "Starting game!" << std::endl;

            auto fightCor = fight();
            auto moveCor = moveNpcs();

            while (std::chrono::steady_clock::now() - start < duration_limit){
                printCurrentStatus();
                logger << "Moving..." << std::endl;
                moveCor.resume();
                logger << "Finished moving" << std::endl;
                logger << "Fighting..." << std::endl;
                fightCor.resume();
                logger << "Finished fighting" << std::endl;
            }
            logger << "Finished game!" << std::endl;
            printCurrentStatus();
            printStats();
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

    Utils::Task Field::moveNpcs() {
        while (true) {
            std::random_device dev;
            Utils::RandomNumberGenerator rng(dev);

            for (auto &npc : npcs) {
                if (!npc->getIsAlive()) continue;
                auto md = npc->getMoveDistance();
                auto pos = npc->getPos();

                auto range = rng.generateInt(0, std::floor(md));
                auto dx = rng.generateInt(-std::floor(std::sqrt(range)), std::floor(std::sqrt(range)));
                auto dy = static_cast<int>(std::floor(std::sqrt(range * range - dx * dx))) * std::pow(-1, range % 2);

                if (pos.getX() + dx > maxX) dx = maxX - pos.getX();
                if (pos.getY() + dy > maxY) dy = maxY - pos.getY();

                if (pos.getX() + dx < minX) dx = minX - pos.getX();
                if (pos.getY() + dy < minY) dy = minY - pos.getY();

                *npc += Utils::Vec2D<int>(dx, dy);
            }

            co_await std::suspend_always{};
        }
    }



    Utils::Task Field::fight() {
        while (true) {
            for (auto &npc1 : npcs) {
                for (auto &npc2 : npcs) {
                    npc1->accept(npc2);
                }
            }

            co_await std::suspend_always{};
        }
    }

    void Field::attachLoggers(const std::vector<std::shared_ptr<Logger::ILogger>> &l) {
        loggers.insert(loggers.end(), l.begin(),l.end());
        for (auto& npc : npcs){
            npc->attachLoggers(l);
        }
    }

    void Field::detachLogger(const std::string &loggerName) {
        loggers.erase(
            std::remove_if(
                loggers.begin(),
                loggers.end(),
                [loggerName](const std::shared_ptr<Logger::ILogger>& item)
                { return item->getName() == loggerName; }
            ),
            loggers.end()
        );

        for (auto& npc : npcs){
            npc->detachLogger(loggerName);
        }
    }

    void Field::printStats() const {
        for (auto& npc : npcs){
            auto pos = npc->getPos();
            if (npc->getIsAlive()){
                logMultiple(std::format("{} of type {} is alive and at x={} y={}", npc->getName(), npc->getType(), pos.getX(), pos.getY()), loggers);
            } else {
                logMultiple(std::format("{} of type {} was killed at x={} y={}", npc->getName(), npc->getType(), pos.getX(), pos.getY()), loggers);
            }
        }
    }

}