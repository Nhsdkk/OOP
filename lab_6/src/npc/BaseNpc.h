//
// Created by nikit on 11/24/2024.
//

#ifndef OOP_LAB_6_SRC_BASENPC_H_
#define OOP_LAB_6_SRC_BASENPC_H_

#include <format>
#include <utility>
#include "../utils/Point.h"
#include "../utils/ISerializable.h"
#include "../utils/IElement.h"
#include "../logger/ILogger.h"

namespace NPC {

    class BaseNpc : public Utils::ISerializable, public Utils::IElement<BaseNpc>{
        Utils::Point<double> pos;
        double range;
        std::string name;
        bool isAlive;
        std::shared_ptr<Logger::ILogger> logger;

        public:
            BaseNpc() : pos(), range(), name(), isAlive(false), logger(nullptr) {}
            BaseNpc(
                const Utils::Point<double>& position,
                double range,
                std::string  name,
                const bool alive,
                std::shared_ptr<Logger::ILogger> logger
            ) : pos(position), name(std::move(name)), isAlive(alive), logger(std::move(logger)), range(range) {}

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
            double getRange() const { return range; }
            std::string getName() const { return name; }
            bool getIsAlive() const{ return isAlive; }

            virtual std::string getType() const = 0;

            std::string Serialize() const override {
                std::ostringstream oss;
                oss << "{" << std::endl;
                oss << "Position=" << pos.Serialize() << ";" << std::endl;
                oss << "Range=" << range << ";" << std::endl;
                oss << "Name=" << name << ";" << std::endl;
                oss << "IsAlive=" << (isAlive ? "true" : "false") << ";" << std::endl;
                oss << "}";
                return oss.str();
            }

            void Deserialize(const Json::JsonObject& jsonObject) override {
                if (jsonObject.getType() != Json::Map) throw std::invalid_argument("Can't parse value to point");
                auto obj = jsonObject.getObject();

                pos = Utils::Point<double>();
                pos.Deserialize(obj.at("Position"));
                range = Utils::getOrThrow<double>(obj.at("Range"));
                name = Utils::getOrThrow<std::string>(obj.at("Name"));
                isAlive = Utils::getOrThrow<std::string>(obj.at("IsAlive")) == "true";
            }

            bool operator==(const BaseNpc& other) const {
                return getIsAlive() == other.getIsAlive() && getName() == other.getName() && getPos() == other.getPos() && getRange() == other.getRange();
            }
            ~BaseNpc() override = default;
    };

} // NPC

#endif //OOP_LAB_6_SRC_BASENPC_H_
