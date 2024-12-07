//
// Created by nikit on 11/24/2024.
//

#include "BaseNpc.h"

namespace NPC {
    void BaseNpc::kill(const std::shared_ptr<BaseNpc>& victim) {
        if (!canAttack(victim)) return;
        isAlive = false;
        if (loggers.empty()) return;
        for (auto& logger : loggers)
            logger->log(std::format("{} of type {} got killed by {} of type {}", victim->getName(), victim->getType(), name, getType()));
    }

    void BaseNpc::attachLoggers(const std::vector<std::shared_ptr<Logger::ILogger>> &l) { loggers.insert(loggers.end(), l.begin(),l.end()); }
    void BaseNpc::detachLogger(const std::string &loggerName) {
        loggers.erase(
            std::remove_if(
                loggers.begin(),
                loggers.end(),
                [loggerName](const std::shared_ptr<Logger::ILogger>& item)
                { return item->getName() == loggerName; }
            ),
            loggers.end()
        );
    }

    Utils::Point<double> BaseNpc::getPos() const { return pos; }
    double BaseNpc::getRange() const { return range; }
    std::string BaseNpc::getName() const { return name; }
    bool BaseNpc::getIsAlive() const { return isAlive; }

    bool BaseNpc::canAttack(const std::shared_ptr<BaseNpc>& victim) const {
        auto vec = Utils::Vec2D(pos, victim->pos);
        if (vec.getLength() - range < std::numeric_limits<double>::epsilon() && victim->isAlive && isAlive) return true;
        return false;
    }

    std::string BaseNpc::serialize() const {
        std::ostringstream oss;
        oss << "{" << std::endl;
        oss << "Position=" << pos.serialize() << ";" << std::endl;
        oss << "Range=" << range << ";" << std::endl;
        oss << "Name=" << name << ";" << std::endl;
        oss << "IsAlive=" << (isAlive ? "true" : "false") << ";" << std::endl;
        oss << "}";
        return oss.str();
    }

    void BaseNpc::deserialize(const Json::JsonObject &jsonObject) {
        if (jsonObject.getType() != Json::Map) throw std::invalid_argument("Can't parse value to point");
        auto obj = jsonObject.getObject();

        pos = Utils::Point<double>();
        pos.deserialize(obj.at("Position"));
        range = obj.at("Range").getValue<double>();
        name = obj.at("Name").getValue<std::string>();
        isAlive = obj.at("IsAlive").getValue<std::string>() == "true";
    }

    bool BaseNpc::operator==(const BaseNpc &other) const {
        return getIsAlive() == other.getIsAlive() && getName() == other.getName() && getPos() == other.getPos() && getRange() == other.getRange();
    }

    BaseNpc &BaseNpc::operator=(BaseNpc &&other) noexcept {
        pos = std::move(other.pos);
        range = other.range;
        name = std::move(other.name);
        isAlive = other.isAlive;
        loggers = std::move(other.loggers);
        return *this;
    }
} // NPC