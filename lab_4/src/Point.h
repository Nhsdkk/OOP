#pragma once

#include <type_traits>
#include <cstdio>
#include <iosfwd>
#include <cmath>

namespace Shape {
    const auto eps = 1e-15;

    template <typename T>
    concept Numeric = std::is_scalar_v<T>;

    template <Numeric T>
    class Point {
        public:
            T x;
            T y;
            Point() : x(0), y(0){}
            Point(const T& _x, const T& _y): x(_x), y(_y){}
            Point(const Point<T>& point): x(point.x), y(point.y){}
            Point(Point<T>&& point) noexcept{
                x = std::move(point.x);
                y = std::move(point.y);
            }

            ~Point() = default;

            bool operator== (const Point& other) const{
                return std::fabs(x - other.x) < eps && std::fabs(y - other.y) < eps;
            }

            friend std::istream& operator>>(std::istream& is, Point<T>& point){
                std::cout << "Enter x and y of the point: ";
                is >> point.x >> point.y;
                return is;
            }

    };

}
