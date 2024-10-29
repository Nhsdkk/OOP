#include <memory>

#include "src/Figure.h"
#include "src/Triangle.h"
#include "src/Square.h"
#include "src/Octagon.h"

int main() {
    auto tr = Shape::Octagon<double>({Shape::Point{1.0, 2.0}});
}