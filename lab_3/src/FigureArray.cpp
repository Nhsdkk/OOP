#include "FigureArray.h"

namespace Shape {
    size_t calculate_capacity(size_t newSize){
        return static_cast<size_t>(std::pow(2, std::ceil(std::log2(newSize))));
    }

    FigureArray::FigureArray(std::initializer_list<Figure *> list) : FigureArray(static_cast<size_t>(list.size())) {
        auto i = 0;
        for (auto& fig : list){
            figures[i++] = fig;
            totalArea += double(*fig);
        }
    }

    void FigureArray::push_back(Figure* figure) {
        if (capacity == 0){
            figures = static_cast<Figure **>(std::malloc(sizeof(Figure *)));
            capacity = 1;
        }

        if (size == capacity){
            capacity = calculate_capacity(size + 1);
            figures = static_cast<Figure **>(std::realloc(figures, sizeof(Figure *) * capacity));
        }

        figures[size] = figure;
        size++;

        totalArea += double(*figure);
    }

    void FigureArray::remove_at(size_t idx) {
        if (idx >= size) throw std::out_of_range("Invalid index");
        totalArea -= double(*figures[idx]);
        for (size_t i = idx; i < size - 1; ++i){
            figures[i] = figures[i + 1];
        }
    }

    Figure *FigureArray::operator[](size_t idx) const {
        if (idx >= size) throw std::out_of_range("Invalid index");
        return figures[idx];
    }

    FigureArray::~FigureArray() {
        std::free(figures);
        figures = nullptr;
    }

    FigureArray::FigureArray(size_t size) : size(size) {
        totalArea = 0;
        capacity = calculate_capacity(size);
        figures = static_cast<Figure **>(std::malloc(sizeof(Figure *) * capacity));
    }
}