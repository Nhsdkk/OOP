#ifndef OOP_LAB_6_SRC_FIELD_H_
#define OOP_LAB_6_SRC_FIELD_H_

#include <vector>
#include <memory>
#include "npc/BaseNpc.h"
namespace Field {

    class Field {
        std::vector<std::shared_ptr<NPC::BaseNpc>> npcs;
        std::vector<std::shared_ptr<Logger::ILogger>> loggers;
        int minX, maxX, minY, maxY;

        void moveNpcs();
        void fight();

        public:
            Field() : npcs(), minX(0), minY(30), maxX(0), maxY(30) {
                std::cout << "HI";
            }
            Field(
                std::initializer_list<std::shared_ptr<NPC::BaseNpc>> npc,
                int minX = 0,
                int maxX = 30,
                int minY = 0,
                int maxY = 30
            ) : npcs(npc), minX(minX), maxX(maxX), minY(minY), maxY(maxY) {
                std::cout << "HI";
            };
            explicit Field(
                size_t count,
                int minX = 0,
                int maxX = 30,
                int minY = 0,
                int maxY = 30
            );
            Field(const Field& other) = default;
            Field(Field&& other) = default;

            Field& operator=(const Field& other) = default;
            Field& operator=(Field&& other) noexcept;

            void play(int sec = 3);
            void printStats() const;
            void printCurrentStatus() const;

            void attachLoggers(const std::vector<std::shared_ptr<Logger::ILogger>> &l);
            void detachLogger(const std::string& loggerName);

            void backup() const;
            void load();


            ~Field() = default;
    };

} // Field

#endif //OOP_LAB_6_SRC_FIELD_H_
