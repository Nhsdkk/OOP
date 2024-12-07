//
// Created by nikit on 11/24/2024.
//

#include "Elf.h"

namespace NPC {
    void Elf::visit(std::shared_ptr<Thief> npc) { kill(npc); }
    void Elf::visit(std::shared_ptr<Elf> npc) {  }
    void Elf::visit(std::shared_ptr<Squirrel> npc) {  }

    void Elf::accept(const std::shared_ptr<BaseNpc> &visitor) {
        auto ptrToThis = std::static_pointer_cast<Elf>(shared_from_this());
        visitor->visit(ptrToThis);
    }

    std::string Elf::getType() const { return "Elf"; }
    char Elf::getShortType() const { return 'E'; }

    Elf &Elf::operator=(Elf &&other) noexcept {
        BaseNpc::operator=(std::move(other));
        return *this;
    }
} // NPC