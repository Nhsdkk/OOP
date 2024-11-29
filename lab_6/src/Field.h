//
// Created by nikit on 11/24/2024.
//

#ifndef OOP_LAB_6_SRC_FIELD_H_
#define OOP_LAB_6_SRC_FIELD_H_

#include <vector>
#include <memory>
#include "npc/BaseNpc.h"
namespace Field {

    class Field {
        std::vector<std::shared_ptr<NPC::BaseNpc>> npcs;
        public:
            Field() : npcs() {}
            Field(std::initializer_list<std::shared_ptr<NPC::BaseNpc>> npc) : npcs(npc) {}
    };

} // Field

#endif //OOP_LAB_6_SRC_FIELD_H_
