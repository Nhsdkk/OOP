//
// Created by nikit on 11/29/2024.
//

#include "Squirrel.h"

namespace NPC {
    void Squirrel::visit(std::shared_ptr<Thief> npc) { }
    void Squirrel::visit(std::shared_ptr<Elf> npc) { kill(npc); }
    void Squirrel::visit(std::shared_ptr<Squirrel> npc) { }

    void Squirrel::accept(const std::shared_ptr<BaseNpc> &visitor) {
        auto ptrToThis = std::static_pointer_cast<Squirrel>(shared_from_this());
        visitor->visit(ptrToThis);
    }

    std::string Squirrel::getType() const { return "Squirrel"; }

    Squirrel &Squirrel::operator=(Squirrel &&other) noexcept {
        BaseNpc::operator=(std::move(other));
        return *this;
    }
} // NPC