//
// Created by nikit on 11/24/2024.
//

#ifndef OOP_LAB_6_SRC_ELF_H_
#define OOP_LAB_6_SRC_ELF_H_

#include <utility>

#include "BaseNpc.h"

namespace NPC {

    class Elf : public BaseNpc {
        public:
            Elf(
                const Utils::Point<double>& position,
                const Utils::Vec2D<double>& range,
                const std::string& name,
                const bool alive,
                std::shared_ptr<Logger::ILogger> logger
            ) : BaseNpc(position, range, name, alive, std::move(logger)) {}
            std::string getType() const override { return "Elf"; }
    };

} // NPC

#endif //OOP_LAB_6_SRC_ELF_H_
