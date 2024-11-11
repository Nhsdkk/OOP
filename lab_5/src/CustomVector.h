#pragma once

#include <type_traits>
#include <memory_resource>
#include <memory>
#include <cmath>
#include <cstring>
#include "CustomIterator.h"

namespace CustomContainers {

    size_t calculate_capacity(size_t newSize){
        return static_cast<size_t>(std::pow(2, std::ceil(std::log2(newSize))));
    }

    template <class T, class alloc_t>
    requires std::is_default_constructible_v<T> && std::is_same_v<alloc_t, std::pmr::polymorphic_allocator<T>>
    class CustomVector {
        struct PolymorphicDeleter
        {
            void operator()(T *ptr) const
            {
            }
        };

        std::unique_ptr<T, PolymorphicDeleter> data;
        size_t size, capacity;
        alloc_t allocator;

        public:
            explicit CustomVector(alloc_t alloc = {}) : size(0), data(nullptr), capacity(0), allocator(alloc) {}
            explicit CustomVector(size_t n, alloc_t alloc = {}) : size(n), capacity(calculate_capacity(n)), allocator(alloc){
                data = std::unique_ptr<T, PolymorphicDeleter>(allocator.allocate(capacity), PolymorphicDeleter{});
            }
            explicit CustomVector(std::initializer_list<T> list, alloc_t alloc = {}) : size(list.size()), capacity(calculate_capacity(list.size())), allocator(alloc){
                data = std::unique_ptr<T, PolymorphicDeleter>(allocator.allocate(capacity), PolymorphicDeleter{});
                auto i = 0;
                for (auto & item: list){
                    data.get()[i] = item;
                    i++;
                }
            }

            CustomVector(const CustomVector& other) : size(other.size), capacity(other.capacity), allocator(other.allocator){
                data = std::unique_ptr<T, PolymorphicDeleter>(allocator.allocate(capacity), PolymorphicDeleter{});
                std::memcpy(data.get(), other.data.get(), size * sizeof (T));
            }

            CustomVector(CustomVector&& other) noexcept : size(other.size), capacity(other.capacity), allocator(other.allocator) {
                data = std::move(other.data);
            }

            CustomVector& operator=(const CustomVector& other) {
                size = other.size;
                capacity = other.capacity;
                allocator = other.allocator;

                data = std::unique_ptr<T, PolymorphicDeleter>(allocator.allocate(capacity), PolymorphicDeleter{});
                auto i = 0;
                for (auto & item: other){
                    data.get()[i] = item;
                    i++;
                }

                return *this;
            }

            CustomVector& operator=(CustomVector&& other)  noexcept {
                size = other.size;
                capacity = other.capacity;
                allocator = other.allocator;

                data = std::move(other.data);
                return *this;
            }

            T operator[](size_t idx){
                if (idx >= size) throw std::out_of_range("The index is beyond the bounds of the container");
                return data.get()[idx];
            }

            CustomIterator<T, CustomVector<T, alloc_t>> begin() {
                return new CustomIterator<T, CustomVector<T, alloc_t>>(this, 0, size);
            }

            CustomIterator<T, CustomVector<T, alloc_t>> end() {
                return new CustomIterator<T, CustomVector<T, alloc_t>>(this, size, size);
            }

            size_t get_size(){
                return size;
            }

            size_t get_capacity(){
                return capacity;
            }

            void push_back(T item){
                size++;
                if (size > capacity){
                    T* newData = allocator.allocate(calculate_capacity(size));
                    memcpy(newData, data.get(), (size - 1) * sizeof (T));
                    data = std::unique_ptr<T, PolymorphicDeleter>(newData, PolymorphicDeleter{});
                }
                data.get()[size - 1] = item;
            }

            void pop_back(){
                size--;
            }

            void remove_at(size_t idx) {
                if (idx >= size) throw std::out_of_range("The index is beyond the bounds of the container");
                for (auto i = idx; i < size - 1; ++i){
                    data.get()[i] = data.get()[i + 1];
                }
                size--;
            }

            ~CustomVector() {
                if constexpr (std::is_destructible_v<T>){
                    for (size_t i = 0; i < size; ++i){
                        std::allocator_traits<alloc_t>::destroy(allocator, data.get() + i);
                    }
                }

                allocator.deallocate(data.get(), capacity);
            }
    };

}
