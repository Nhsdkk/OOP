#ifndef OOP_LAB_3_SRC_FIGURE_H_
#define OOP_LAB_3_SRC_FIGURE_H_

#include <vector>
#include <ostream>
#include <iostream>

namespace Shape {

    struct Point {
      double x, y;
      bool operator== (const Point& other) const{
          return x == other.x && y == other.y;
      }
      friend std::istream& operator>>(std::istream& is, Point& point){
          std::cout << "Enter x and y of the point: ";
          is >> point.x >> point.y;
          return is;
      }
    };

    class Figure {
        protected:
            std::vector<Point> points;
        public:
            Figure() = default;
            Figure(std::initializer_list<Point> points);

            Figure(const Figure& figure);
            Figure(Figure&& figure) noexcept;
            Figure& operator=(const Figure& other);
            Figure& operator=(Figure&& other)  noexcept ;

            friend std::ostream& operator<< (std::ostream& os, const Figure& figure);
            friend std::istream& operator>> (std::istream& is, Figure& figure);

            virtual bool operator==(const Figure& other) const;

            virtual Point get_center();
            virtual explicit operator double()const;

            virtual ~Figure() = default;
    };

}

#endif