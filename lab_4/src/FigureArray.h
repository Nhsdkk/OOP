#pragma once

namespace Shape {
    size_t calculate_capacity(size_t newSize);

    template<Numeric T>
    class FigureArray {
        Figure<T>** figures;
        double totalArea;
        size_t size, capacity;
        explicit FigureArray(size_t size);

        public:
            FigureArray() : figures(nullptr), size(0), capacity(0), totalArea(0) {};
            FigureArray(std::initializer_list<Figure<T>*> list);

            FigureArray(const FigureArray& array);
            FigureArray(FigureArray&& array) noexcept;
            FigureArray& operator=(const FigureArray& array);
            FigureArray& operator=(FigureArray&& array) noexcept;

            void push_back(Figure<T>* figure);
            void remove_at(size_t idx);

            size_t get_size() const{
                return size;
            }
            size_t get_capacity() const{
                return size;
            }

            double get_summary_area() const {
                return totalArea;
            }

            Figure<T>* operator[](size_t idx) const;

            ~FigureArray();
    };

}