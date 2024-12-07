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
            Field(std::initializer_list<std::shared_ptr<NPC::BaseNpc>> npc) : npcs(npc) {};
            explicit Field(size_t count);
            Field(const Field& other) = default;
            Field(Field&& other) = default;

            Field& operator=(const Field& other) = default;
            Field& operator=(Field&& other) noexcept;

            void play();
            void backup() const;
            void load(const std::vector<std::shared_ptr<Logger::ILogger>>& loggers);
            ~Field() = default;
    };

} // Field

#endif //OOP_LAB_6_SRC_FIELD_H_
