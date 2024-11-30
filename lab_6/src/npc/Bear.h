//
// Created by nikit on 11/29/2024.
//

#ifndef OOP_LAB_6_SRC_BEAR_H_
#define OOP_LAB_6_SRC_BEAR_H_

#include "BaseNpc.h"
#include "../utils/IVisitor.h"
#include "Squirrel.h"

namespace NPC {

 class Bear : public BaseNpc, public Utils::IVisitor<Bear, NPC::Elf, NPC::Squirrel, NPC::BaseNpc> {
        public:
            Bear() : BaseNpc(){};
            Bear(
                const Utils::Point<double>& position,
                double range,
                const std::string& name,
                const bool alive,
                std::shared_ptr<Logger::ILogger> logger
            ) : BaseNpc(position, range, name, alive, std::move(logger)) {}
            std::string getType() const override { return "Bear"; }
            void accept(const BaseNpc& visitor) override {
                visitor
            }
    };

} // NPC

#endif //OOP_LAB_6_SRC_BEAR_H_
