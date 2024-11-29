//
// Created by nikit on 11/24/2024.
//

#ifndef OOP_LAB_6_SRC_POINT_H_
#define OOP_LAB_6_SRC_POINT_H_

#include <istream>
#include <cmath>
#include <iostream>
#include "ISerializable.h"
namespace Utils {

template <class T>
requires std::is_arithmetic_v<T>
class Point : public ISerializable {
    T x, y;

    public:
        Point() = default;
        Point(T x, T y) : x(x), y(y) {}
        Point(const Point& other) : x(other.x), y(other.y){}
        Point(Point&& other) noexcept : x(other.x), y(other.y){}
        Point& operator=(const Point& other) {
            x = other.x;
            y = other.y;
            return *this;
        };
        Point& operator=(Point&& other) noexcept {
            x = other.x;
            y = other.y;
            return *this;
        };

        bool operator== (const Point& other) const{
            return std::fabs(x - other.x) < std::numeric_limits<T>::epsilon() && std::fabs(y - other.y) < std::numeric_limits<T>::epsilon();
        }

        friend std::istream& operator>>(std::istream& is, Point& point){
            std::cout << "Enter x and y of the point: ";
            is >> point.x >> point.y;
            return is;
        }

        friend std::ostream & operator>>(std::ostream & os, Point& point){
            os << "X: " << point.x << " Y: " << point.y;
            return os;
        }

        std::string Serialize() const override {
            std::ostringstream oss;
            oss << "{" << std::endl;
            oss << "X=" << x << std::endl;
            oss << "Y=" << y << std::endl;
            oss << "}";
            return oss.str();
        }

        void Deserialize(const std::string& values) override {
            auto m = toMap(values);

            x = getOrThrow<double>(m["X"]);
            y = getOrThrow<double>(m["Y"]);
        }
};

} // Utils

#endif //OOP_LAB_6_SRC_POINT_H_