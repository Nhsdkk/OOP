//
// Created by nikit on 11/29/2024.
//

#ifndef OOP_LAB_6_SRC_SQUIRREL_H_
#define OOP_LAB_6_SRC_SQUIRREL_H_

#include "BaseNpc.h"
namespace NPC {

    class Squirrel : public BaseNpc  {
        public:
            Squirrel(
                const Utils::Point<double>& position,
                const Utils::Vec2D<double>& range,
                const std::string& name,
                const bool alive,
                std::shared_ptr<Logger::ILogger> logger
            ) : BaseNpc(position, range, name, alive, std::move(logger)) {}
            std::string getType() const override { return "Squirrel"; }
    };

} // NPC

#endif //OOP_LAB_6_SRC_SQUIRREL_H_
