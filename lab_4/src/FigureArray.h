#pragma once

#include <memory>
#include "Figure.h"
#include "Square.h"
#include "Triangle.h"
#include "Octagon.h"

namespace Shape {
    size_t calculate_capacity(size_t newSize) {
        return static_cast<size_t>(std::pow(2, std::ceil(std::log2(newSize))));
    }

    template<class T> struct is_pointer { enum {Value = false}; };
    template<class T> struct is_pointer<T*> { enum {Value = true};};
    template<class T> struct is_pointer<std::unique_ptr<T>> { enum {Value = true};};
    template<class T> struct is_pointer<std::shared_ptr<T>> { enum {Value = true};};
    template<class T> struct is_pointer<std::weak_ptr<T>> { enum {Value = true};};

    template<class T> struct remove_pointer { typedef T type; };
    template<class T> struct remove_pointer<T*> { typedef T type; };
    template<class T> struct remove_pointer<std::unique_ptr<T>> { typedef T type; };
    template<class T> struct remove_pointer<std::shared_ptr<T>> { typedef T type; };
    template<class T> struct remove_pointer<std::weak_ptr<T>> { typedef T type; };


    template<class T, class U>
    concept FigureOrPtr = std::derived_from<typename remove_pointer<T>::type, Figure<U>>;

    template<class T, class U>
    requires FigureOrPtr<T, U>
    class FigureArray {
        std::unique_ptr<T[]> figures;
        double totalArea;
        size_t size, capacity;
        explicit FigureArray(size_t size) : size(size) {
            totalArea = 0;
            capacity = calculate_capacity(size);
            figures = std::make_unique<T[]>(capacity);
        }

        public:
            FigureArray() : figures(nullptr), size(0), capacity(0), totalArea(0) {};
            FigureArray(std::initializer_list<T> list) : FigureArray(static_cast<size_t>(list.size())) {
                auto i = 0;
                for (auto& fig : list){
                    figures[i++] = fig;
                    totalArea += double(*fig);
                }
            }
            
            explicit FigureArray(const FigureArray<T, U>& array) : FigureArray(array.size){
                totalArea = array.totalArea;
                capacity = array.capacity;
                for (auto i = 0; i < size; ++i){
                    figures[i] = is_pointer<T>::Value ? *array.figures[i] : array.figures[i];
                }
            }

            FigureArray(FigureArray<T, U>&& array) noexcept : totalArea(array.totalArea), size(array.size), capacity(array.capacity){
                figures = std::move(array.figures);

                array.figures = nullptr;
                array.size = 0;
                array.capacity = 0;
                array.totalArea = 0;
            }

            FigureArray& operator=(const FigureArray& array){
                auto copy = FigureArray(array);

                figures = std::move(copy.figures);
                size = copy.size;
                capacity = copy.capacity;
                totalArea = copy.totalArea;

                copy.figures = nullptr;
                return *this;
            }

            FigureArray& operator=(FigureArray&& array) noexcept {
                figures = std::move(array.figures);

                array.figures = nullptr;
                array.size = 0;
                array.capacity = 0;
                array.totalArea = 0;

                return *this;
            }

            void push_back(T figure) requires (!std::is_pointer_v<T>){
              if (capacity == 0){
                  figures = std::make_unique<T[]>(1);
                  capacity = 1;
              }

              if (size == capacity){
                  capacity = calculate_capacity(size + 1);
                  auto fig1 = std::move(figures);
                  figures = std::make_unique<T[]>(capacity);

                  for (auto i = 0; i < size; ++i){
                      figures[i] = std::move(fig1[i]);
                  }
              }

              figures[size] = std::move(figure);
              size++;

              totalArea += double (figure);
            }

            void push_back(T figure) requires (std::is_pointer_v<T>){
                if (capacity == 0){
                    figures = std::make_unique<T[]>(1);
                    capacity = 1;
                }

                if (size == capacity){
                    capacity = calculate_capacity(size + 1);
                    auto fig1 = std::move(figures);
                    figures = std::make_unique<T[]>(capacity);

                    for (auto i = 0; i < size; ++i){
                        figures[i] = std::move(fig1[i]);
                    }
                }

                figures[size] = std::move(figure);
                size++;

                totalArea += double (*figure);
            }

            void remove_at(size_t idx) requires (std::is_pointer_v<T>){
                if (idx >= size) throw std::out_of_range("Invalid index");
                totalArea -= double (*figures[idx]);
                for (size_t i = idx; i < size - 1; ++i){
                    figures[i] = std::move(figures[i + 1])  ;
                }
            }

            void remove_at(size_t idx) requires(!std::is_pointer_v<T>){
              if (idx >= size) throw std::out_of_range("Invalid index");
              totalArea -= double (figures[idx]);
              for (size_t i = idx; i < size - 1; ++i){
                  figures[i] = std::move(figures[i + 1])  ;
              }
            }

            size_t get_size() const{
                return size;
            }
            size_t get_capacity() const{
                return size;
            }

            double get_summary_area() const {
                return totalArea;
            }

            T operator[](size_t idx) const {
                if (idx >= size) throw std::out_of_range("Invalid index");
                return figures[idx];
            }

            ~FigureArray() = default;
    };

}