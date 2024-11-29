//
// Created by nikit on 11/24/2024.
//

#ifndef OOP_LAB_6_SRC_BASENPC_H_
#define OOP_LAB_6_SRC_BASENPC_H_

#include <format>
#include <utility>
#include "../utils/Point.h"
#include "../utils/ISerializable.h"
#include "../logger/ILogger.h"
#include "../utils/Vec2D.h"
namespace NPC {

    class BaseNpc : public Utils::ISerializable {
        Utils::Point<double> pos;
        Utils::Vec2D<double> range;
        std::string name;
        bool isAlive;
        std::shared_ptr<Logger::ILogger> logger;

        public:
            BaseNpc() : pos(), name(), isAlive(false), logger(nullptr) {}
            BaseNpc(
                const Utils::Point<double>& position,
                const Utils::Vec2D<double>& range,
                const std::string& name,
                const bool alive,
                std::shared_ptr<Logger::ILogger> logger
            ) : pos(position), name(name), isAlive(alive), logger(std::move(logger)), range(range) {}

            virtual void kill(const std::string& killerName, const std::string& killerType){
                if (logger == nullptr) return;
                logger->log(std::format("{} of type {} got killed by {} of type {}", name, getType(), killerName, killerType));
            }

            void attachLogger(std::shared_ptr<Logger::ILogger> l) {
                logger = std::move(l);
            }

            void detachLogger() {
                logger = nullptr;
            }

            Utils::Point<double> getPos() const { return pos; }
            std::string getName() const { return name; }
            bool getIsAlive() const{ return isAlive; }

            // TODO: Use custom exception
            virtual std::string getType() const { throw std::invalid_argument("Unimplemented"); }

            std::string Serialize() const override {
                std::ostringstream oss;
                oss << "{" << std::endl;
                oss << "Pos=" << pos.Serialize() << std::endl;
                oss << "Range=" << range.Serialize() << std::endl;
                oss << "Name=" << name << std::endl;
                oss << "IsAlive=" << (isAlive ? "true" : "false") << std::endl;
                oss << "}";
                return oss.str();
            }

            void Deserialize(const std::string& values) override {
                auto m = Utils::toMap(values);

                pos = Utils::Point<double>();
                pos.Deserialize(m["Position"]);
                name = m["Name"];
                isAlive = m["IsAlive"] == "true";
            }
    };

} // NPC

#endif //OOP_LAB_6_SRC_BASENPC_H_
