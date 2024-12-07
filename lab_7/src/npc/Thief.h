//
// Created by nikit on 11/29/2024.
//

#ifndef OOP_LAB_6_SRC_BEAR_H_
#define OOP_LAB_6_SRC_BEAR_H_

#include "BaseNpc.h"
#include "Squirrel.h"
#include "Elf.h"

namespace NPC {

    class Thief : public BaseNpc {
        public:
            Thief() : BaseNpc(){};
            Thief(
                const Utils::Point<int>& position,
                const std::string& name,
                const bool alive,
                std::vector<std::shared_ptr<Logger::ILogger>> loggers,
                double range = 10,
                double moveDistance = 10
            ) : BaseNpc(position, range, moveDistance, name, alive, std::move(loggers)) {}
            Thief(const Thief& other) = default;
            Thief(Thief&& other) noexcept = default;

            Thief& operator=(const Thief& other) = default;
            Thief& operator=(Thief&& other) noexcept;

            std::string getType() const override;
            char getShortType() const override;

            void accept(const std::shared_ptr<BaseNpc>& visitor) override;

            void visit(std::shared_ptr<Thief> npc) override;
            void visit(std::shared_ptr<Elf> npc) override;
            void visit(std::shared_ptr<Squirrel> npc) override;
            ~Thief() override = default;
    };

} // NPC

#endif //OOP_LAB_6_SRC_BEAR_H_
