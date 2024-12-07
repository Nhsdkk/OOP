//
// Created by nikit on 11/24/2024.
//

#ifndef OOP_LAB_6_SRC_ELF_H_
#define OOP_LAB_6_SRC_ELF_H_

#include <utility>

#include "BaseNpc.h"
#include "Thief.h"
#include "Squirrel.h"

namespace NPC {

    class Elf : public BaseNpc {
        public:
            Elf(): BaseNpc() {}
            Elf(
                const Utils::Point<double>& position,
                double range,
                const std::string& name,
                const bool alive,
                std::vector<std::shared_ptr<Logger::ILogger>> loggers
            ) : BaseNpc(position, range, name, alive, std::move(loggers)) {}
            Elf(const Elf& other) = default;
            Elf(Elf&& other) noexcept = default;

            Elf& operator=(const Elf& other) = default;
            Elf& operator=(Elf&& other) noexcept;

            std::string getType() const override;

            void accept(const std::shared_ptr<BaseNpc>& visitor) override;

            void visit(std::shared_ptr<Thief> npc) override;
            void visit(std::shared_ptr<Elf> npc) override;
            void visit(std::shared_ptr<Squirrel> npc) override;
    };

} // NPC

#endif //OOP_LAB_6_SRC_ELF_H_
