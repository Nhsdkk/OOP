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
        Utils::Point<int> pos;
        double range, moveDistance;
        std::string name;
        bool isAlive;
        std::vector<std::shared_ptr<Logger::ILogger>> loggers;

        public:
            BaseNpc() : pos(), range(), name(), isAlive(false), loggers(), moveDistance() {}
            BaseNpc(
                const Utils::Point<int>& position,
                double range,
                double moveDistance,
                std::string  name,
                const bool alive,
                std::vector<std::shared_ptr<Logger::ILogger>> loggers
            ) : pos(position), name(std::move(name)), isAlive(alive), loggers(std::move(loggers)), range(range), moveDistance(moveDistance) {}
            BaseNpc(const BaseNpc& other) = default;
            BaseNpc(BaseNpc&& other) noexcept = default;

            BaseNpc& operator=(const BaseNpc& other) = default;
            BaseNpc& operator=(BaseNpc&& other) noexcept;

            void kill(const std::shared_ptr<BaseNpc>& victim);
            void move(const Utils::Vec2D<double>& moveVec);

            void attachLoggers(const std::vector<std::shared_ptr<Logger::ILogger>> &l);

            void detachLogger(const std::string& loggerName);

            Utils::Point<int> getPos() const;
            double getRange() const;
            double getMoveDistance() const;
            std::string getName() const;
            bool getIsAlive() const;

            virtual std::string getType() const = 0;
            virtual char getShortType() const = 0;

            virtual void accept(const std::shared_ptr<BaseNpc>& npc) = 0;

            virtual void visit(std::shared_ptr<Thief> npc) = 0;
            virtual void visit(std::shared_ptr<Elf> npc) = 0;
            virtual void visit(std::shared_ptr<Squirrel> npc) = 0;

            bool canAttack(const std::shared_ptr<BaseNpc>& victim) const;

            std::string serialize() const override;

            void deserialize(const Json::JsonObject& jsonObject) override;

            bool operator==(const BaseNpc& other) const;
            BaseNpc& operator+=(const Utils::Vec2D<int>& vec);

            ~BaseNpc() override = default;
    };

} // NPC

#endif //OOP_LAB_6_SRC_BASENPC_H_
