#pragma once
#include "Figure.h"
#include <cmath>
#include <numbers>

namespace Shape {
    template<Numeric T>
    class Octagon : public Figure<T> {
        double l;
        using Figure<T>::points;
        public:
            Octagon() : Figure<T>({
                Point<T>{0,0},
                Point<T>{-1,0},
                Point<T>{-1 - 1 / std::sqrt(2),1/std::sqrt(2)},
                Point<T>{-1 - 1 / std::sqrt(2),1 + 1/std::sqrt(2)},
                Point<T>{-1,1 + 2 * 1/std::sqrt(2)},
                Point<T>{0,1 + 2 * 1/std::sqrt(2)},
                Point<T>{1 / std::sqrt(2),1 + 1/std::sqrt(2)},
                Point<T>{1 / std::sqrt(2),1/std::sqrt(2)},
            }), l(1) {}

            Octagon(std::initializer_list<Point<T>> p): Figure<T>(p) {
                double dx {points[0]->x - points[1]->x}, dy {points[0]->y - points[1]->y};
                l = dx * dx + dy * dy;
            }

            Octagon(const Octagon<T>& octagon): Figure<T>(octagon) {
                l = octagon.l;
            }
            Octagon(Octagon<T>&& octagon) noexcept {
                l = octagon.l;
                points = std::move(octagon.points);
            }
            Octagon& operator=(const Octagon<T>& other) {
                auto copy = Octagon(other);
                l = copy.l;
                points = std::move(copy.points);
                return *this;
            }
            Octagon& operator=(Octagon<T>&& other) noexcept {
                l = other.l;
                points = std::move(other.points);
                return *this;
            }

            friend std::istream& operator>> (std::istream& is, Octagon<T>& octagon) {
                std::cout << "Enter l: ";
                is >> octagon.l;
                std::cout << "Enter center of the figure: ";
                auto center = Point<T>{};
                is >> center;

                auto delta = octagon.l / std::numbers::sqrt2;
                auto startP = Point{center.x - octagon.l / 2, center.y - octagon.l/2 - delta};

                octagon.points = {
                    std::make_unique(startP),
                    std::make_unique(Point<T>{startP.x - octagon.l, startP.y}),
                    std::make_unique(Point<T>{startP.x - octagon.l - delta, startP.y + delta}),
                    std::make_unique(Point<T>{startP.x - octagon.l - delta, startP.y + delta + octagon.l}),
                    std::make_unique(Point<T>{startP.x - octagon.l, startP.y + 2 * delta + octagon.l}),
                    std::make_unique(Point<T>{startP.x, startP.y + 2 * delta + octagon.l}),
                    std::make_unique(Point<T>{startP.x + delta, startP.y + delta + octagon.l}),
                    std::make_unique(Point<T>{startP.x + delta, startP.y + delta})
                };

                return is;
            }

            explicit operator double()const override {
                return 2 * l * l * (std::numbers::sqrt2 + 1);
            }
    };  

}
