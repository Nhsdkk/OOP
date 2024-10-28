#ifndef OOP_LAB_3_SRC_TRIANGLE_H_
#define OOP_LAB_3_SRC_TRIANGLE_H_

#include "Figure.h"
#include <cmath>

namespace Shape {

    class Triangle : public Figure {
        double l;
        public:
            Triangle() : Figure({Point{0,0}, Point{0,2}, Point{1,std::sqrt(3)}}), l(2) {}
            Triangle(std::initializer_list<Point> points);
            Triangle(double l, const Point& center);

            Triangle(const Triangle& triangle);
            Triangle(Triangle&& triangle) noexcept;
            Triangle& operator=(const Triangle& other);
            Triangle& operator=(Triangle&& other)  noexcept;

            friend std::istream& operator>> (std::istream& is, Triangle& triangle);

            explicit operator double()const override;
    };

}

#endif
