//
// Created by nikit on 11/29/2024.
//

#ifndef OOP_LAB_6_SRC_VEC2D_H_
#define OOP_LAB_6_SRC_VEC2D_H_

#include <type_traits>
#include <istream>
#include <iostream>
#include "cmath"
#include "ISerializable.h"
namespace Utils {

template<class T>
requires std::is_arithmetic_v<T>
class Vec2D : public ISerializable {
    T dx, dy;

    double getLength() { return std::sqrt(dx * dx + dy * dy); }

    public:
        Vec2D() = default;
        Vec2D(T dx, T dy) : dx(dx), dy(dy) {}
        Vec2D(const Vec2D& other) : dx(other.dx), dy(other.dy){}
        Vec2D(Vec2D&& other) noexcept : dx(other.dx), dy(other.dy){}
        Vec2D& operator=(const Vec2D& other) {
            dx = other.dx;
            dy = other.dy;
            return *this;
        };
        Vec2D& operator=(Vec2D&& other) noexcept {
            dx = other.dx;
            dy = other.dy;
            return *this;
        };

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

        std::string Serialize() const override {
            std::ostringstream oss;
            oss << "{" << std::endl;
            oss << "dX=" << dx << std::endl;
            oss << "dY=" << dy << std::endl;
            oss << "}";
            return oss.str();
        }
    
        void Deserialize(const std::string& values) override {
            auto m = toMap(values);
    
            dx = getOrThrow<double>(m["dX"]);
            dy = getOrThrow<double>(m["dY"]);
        }
};

} // Utils

#endif //OOP_LAB_6_SRC_VEC2D_H_
