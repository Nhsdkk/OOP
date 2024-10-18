#ifndef OOP_LAB_3_SRC_SQUARE_H_
#define OOP_LAB_3_SRC_SQUARE_H_

#include "Figure.h"
namespace Shape {

class Square : public Figure {
    private:
        double l;
        Point bl{}, tr{};
    public:
        Square() : Figure({Point{0,0}, Point{0,1}, Point{1,1}, Point{1,0}}), l(1) {}
        Square(std::initializer_list<Point> points);
        Square(double l, const Point& center);
        Square(const Point& p1, const Point& p2);

        Square(const Square& square);
        Square(Square&& square) noexcept;
        Square& operator=(const Square& other);
        Square& operator=(Square&& other)  noexcept ;

        friend std::istream& operator>> (std::istream& is, Square& square);

        bool operator==(const Square& square) const;

        explicit operator double()const override;
    };

}

#endif
