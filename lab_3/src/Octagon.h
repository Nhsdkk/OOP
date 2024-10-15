#ifndef OOP_LAB_3_SRC_OCTAGON_H_
#define OOP_LAB_3_SRC_OCTAGON_H_

#include "Figure.h"
#include <cmath>

namespace Shape {

    class Octagon : public Figure {
        double l;
     public:
        Octagon() : Figure({
            Point{0,0},
            Point{-1,0},
            Point{-1 - 1 / std::sqrt(2),1/std::sqrt(2)},
            Point{-1 - 1 / std::sqrt(2),1 + 1/std::sqrt(2)},
            Point{-1,1 + 2 * 1/std::sqrt(2)},
            Point{0,1 + 2 * 1/std::sqrt(2)},
            Point{1 / std::sqrt(2),1 + 1/std::sqrt(2)},
            Point{1 / std::sqrt(2),1/std::sqrt(2)},
        }), l(1) {}
        Octagon(std::initializer_list<Point> points);
        Octagon(double l, const Point& center);

        Octagon(const Octagon& octagon) = default;
        Octagon(Octagon&& octagon) noexcept = default;
        Octagon& operator=(const Octagon& other) = default;
        Octagon& operator=(Octagon&& other)  noexcept = default;

        friend std::istream& operator>> (std::istream& is, Octagon& octagon);

        explicit operator double()const override;
    };  

}

#endif
