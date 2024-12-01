//
// Created by nikit on 11/24/2024.
//

#ifndef OOP_LAB_6_SRC_BASENPC_H_
#define OOP_LAB_6_SRC_BASENPC_H_

#include <format>
#include <utility>
#include "../utils/Point.h"
#include "../utils/ISerializable.h"
#include "../logger/ILogger.h"
#include "../utils/Vec2D.h"

namespace NPC {
    class Elf;
    class Squirrel;
    class Thief;

    class BaseNpc : public Utils::ISerializable, public std::enable_shared_from_this<BaseNpc>{
        Utils::Point<double> pos;
        double range;
        std::string name;
        bool isAlive;
        std::vector<std::shared_ptr<Logger::ILogger>> loggers;

        public:
            BaseNpc() : pos(), range(), name(), isAlive(false), loggers() {}
            BaseNpc(
                const Utils::Point<double>& position,
                double range,
                std::string  name,
                const bool alive,
                std::vector<std::shared_ptr<Logger::ILogger>> loggers
            ) : pos(position), name(std::move(name)), isAlive(alive), loggers(std::move(loggers)), range(range) {}
            BaseNpc(const BaseNpc& other) = default;
            BaseNpc(BaseNpc&& other) noexcept = default;

            BaseNpc& operator=(const BaseNpc& other) = default;
            BaseNpc& operator=(BaseNpc&& other) noexcept;

            void kill(const std::shared_ptr<BaseNpc>& victim);

            void attachLoggers(const std::vector<std::shared_ptr<Logger::ILogger>> &l);

            void detachLogger(const std::string& loggerName);

            Utils::Point<double> getPos() const;
            double getRange() const;
            std::string getName() const;
            bool getIsAlive() const;

            virtual std::string getType() const = 0;

            virtual void accept(const std::shared_ptr<BaseNpc>& npc) = 0;

            virtual void visit(std::shared_ptr<Thief> npc) = 0;
            virtual void visit(std::shared_ptr<Elf> npc) = 0;
            virtual void visit(std::shared_ptr<Squirrel> npc) = 0;

            bool canAttack(const std::shared_ptr<BaseNpc>& victim) const;

            std::string serialize() const override;

            void deserialize(const Json::JsonObject& jsonObject) override;

            bool operator==(const BaseNpc& other) const;
            ~BaseNpc() override = default;
    };

} // NPC

#endif //OOP_LAB_6_SRC_BASENPC_H_
