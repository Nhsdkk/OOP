#pragma once

#include <initializer_list>
#include <stdexcept>
#include <string>

namespace hex {

    class BinaryException final: public std::exception {
    public:
        explicit BinaryException(unsigned char ch);
        [[nodiscard]] const char * what() const noexcept override;
    private:
        std::string message;
    };

    class Hex {
    public:
        Hex();
        explicit Hex(const std::string& string);
        Hex(size_t size, unsigned char ch);
        Hex(const std::initializer_list<unsigned char> &t);
        Hex(const Hex& hex);
        Hex(Hex&& hex) noexcept ;

        unsigned char * get_value() const;

        Hex operator+(const Hex& other) const;
        Hex operator-(const Hex& other) const;
        bool operator<(const Hex& other) const;
        bool operator>(const Hex& other) const;
        bool operator==(const Hex& other) const;
        Hex operator+=(const Hex& other);
        Hex operator-=(const Hex& other);

        virtual ~Hex() noexcept;

    private:
        unsigned char* value;
        size_t size;

        explicit Hex(size_t size);

        void set_char(unsigned char ch, size_t idx) const;
        static std::string lpad(const unsigned char * const val, size_t size, size_t preferredSize);
        static std::string trim(std::string val);
        static short get_int(const unsigned char ch);
    };

}
