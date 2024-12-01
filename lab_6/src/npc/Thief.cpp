//
// Created by nikit on 11/29/2024.
//

#include "Thief.h"

namespace NPC {
    void Thief::visit(std::shared_ptr<Squirrel> npc) { kill(npc); }
    void Thief::visit(std::shared_ptr<Elf> npc) { }
    void Thief::visit(std::shared_ptr<Thief> npc) { }

    void Thief::accept(const std::shared_ptr<BaseNpc> &visitor) {
        auto ptrToThis = std::static_pointer_cast<Thief>(shared_from_this());
        visitor->visit(ptrToThis);
    }

    std::string Thief::getType() const { return "Thief"; }

    Thief &Thief::operator=(Thief &&other) noexcept {
        BaseNpc::operator=(std::move(other));
        return *this;
    }
} // NPC