//
// Created by nikit on 12/1/2024.
//

#ifndef OOP_LAB_6_SRC_UTILS_VEC2D_H_
#define OOP_LAB_6_SRC_UTILS_VEC2D_H_

#include <type_traits>
#include <cmath>
#include <iostream>
#include "ISerializable.h"
#include "Point.h"

namespace Utils {

template<class T>
requires std::is_arithmetic_v<T>
     class Vec2D : public Utils::ISerializable {
        T dx, dy;
     public:
        Vec2D() = default;
        Vec2D(T dx, T dy) : dx(dx), dy(dy) {}
        Vec2D(const Point<T>& p1, const Point<T>& p2) : dx(static_cast<T>(std::abs(p1.getX() - p2.getX()))), dy(static_cast<T>(std::abs(p1.getY() - p2.getY()))) {}
        Vec2D(const Vec2D& other) = default;
        Vec2D(Vec2D&& other) noexcept = default;
        Vec2D& operator=(const Vec2D& other) = default;
        Vec2D& operator=(Vec2D&& other) noexcept {
            dx = other.dx;
            dy = other.dy;
            return *this;
        };

        double getLength() const { return std::sqrt(dx * dx + dy * dy); }
        T getDx() const { return dx; }
        T getDy() const { return dy; }

        bool operator== (const Vec2D& other) const{
            return std::fabs(dx - other.dx) < std::numeric_limits<T>::epsilon() && std::fabs(dy - other.dy) < std::numeric_limits<T>::epsilon();
        }
        bool operator< (const Vec2D& other) const { return getLength() < other.getLength(); }
        friend std::istream& operator>>(std::istream& is, Vec2D& Vec2D){
            std::cout << "Enter dx and dy of the Vec2D: ";
            is >> Vec2D.dx >> Vec2D.dy;
            return is;
        }
        friend std::ostream & operator>>(std::ostream & os, Vec2D& Vec2D){
            os << "dX: " << Vec2D.dx << " dY: " << Vec2D.dy;
            return os;
        }

        std::string serialize() const override {
            std::ostringstream oss;
            oss << "{" << std::endl;
            oss << "dX=" << dx << ";" << std::endl;
            oss << "dY=" << dy << ";" << std::endl;
            oss << "}";
            return oss.str();
        }

        void deserialize(const Json::JsonObject& jsonObject) override {
            if (jsonObject.getType() != Json::Map) throw std::invalid_argument("Can't parse value to point");
            auto obj = jsonObject.getObject();
            dx = obj.at("dX").getValue<double>();
            dy = obj.at("dY").getValue<double>();
        }

        ~Vec2D() override = default;
};

} // Utils

#endif //OOP_LAB_6_SRC_UTILS_VEC2D_H_
