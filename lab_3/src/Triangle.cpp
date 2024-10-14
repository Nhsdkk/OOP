#include "Triangle.h"

namespace Shape {
    std::istream &operator>>(std::istream &is, Triangle &triangle) {
        triangle.points.clear();
        for (auto i = 0; i < 3; ++i){
            auto p = Point{};
            is >> p;
            triangle.points.push_back(p);
        }
        return is;
    }

    Triangle::operator double() const {
//        auto p1 = points[0];
//        auto p2 = points[0];
//        auto p3 = points[0];
//        return 0.5 * std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
        return pow(l, 2) * std::sqrt(3) / 4;
    }

    Triangle::Triangle(double l, const Point &center) : l(l) {
        double h {l * std::sqrt(3) / 2};

        points.push_back(Point{center.x - l / 2, center.y - h / 3});
        points.push_back(Point{center.x + l / 2, center.y - h / 3});
        points.push_back(Point{center.x, center.y + 2 * h / 3});
    }

    Triangle::Triangle(std::initializer_list<Point> p) : Figure(p) {
        l = std::sqrt(std::pow(points[0].x - points[1].x, 2) + std::pow(points[0].y - points[1].y, 2));
    }

    Triangle::Triangle(const Triangle &triangle) : Figure(triangle) {
        l = triangle.l;
    }

    Triangle::Triangle(Triangle &&triangle) noexcept {
        l = triangle.l;
        points = std::move(triangle.points);
    }

    Triangle& Triangle::operator=(const Triangle &other) {
        auto cpy = Triangle(other);
        l = cpy.l;
        points = std::move(cpy.points);
        return *this;
    }

    Triangle &Triangle::operator=(Triangle &&other) noexcept {
        l = other.l;
        points = std::move(other.points);
        return *this;
    }
}