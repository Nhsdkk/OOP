#include "hex.h"

#include <stdexcept>
#include <algorithm>
#include <format>
#include <cmath>
#include <iostream>

namespace hex {
    const unsigned short base = 16;
    const unsigned char chars[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };

    Hex::Hex(): value(nullptr), size(0) {}

    Hex::Hex(const size_t size) {
        this->size = size;
        this->value = new unsigned char[size + 1];
        this->value[this->size] = '\0';
    }

    Hex::Hex(const std::string& string) : Hex(string.length()) {
        for (size_t i = 0; i < this->size; ++i) {
            this->set_char(string[i], i);
        }
    }

//    Hex::Hex(const size_t size, const unsigned char ch) : Hex(size) {
//      for (size_t i = 0; i < this->size; ++i) {
//          this->set_char(ch, i);
//      }
//    }

    Hex::Hex(const std::initializer_list<unsigned char> &t) : Hex(t.size()) {
        size_t i {0};

        for (const auto& c : t) {
            this->set_char(c, i++);
        }
    }

    Hex::Hex(const Hex &hex) : Hex(hex.size) {
        for (size_t i = 0; i < hex.size; ++i) {
            this->set_char(hex.value[i], i);
        }
    }

    Hex::Hex(Hex &&hex) noexcept {
        swap(*this, hex);
    }

    unsigned char * Hex::get_value() const {
        if (this->size == 0) return reinterpret_cast<unsigned char *>('0');
        return this->value;
    }

    Hex Hex::operator+(const Hex &other) const {
        unsigned short buff {0};

        if (this->size > other.size) return other + *this;

        if (this->size == 0) return other;

        const size_t new_size = other.size;
        auto result = lpad(this->value, this->size, new_size);

        for (int i = static_cast<int>(new_size) - 1; i >= 0; --i) {
            short rval = get_int(result[i]), lval = get_int(other.value[i]);
            short sum = lval + rval + buff;
            buff = sum / base;
            result[i] = chars[sum % base];
        }

        if (buff != 0) result = std::format("{}{}", buff, result);

        return Hex(result);
    }

    Hex Hex::operator-(const Hex &other) const {
        unsigned short buff {0};

        if (other > *this) throw std::invalid_argument("result of subtraction is negative");

        const size_t new_size = this->size;
        auto result = lpad(other.value, other.size, new_size);

        for (int i = static_cast<int>(new_size) - 1; i >= 0; --i) {
            short rval = get_int(this->value[i]), lval = get_int(result[i]);
            short diff = rval - lval - buff;
            buff = std::abs(static_cast<int>(std::floor(diff / static_cast<double>(base))));
            result[i] = chars[std::abs(diff % base)];
        }

        return Hex(trim(result));
    }

    bool Hex::operator<(const Hex &other) const {
        if (this->size != other.size) return this->size < other.size;
        if (this->size == 0) return false;

        for (size_t i = 0; i <= this->size; ++i) {
            short rval = get_int(this->value[i]), lval = get_int(other.value[i]);

            if (lval == rval) continue;

            return rval < lval;
        }

        return false;
    }

    bool Hex::operator>(const Hex &other) const {
        if (this->size != other.size) return this->size > other.size;
        if (this->size == 0) return false;

        for (size_t i = 0; i <= this->size; ++i) {
            short rval = get_int(this->value[i]), lval = get_int(other.value[i]);

            if (lval == rval) continue;

            return rval > lval;
        }

        return false;
    }

    bool Hex::operator==(const Hex &other) const {
        if (this->size != other.size) return false;
        if (this->size == 0) return true;
        for (size_t i = 0; i < this->size; ++i) {
            if (this->value[i] != other.value[i]) return false;
        }
        return true;
    }

    Hex::~Hex() noexcept {
        if (this->size == 0) return;
        this->size = 0;
        this->value = nullptr;
    }

    void Hex::set_char(const unsigned char ch, const size_t idx) const {
        if (std::find(std::begin(chars), std::end(chars), ch) == std::end(chars)) throw BinaryException(ch);
        if (idx >= this->size) throw std::out_of_range(std::format("received value outside of number bounds {}" ,idx));
        this->value[idx] = ch;
    }

    std::string Hex::lpad(const unsigned char *const val, size_t valSize, size_t preferredSize) {
        auto diff = preferredSize - valSize;
        std::string result(preferredSize, ' ');

        for (size_t i = 0; i < preferredSize; ++i){
            if (i < diff){
                result[i] = '0';
                continue;
            }

            result[i] = val[i - diff];
        }

        return result;
    }

    std::string Hex::trim(std::string val) {
        auto i{0};
        while (val[i] == '0') { ++i; }

        std::string result(val.length() - i, ' ');

        for (auto k = 0; k < val.length(); ++k){
            result[k] = val[k + i];
        }

        return result;
    }

    short Hex::get_int(const unsigned char ch) {
        short number = ch - '0';
        short al = ch - 'A';
        if (al >= 0) return al + 10;
        else return number;
    }

    Hex Hex::operator+=(const Hex &other) {
        auto result = *this + other;
        this->size = result.size;
        this->value = result.value;
        return *this;
    }

    Hex Hex::operator-=(const Hex &other) {
        auto result = *this - other;
        this->size = result.size;
        this->value = result.value;
        return *this;
    }

    Hex &Hex::operator=(const Hex &other) {
        auto otherCopy = Hex(other);
        swap(*this, otherCopy);
        return *this;
    }

    Hex &Hex::operator=(Hex &&other) noexcept {
        swap(*this, other);
        return *this;
    }

    void Hex::swap(Hex &h1, Hex &h2) {
        h1.value = h2.value;
        h1.size = h2.size;

        h2.~Hex();
    }

    bool Hex::operator!=(const Hex &other) const {
        return !(*this == other);
    }

    BinaryException::BinaryException(const unsigned char ch) : message(std::format("received non binary value {}", ch)) {}

    const char *BinaryException::what() const noexcept {
        return message.data();
    }

}
