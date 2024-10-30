#include <memory>

#include "src/Figure.h"
#include "src/Triangle.h"
#include "src/Square.h"
#include "src/Octagon.h"

int main() {
    auto center = Shape::Point<double >{1, 1};
    auto square1 = std::make_unique<Shape::Figure<double>>(Shape::Figure{center, center, center});
    auto s1 = std::move(square1);
}