#include "Figure.h"

namespace Shape {
    std::ostream &operator<<(std::ostream &os, const Figure &figure) {
        for (auto point : figure.points){
            os << "x: " << point.x << " y: " << point.y << std::endl;
        }
        return os;
    }

    std::istream &operator>>(std::istream &is, Figure &figure) {
        int n;
        std::cout << "Enter the amount of points: ";
        is >> n;
        figure.points.clear();
        for (auto i = 0; i < n; ++i){
            auto p = Point{};
            is >> p;
            figure.points.push_back(p);
        }
        return is;
    }

    Point Figure::get_center() {
        if (points.empty()) throw std::invalid_argument("get_center is called on empty figure");
        double x {0}, y{0};

        for (auto& p: points){
            x += p.x;
            y += p.y;
        }

        return Point{x/static_cast<double>(points.size()), y/static_cast<double>(points.size())};
    }

    Figure::Figure(const Figure &figure) {
        for (auto& p: figure.points){
            points.push_back(Point{p.x, p.y});
        }
    }

    Figure::Figure(Shape::Figure &&figure)  noexcept {
        points = std::move(figure.points);
    }

    Figure::Figure(std::initializer_list<Point> pts) {
        for (auto& p: pts){
            points.push_back(Point{p.x, p.y});
        }
    }

    Figure &Figure::operator=(const Figure &other) {
        auto figure = Figure(other);
        points = std::move(figure.points);
        return *this;
    }

    Figure &Figure::operator=(Figure &&other) noexcept {
        points = std::move(other.points);
        return *this;
    }

    bool Figure::operator==(const Figure &other) const {
        if (points.size() != other.points.size()) return false;
        for(auto& p : points){
            auto flag = false;
            for (auto& p1 : other.points){
                if (p1.x == p.x && p.y == p1.y){
                    flag = true;
                    break;
                }
            }

            if (!flag) return false;
        }
        return true;
    }

    Figure::operator double() const {
        return 0;
    }
}