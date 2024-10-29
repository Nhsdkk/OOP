#pragma once
#include <vector>
#include <ostream>
#include <iostream>
#include <cmath>
#include <limits>
#include <memory>
#include "Point.h"

namespace Shape {
    template <Numeric T>
    class Figure {
        protected:
            std::vector<std::unique_ptr<Point<T>>> points;
        public:
            Figure() : points({}) {}
            Figure(std::initializer_list<Point<T>> pts){
                for (auto p: pts){
                    points.emplace_back(std::make_unique<Point<T>>(p));
                }
            }

            Figure(const Figure<T>& figure) {
                for (auto& p : figure.points){
                    points.emplace_back(
                        std::make_unique<Point<T>>(Point(p->x, p->y)
                        )
                    );
                }
            }
            Figure(Figure<T>&& figure) noexcept{
                points = std::move(figure.points);
            }
            Figure& operator=(const Figure<T>& other){
                auto figure = Figure(other);
                points = std::move(figure.points);
                return *this;
            }
            Figure& operator=(Figure<T>&& other)  noexcept {
                points = std::move(other.points);
                return *this;
            }

            Point<T> operator[](size_t idx){
                auto p = points.at(idx);
                return Point(p.x, p.y);
            }

            friend std::ostream& operator<< (std::ostream& os, const Figure<T>& figure){
                for (auto point : figure.points){
                    os << "x: " << point.x << " y: " << point.y << std::endl;
                }
                return os;
            }
            friend std::istream& operator>> (std::istream& is, Figure<T>& figure){
                int n;
                std::cout << "Enter the amount of points: ";
                is >> n;
                figure.points.clear();
                for (auto i = 0; i < n; ++i){
                    auto p = Point<T>{};
                    is >> p;
                    figure.points.emplace_back(std::make_unique(p));
                }
                return is;
            }

            virtual bool operator==(const Figure<T>& other) const {
                if (points.size() != other.points.size()) return false;
                for(auto& p : points){
                    auto flag = false;
                    for (auto& p1 : other.points){
                        if (*p1 == *p){
                            flag = true;
                            break;
                        }
                    }

                    if (!flag) return false;
                }
                return true;
            }

            virtual Point<double> get_center(){
                if (points.empty()) throw std::invalid_argument("get_center is called on empty figure");
                double x {0}, y{0};

                for (auto& p: points){
                    x += p->x;
                    y += p->y;
                }

                return Point{x/static_cast<double>(points.size()), y/static_cast<double>(points.size())};
            }

            virtual explicit operator double()const {
                double area = 0;
                for (int i = 0; i < points.size() - 1; ++i) {
                    area += points[i]->x * points[i + 1]->y - points[i + 1]->x * points[i]->y;
                }
                return 0.5 * std::abs(area);
            }

            virtual ~Figure() = default;
    };

}
