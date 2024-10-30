#pragma once
#include "Figure.h"
namespace Shape {

template <Numeric T>
class Square : public Figure<T> {
    private:
        T l;
        using Figure<T>::points;
        std::unique_ptr<Point<T>> bl{}, tr{};
    public:
        Square() : Figure<T>({
            Point<T>{0,0},
            Point<T>{0,1},
            Point<T>{1,1},
            Point<T>{1,0}
        }), l(1) {}

        Square(const Point<T> &center, const double l) : l(l) {
            double l2 {l/2};

            points.emplace_back(std::make_unique<Point<T>>(Point<T>{center.x + l2, center.y + l2}));
            points.emplace_back(std::make_unique<Point<T>>(Point<T>{center.x + l2, center.y - l2}));
            points.emplace_back(std::make_unique<Point<T>>(Point<T>{center.x - l2, center.y + l2}));
            points.emplace_back(std::make_unique<Point<T>>(Point<T>{center.x - l2, center.y - l2}));

            bl = std::make_unique<Point<T>>(Point<T>{center.x - l2, center.y - l2});
            tr = std::make_unique<Point<T>>(Point<T>{center.x + l2, center.y + l2});
        }

        Square(std::initializer_list<Point<T>> pts) : Figure<T>(pts) {
            T minX {std::numeric_limits<T>::max()},
            minY {std::numeric_limits<T>::max()},
            maxX {std::numeric_limits<T>::min()},
            maxY {std::numeric_limits<T>::min()};
            for (auto& p : pts){
                minX = std::min(minX, p.x);
                maxX = std::max(maxX, p.x);
                minY = std::min(minY, p.y);
                maxY = std::max(maxY, p.y);
            }

            l = maxX - minX;

            tr = std::make_unique<Point<T>>(Point{maxX, maxY});
            bl = std::make_unique<Point<T>>(Point{minX, minY});
        }

        Square(const Point<T>& p1, const Point<T>& p2): Figure<T>(){
            l = std::abs(p1.x - p2.x);
            T minX {std::min(p1.x, p2.x)}, minY {std::min(p1.y, p2.y)};

            points.emplace_back(std::make_unique<Point<T>>(p1));
            points.emplace_back(std::make_unique<Point<T>>(p2));
            points.emplace_back(std::make_unique<Point<T>>(Point<T>{minX + l, minY}));
            points.emplace_back(std::make_unique<Point<T>>(Point<T>{minX, minY + l}));

            tr = std::make_unique<Point<T>>(Point<T>{minX + l, minY + l});
            bl = std::make_unique<Point<T>>(Point<T>{minX, minY});
        }

        Square(const Square& square): Figure<T>(square) {
            l = square.l;
            tr = std::make_unique<Point<T>>(Point(square.tr->x, square.tr->y));
            bl = std::make_unique<Point<T>>(Point(square.bl->x, square.bl->y));
        }

        Square(Square<T>&& square) noexcept {
            l = square.l;

            tr = std::move(square.tr);
            bl = std::move(square.bl);

            points = std::move(square.points);
        }

        Square& operator=(const Square<T>& other){
            auto copy = Square(other);
            l = copy.l;
            tr = std::move(copy.tr);
            bl = std::move(copy.bl);
            points = std::move(copy.points);
            return *this;
        }

        Square& operator=(Square<T>&& other)  noexcept {
            l = other.l;
            tr = std::move(other.tr);
            bl = std::move(other.bl);
            points = std::move(other.points);
            return *this;
        }

        friend std::istream& operator>> (std::istream& is, Square<T>& square) {
            Point<T> p{};
            square.points.clear();

            std::cout << "Enter length of the square side: ";
            is >> square.l;
            std::cout << "Bottom left point" << std::endl;
            is >> p;

            square.bl = std::make_unique(p);
            square.tr = std::make_unique(Point<T>{p.x + square.l, p.y + square.l});

            square.points.emplace_back(std::make_unique(square.tr));
            square.points.emplace_back(std::make_unique(Point<T>{p.x + square.l, p.y - square.l}));
            square.points.emplace_back(std::make_unique(Point<T>{p.x - square.l, p.y + square.l}));
            square.points.emplace_back(std::make_unique(square.bl));

            return is;
        }

        bool operator==(const Square<T>& square) const {
            return l == square.l && bl == square.bl && tr == square.tr;
        }

        explicit operator double()const override {
            return l*l;
        }
    };

}
