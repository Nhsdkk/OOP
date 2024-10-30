#pragma once
#include "Figure.h"
#include <cmath>
#include <numbers>

namespace Shape {

    template <Numeric T>
    class Triangle : public Figure<T> {
        double l;
        using Figure<T>::points;
        public:
            Triangle() : Figure<T>({
                Point<T>{0,0},
                Point<T>{0,2},
                Point<T>{1,std::sqrt(3)}
            }), l(2) {}
            Triangle(std::initializer_list<Point<T>> p) : Figure<T>(p) {
                l = std::sqrt(std::pow(points[0]->x - points[1]->x, 2) + std::pow(points[0]->y - points[1]->y, 2));
            }

            Triangle(double l, const Point<T> &center) : l(l) {
                double h {l * std::numbers::sqrt3 / 2.0};

                points.emplace_back(std::make_unique<Point<T>>(Point<T>{center.x - l / 2.0, center.y - h / 3.0}));
                points.emplace_back(std::make_unique<Point<T>>(Point<T>{center.x + l / 2.0, center.y - h / 3.0}));
                points.emplace_back(std::make_unique<Point<T>>(Point<T>{center.x, center.y + 2.0 * h / 3.0}));
            }

            Triangle(const Triangle<T>& triangle) : Figure<T>(triangle) {
                l = triangle.l;
            }
            Triangle(Triangle<T>&& triangle) noexcept{
                l = triangle.l;
                points = std::move(triangle.points);
            }
            Triangle<T>& operator=(const Triangle<T>& other){
                auto cpy = Triangle(other);
                l = cpy.l;
                points = std::move(cpy.points);
                return *this;
            }
            Triangle<T>& operator=(Triangle<T>&& other)  noexcept{
                l = other.l;
                points = std::move(other.points);
            }

            friend std::istream& operator>> (std::istream& is, Triangle<T>& triangle){
                triangle.points.clear();
                for (auto i = 0; i < 3; ++i){
                    auto p = Point<T>{};
                    is >> p;
                    triangle.points.emplace_back(std::make_unique(p));
                }
                return is;
            }

            explicit operator double()const override {
                return pow(l, 2) * std::sqrt(3) / 4;
            }
    };

}
