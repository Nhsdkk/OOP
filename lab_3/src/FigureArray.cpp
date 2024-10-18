#include "FigureArray.h"

namespace Shape {
    size_t calculate_capacity(size_t newSize){
        return static_cast<size_t>(std::pow(2, std::ceil(std::log2(newSize))));
    }

    FigureArray::FigureArray(const std::initializer_list<Figure *> list) : FigureArray(static_cast<size_t>(list.size())) {
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

    void FigureArray::remove_at(const size_t idx) {
        if (idx >= size) throw std::out_of_range("Invalid index");
        totalArea -= double(*figures[idx]);
        for (size_t i = idx; i < size - 1; ++i){
            figures[i] = figures[i + 1];
        }
    }

    Figure *FigureArray::operator[](const size_t idx) const {
        if (idx >= size) throw std::out_of_range("Invalid index");
        return figures[idx];
    }

    FigureArray::~FigureArray() {
        std::free(figures);
        figures = nullptr;
    }

    FigureArray::FigureArray(const size_t size) : size(size) {
        totalArea = 0;
        capacity = calculate_capacity(size);
        figures = static_cast<Figure **>(std::malloc(sizeof(Figure *) * capacity));
    }

    FigureArray::FigureArray(FigureArray &&array) noexcept : totalArea(array.totalArea), size(array.size), capacity(array.capacity) {
        figures = array.figures;

        array.figures = nullptr;
        array.size = 0;
        array.capacity = 0;
        array.totalArea = 0;
    }

    FigureArray::FigureArray(const FigureArray &array) : totalArea(array.totalArea), size(array.size), capacity(array.capacity) {
        figures = static_cast<Figure**>(std::malloc(sizeof(Figure*) * array.size));
        for (auto i = 0; i < array.size; ++i){
            figures[i] = array[i];
        }
    }

    FigureArray &FigureArray::operator=(FigureArray &&array) noexcept {
        figures = array.figures;

        array.figures = nullptr;
        array.size = 0;
        array.capacity = 0;
        array.totalArea = 0;

        return *this;
    }

    FigureArray &FigureArray::operator=(const FigureArray &array) {
        auto copy = FigureArray(array);

        figures = copy.figures;
        size = copy.size;
        capacity = copy.capacity;
        totalArea = copy.totalArea;

        copy.figures = nullptr;
        return *this;
    }
}