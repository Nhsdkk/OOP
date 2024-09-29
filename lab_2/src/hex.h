#pragma once

#include <initializer_list>
#include <stdexcept>
#include <string>

namespace exception {
    class BinaryException final: public std::exception {
     public:
      explicit BinaryException(unsigned char ch);
      [[nodiscard]] const char * what() const noexcept override;
     private:
      std::string message;
    };
}

namespace hex {
    class Hex {
    public:
        Hex();
        explicit Hex(const std::string& string);
//        Hex(size_t size, unsigned char ch);
        Hex(const std::initializer_list<unsigned char> &t);

        Hex(const Hex& hex);
        Hex& operator=(const Hex& other);

        Hex(Hex&& hex) noexcept ;
        Hex& operator=(Hex&& other)  noexcept ;

        unsigned char * get_value() const;

        Hex operator+(const Hex& other) const;
        Hex operator-(const Hex& other) const;
        bool operator<(const Hex& other) const;
        bool operator>(const Hex& other) const;
        bool operator==(const Hex& other) const;
        bool operator!=(const Hex& other) const;
        Hex& operator+=(const Hex& other);
        Hex& operator-=(const Hex& other);

        ~Hex() noexcept;

    private:
        unsigned char* value;
        size_t size;

        explicit Hex(size_t size);

        static void swap(Hex& h1, Hex& h2) ;
    };

}
