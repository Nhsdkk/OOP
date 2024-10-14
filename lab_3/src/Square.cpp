#include "Square.h"

namespace Shape {
    Square::Square(double l, Point &center) : l(l) {
        double l2 {l/2};

        points.push_back(Point{center.x + l2, center.y + l2});
        points.push_back(Point{center.x + l2, center.y - l2});
        points.push_back(Point{center.x - l2, center.y + l2});
        points.push_back(Point{center.x - l2, center.y - l2});

        bl = Point{center.x - l2, center.y - l2};
        tr = Point{center.x + l2, center.y + l2};
    }

    Square::Square(Point &p1, Point &p2) {
        l = std::abs(p1.x - p2.x);
        double minX {std::min(p1.x, p2.x)}, minY {std::min(p1.y, p2.y)};

        points.push_back(p1);
        points.push_back(p2);
        points.push_back(Point{minX + l, minY});
        points.push_back(Point{minX, minY + l});

        tr = Point{minX + l, minY + l};
        bl = Point{minX, minY};
    }

    Square::Square(std::initializer_list<Point> pts) : Figure(pts) {
        double minX, minY, maxX, maxY;
        for (auto& p : pts){
            minX = std::min(minX, p.x);
            maxX = std::max(maxX, p.x);
            minY = std::min(minY, p.y);
            maxY = std::max(maxY, p.y);
        }

        l = maxX - minX;

        tr = Point{maxX, maxY};
        bl = Point{minX, minY};
    }

    Square::Square(Square &&square) noexcept {
        l = square.l;

        tr = square.tr;
        bl = square.bl;

        points = std::move(square.points);
    }

    Square::Square(const Square &square) : Figure(square) {
        l = square.l;
        tr = square.tr;
        bl = square.bl;
    }

    Square &Square::operator=(const Square &other) {
        auto copy = Square(other);
        l = copy.l;
        tr = copy.tr;
        bl = copy.bl;
        points = std::move(copy.points);
        return *this;
    }

    Square &Square::operator=(Square &&other) noexcept {
        l = other.l;
        tr = other.tr;
        bl = other.bl;
        points = std::move(other.points);
        return *this;
    }

    std::istream &operator>>(std::istream &is, Square &square) {
        Point p{};
        square.points.clear();

        std::cout << "Enter length of the square side: ";
        is >> square.l;
        std::cout << "Bottom left point" << std::endl;
        is >> p;

        square.bl = p;
        square.tr = Point{p.x + square.l, p.y + square.l};

        square.points.push_back(square.tr);
        square.points.push_back(Point{p.x + square.l, p.y - square.l});
        square.points.push_back(Point{p.x - square.l, p.y + square.l});
        square.points.push_back(square.bl);

        return is;
    }

    bool Square::operator==(const Square &square) const {
        return l == square.l && bl == square.bl && tr == square.tr;
    }

    Square::operator double() const {
        return l*l;
    }

}