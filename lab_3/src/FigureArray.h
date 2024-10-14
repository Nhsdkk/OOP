#pragma once

#include "Figure.h"
#include <cmath>

#ifndef OOP_LAB_3_SRC_FIGUREARRAY_H_
#define OOP_LAB_3_SRC_FIGUREARRAY_H_


namespace Shape {
    size_t calculate_capacity(size_t newSize);

    class FigureArray {
        Figure** figures;
        double totalArea;
        size_t size, capacity;
        explicit FigureArray(size_t size);

        public:
            FigureArray() : figures(nullptr), size(0), capacity(0), totalArea(0) {};
            FigureArray(std::initializer_list<Figure*> list);

            void push_back(Figure* figure);
            void remove_at(size_t idx);

            size_t get_size() const{
                return size;
            }
            size_t get_capacity() const{
                return size;
            }

            double get_total_area() const {
                return totalArea;
            }

            Figure* operator[](size_t idx) const;

            ~FigureArray();
    };

}

#endif
