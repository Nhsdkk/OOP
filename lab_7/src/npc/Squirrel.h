//
// Created by nikit on 11/29/2024.
//

#ifndef OOP_LAB_6_SRC_SQUIRREL_H_
#define OOP_LAB_6_SRC_SQUIRREL_H_

#include "BaseNpc.h"
#include "Thief.h"
#include "Elf.h"

namespace NPC {

    class Squirrel : public BaseNpc  {
        public:
            Squirrel(): BaseNpc() {}
            Squirrel(
                const Utils::Point<int>& position,
                const std::string& name,
                const bool alive,
                std::vector<std::shared_ptr<Logger::ILogger>> loggers,
                double range = 5,
                double moveDistance = 5
            ) : BaseNpc(position, range, moveDistance, name, alive, std::move(loggers)) {}
            Squirrel(const Squirrel& other) = default;
            Squirrel(Squirrel&& other) noexcept = default;

            Squirrel& operator=(const Squirrel& other) = default;
            Squirrel& operator=(Squirrel&& other) noexcept;

            std::string getType() const override;
            char getShortType() const override;

            void accept(const std::shared_ptr<BaseNpc>& visitor) override;

            void visit(std::shared_ptr<Thief> npc) override;
            void visit(std::shared_ptr<Elf> npc) override;
            void visit(std::shared_ptr<Squirrel> npc) override;
    };

} // NPC

#endif //OOP_LAB_6_SRC_SQUIRREL_H_
