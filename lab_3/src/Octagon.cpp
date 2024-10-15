#include "Octagon.h"

namespace Shape {
    Octagon::Octagon(std::initializer_list<Point> p) : Figure(p) {
        l = std::sqrt(std::pow(points[0].x - points[1].x, 2) + std::pow(points[0].y - points[1].y, 2));
    }

    Octagon::operator double() const {
        return 2 * pow(l, 2) * (std::sqrt(2) + 1);
    }
    std::istream &operator>>(std::istream &is, Octagon &octagon) {
        std::cout << "Enter l: ";
        is >> octagon.l;
        std::cout << "Enter center of the figure: ";
        auto center = Point{};
        is >> center;

        auto delta = octagon.l / std::sqrt(2);
        auto startP = Point{center.x - octagon.l / 2, center.y - octagon.l/2 - delta};

        octagon.points = {
            startP,
            Shape::Point{startP.x - octagon.l, startP.y},
            Shape::Point{startP.x - octagon.l - delta, startP.y + delta},
            Shape::Point{startP.x - octagon.l - delta, startP.y + delta + octagon.l},
            Shape::Point{startP.x - octagon.l, startP.y + 2 * delta + octagon.l},
            Shape::Point{startP.x, startP.y + 2 * delta + octagon.l},
            Shape::Point{startP.x + delta, startP.y + delta + octagon.l},
            Shape::Point{startP.x + delta, startP.y + delta}
        };

        return is;
    }

    Octagon::Octagon(double l, const Point &center) : l(l) {
        auto delta = l / std::sqrt(2);
        auto startP = Point{center.x + l / 2, center.y - l/2 - delta};

        points = {
            startP,
            Shape::Point{startP.x - l, startP.y},
            Shape::Point{startP.x - l - delta, startP.y + delta},
            Shape::Point{startP.x - l - delta, startP.y + delta + l},
            Shape::Point{startP.x - l, startP.y + 2 * delta + l},
            Shape::Point{startP.x, startP.y + 2 * delta + l},
            Shape::Point{startP.x + delta, startP.y + delta + l},
            Shape::Point{startP.x + delta, startP.y + delta}
        };
    }

    Octagon::Octagon(const Octagon &octagon) : Figure(octagon) {
        l = octagon.l;
    }

    Octagon::Octagon(Octagon &&octagon) noexcept {
        l = octagon.l;
        points = std::move(octagon.points);
    }

    Octagon &Octagon::operator=(const Octagon &other) {
        auto copy = Octagon(other);
        l = copy.l;
        points = std::move(copy.points);
        return *this;
    }
    Octagon &Octagon::operator=(Octagon &&other) noexcept {
        l = other.l;
        points = std::move(other.points);
        return *this;
    }

}