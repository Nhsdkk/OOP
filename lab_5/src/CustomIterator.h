#pragma once
#include <cstdio>
#include <stdexcept>
namespace CustomContainers {

    template<class ItemT, class ArrayT>
    class CustomIterator {
        ArrayT* array;
        size_t idx;
        size_t size;

        public:
            CustomIterator(ArrayT* array, size_t idx, size_t size) : array(array), idx(idx), size(size) {}

            ItemT operator*(){
                if (idx >= size) throw std::out_of_range("Iterator is beyond the bounds of the container");
                return (*array)[idx];
            }

            ItemT operator->(){
                if (idx >= size) throw std::out_of_range("Iterator is beyond the bounds of the container");
                return (*array)[idx];
            }

            CustomIterator<ItemT, ArrayT> operator++(){
                ++idx;
                return *this;
            }

            bool operator!=(const CustomIterator<ItemT, ArrayT>& other) const {
                return this->idx != other.idx || this->array != other.array;
            }
    };

}
