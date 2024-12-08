#include "BaseNpc.h"
#include "../utils/RandomNumberGenerator.h"

constexpr int minDice = 0, maxDice = 6;

namespace {
    int rollDice() {
        std::random_device dev;
        Utils::RandomNumberGenerator rng(dev);
        return rng.generateInt(minDice, maxDice);
    }
}

namespace NPC {
    void BaseNpc::kill(const std::shared_ptr<BaseNpc>& victim) {
        std::lock_guard lock (mtx);
        if (!canAttack(victim)) return;

        auto attackerRoll = rollDice(), defenderRoll = rollDice();
        if (attackerRoll <= defenderRoll) return;

        isAlive = false;

        if (loggers.empty()) return;
        for (auto& logger : loggers)
            logger->log(std::format("{} of type {} got killed by {} of type {}", victim->getName(), victim->getType(), name, getType()));
    }

    void BaseNpc::move(const Utils::Vec2D<double>& moveVec) {
        if (std::abs(moveVec.getLength() - moveDistance) > std::numeric_limits<double>::epsilon()) throw std::invalid_argument(std::format("The distance is too long to move for {}", getType()));
        pos += std::pair<double, double>(moveVec.getDx(), moveVec.getDy());
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

    Utils::Point<int> BaseNpc::getPos() const { return pos; }
    double BaseNpc::getRange() const { return range; }
    std::string BaseNpc::getName() const { return name; }
    bool BaseNpc::getIsAlive() const { return isAlive; }
    double BaseNpc::getMoveDistance() const { return moveDistance; }

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
        oss << "MoveDistance=" << moveDistance << ";" << std::endl;
        oss << "Name=" << name << ";" << std::endl;
        oss << "IsAlive=" << (isAlive ? "true" : "false") << ";" << std::endl;
        oss << "}";
        return oss.str();
    }

    void BaseNpc::deserialize(const Json::JsonObject &jsonObject) {
        if (jsonObject.getType() != Json::Map) throw std::invalid_argument("Can't parse value to point");
        auto obj = jsonObject.getObject();

        pos = Utils::Point<int>();
        pos.deserialize(obj.at("Position"));
        range = obj.at("Range").getValue<double>();
        moveDistance = obj.at("MoveDistance").getValue<double>();
        name = obj.at("Name").getValue<std::string>();
        isAlive = obj.at("IsAlive").getValue<std::string>() == "true";
    }

    bool BaseNpc::operator==(const BaseNpc &other) const {
        return getIsAlive() == other.getIsAlive() && getName() == other.getName() && getPos() == other.getPos() && getRange() == other.getRange() && getMoveDistance() == other.getMoveDistance();
    }

    BaseNpc &BaseNpc::operator=(BaseNpc &&other) noexcept {
        pos = std::move(other.pos);
        range = other.range;
        name = std::move(other.name);
        isAlive = other.isAlive;
        loggers = std::move(other.loggers);
        return *this;
    }

    BaseNpc &BaseNpc::operator+=(const Utils::Vec2D<int> &vec) {
        pos += std::pair<int, int>(vec.getDx(), vec.getDy());
        return *this;
    }

    void BaseNpc::clearLoggers() {
        loggers.clear();
    }
} // NPC