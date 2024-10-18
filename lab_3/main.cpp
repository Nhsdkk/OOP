#include "src/Figure.h"
#include "src/Square.h"
#include "src/FigureArray.h"
#include "src/Triangle.h"

int main() {
    auto center = Shape::Point{1, 1};
    Shape::Triangle square1 {center, center, center};
    Shape::Triangle square2 {center, center, center};
}