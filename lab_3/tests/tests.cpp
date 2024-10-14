#include <gtest/gtest.h>
#include <cmath>
#include "../src/Square.h"
#include "../src/Triangle.h"
#include "../src/FigureArray.h"
#include "../src/Octagon.h"

TEST(SquareTests ,Should_CalculateAreaAndCenterCorrectly_When_CreatingWithPoints){
    auto square = Shape::Square({Shape::Point{0,0}, Shape::Point{0,2}, Shape::Point{2,2}, Shape::Point{2,0}});
    auto center = Shape::Point{1, 1};
    ASSERT_EQ(square.get_center(), center);
    ASSERT_EQ(double(square), 4);
}

TEST(SquareTests ,Should_CalculateAreaAndCenterCorrectly_When_CreatingWithCenterAndL){
    auto center = Shape::Point{1, 1};
    auto square = Shape::Square(2, center);
    ASSERT_EQ(square.get_center(), center);
    ASSERT_EQ(double(square), 4);
}

TEST(SquareTests ,Should_CalculateAreaAndCenterCorrectly_When_CreatingWithCornerPoints){
    auto p1 = Shape::Point{0,0}, p2 = Shape::Point{2, 2};
    auto square = Shape::Square(p1, p2);

    auto center = Shape::Point{1, 1};

    ASSERT_EQ(square.get_center(), center);
    ASSERT_EQ(double(square), 4);
}

TEST(TriangleTests ,Should_CalculateAreaAndCenterCorrectly_When_CreatingWithPoints){
    auto triangle = Shape::Triangle({Shape::Point{0,0}, Shape::Point{0,2}, Shape::Point{1,std::sqrt(3)}});
    auto center = Shape::Point{1.0 / 3, (2 + std::sqrt(3)) / 3};
    ASSERT_EQ(triangle.get_center(), center);
    ASSERT_EQ(double(triangle), pow(2, 2) * std::sqrt(3) / 4);
}

TEST(TriangleTests ,Should_CalculateAreaAndCenterCorrectly_When_CreatingWithCenterAndL){
    auto center = Shape::Point{1, 1};
    auto triangle = Shape::Triangle(2, center);
    ASSERT_EQ(triangle.get_center(), center);
    ASSERT_EQ(double(triangle), pow(2, 2) * std::sqrt(3) / 4);
}

TEST(ArrayTests, Should_CalculateArrayAreaCorrectly_When_CreatingWithInitializerArray){
    auto triangle = Shape::Triangle({Shape::Point{0,0}, Shape::Point{0,2}, Shape::Point{1,std::sqrt(3)}});
    auto p1 = Shape::Point{0,0}, p2 = Shape::Point{2, 2};
    auto square = Shape::Square(p1, p2);
    auto square1 = Shape::Square(p1, p2);

    auto list = Shape::FigureArray({&triangle, &square, &square1});
    ASSERT_EQ(list.get_total_area(), 8 + pow(2, 2) * std::sqrt(3) / 4);
}

TEST(ArrayTests, Should_EveryElementBeAccessible_When_CreatingWithInitializerArray){
    auto triangle = Shape::Triangle({Shape::Point{0,0}, Shape::Point{0,2}, Shape::Point{1,std::sqrt(3)}});
    auto p1 = Shape::Point{0,0}, p2 = Shape::Point{2, 2};
    auto square = Shape::Square(p1, p2);
    auto square1 = Shape::Square(p1, p2);

    auto list = Shape::FigureArray({&triangle, &square, &square1});

    ASSERT_EQ(double(*list[0]), pow(2, 2) * std::sqrt(3) / 4);
    ASSERT_EQ(double(*list[1]), 4);
    ASSERT_EQ(double(*list[2]), 4);

    auto triangleCenter = Shape::Point{1.0 / 3, (2 + std::sqrt(3)) / 3};
    auto squareCenter = Shape::Point{1, 1};

    ASSERT_EQ(list[0]->get_center(), triangleCenter);
    ASSERT_EQ(list[1]->get_center(), squareCenter);
    ASSERT_EQ(list[2]->get_center(), squareCenter);
}

TEST(ArrayTests, Should_CalculateArrayAreaCorrectly_When_CreatingWithPushBack){
    auto triangle = Shape::Triangle({Shape::Point{0,0}, Shape::Point{0,2}, Shape::Point{1,std::sqrt(3)}});
    auto p1 = Shape::Point{0,0}, p2 = Shape::Point{2, 2};
    auto square = Shape::Square(p1, p2);
    auto square1 = Shape::Square(p1, p2);

    Shape::FigureArray list;
    list.push_back(&square1);
    list.push_back(&square);
    list.push_back(&triangle);
    ASSERT_EQ(list.get_total_area(), 8 + pow(2, 2) * std::sqrt(3) / 4);
}

TEST(ArrayTests, Should_EveryElementBeAccessible_When_CreatingWithPushBack){
    auto triangle = Shape::Triangle({Shape::Point{0,0}, Shape::Point{0,2}, Shape::Point{1,std::sqrt(3)}});
    auto p1 = Shape::Point{0,0}, p2 = Shape::Point{2, 2};
    auto square = Shape::Square(p1, p2);
    auto square1 = Shape::Square(p1, p2);

    Shape::FigureArray list;
    list.push_back(&triangle);
    list.push_back(&square);
    list.push_back(&square1);

    ASSERT_EQ(double(*list[0]), pow(2, 2) * std::sqrt(3) / 4);
    ASSERT_EQ(double(*list[1]), 4);
    ASSERT_EQ(double(*list[2]), 4);

    auto triangleCenter = Shape::Point{1.0 / 3, (2 + std::sqrt(3)) / 3};
    auto squareCenter = Shape::Point{1, 1};

    ASSERT_EQ(list[0]->get_center(), triangleCenter);
    ASSERT_EQ(list[1]->get_center(), squareCenter);
    ASSERT_EQ(list[2]->get_center(), squareCenter);
}

TEST(ArrayTests, Should_CalculateArrayAreaCorrectly_When_RemovingItemWithRemoveAt){
    auto triangle = Shape::Triangle({Shape::Point{0,0}, Shape::Point{0,2}, Shape::Point{1,std::sqrt(3)}});
    auto p1 = Shape::Point{0,0}, p2 = Shape::Point{2, 2};
    auto square = Shape::Square(p1, p2);
    auto square1 = Shape::Square(p1, p2);

    Shape::FigureArray list;
    list.push_back(&square1);
    list.push_back(&square);
    list.push_back(&triangle);
    ASSERT_EQ(list.get_total_area(), 8 + pow(2, 2) * std::sqrt(3) / 4);

    list.remove_at(1);
    ASSERT_EQ(list.get_total_area(), 4 + pow(2, 2) * std::sqrt(3) / 4);
}

TEST(ArrayTests, Should_ThrowException_When_AccessingItemWithIndexOutOfRange){
    auto triangle = Shape::Triangle({Shape::Point{0,0}, Shape::Point{0,2}, Shape::Point{1,std::sqrt(3)}});
    auto p1 = Shape::Point{0,0}, p2 = Shape::Point{2, 2};
    auto square = Shape::Square(p1, p2);
    auto square1 = Shape::Square(p1, p2);

    Shape::FigureArray list;
    list.push_back(&square1);
    list.push_back(&square);
    list.push_back(&triangle);

    EXPECT_THROW([&list]{
        list[4];
    }(), std::out_of_range);

    EXPECT_THROW([&list]{
      list.remove_at(4);
    }(), std::out_of_range);
}

TEST(OctagonTests ,Should_CalculateAreaAndCenterCorrectly_When_CreatingWithPoints){
    auto octagon = Shape::Octagon(
{
           Shape::Point{0, 0},
           Shape::Point{-1, 0},
           Shape::Point{-1 - 1 / std::sqrt(2), 1 / std::sqrt(2)},
           Shape::Point{-1 - 1 / std::sqrt(2), 1 + 1 / std::sqrt(2)},
           Shape::Point{-1, 1 + 2 * 1 / std::sqrt(2)},
           Shape::Point{0, 1 + 2 * 1 / std::sqrt(2)},
           Shape::Point{1 / std::sqrt(2), 1 + 1 / std::sqrt(2)},
           Shape::Point{1 / std::sqrt(2), 1 / std::sqrt(2)}
       }
    );
    auto center = Shape::Point{-0.5, (1 + 2 / std::sqrt(2)) / 2};
    ASSERT_EQ(octagon.get_center(), center);
    ASSERT_EQ(double(octagon), 2 * pow(1, 2) * (std::sqrt(2) + 1));
}

TEST(OctagonTests ,Should_CalculateAreaAndCenterCorrectly_When_CreatingWithCenterAndL){
    auto center = Shape::Point{1.0, 1.0};
    auto octagon = Shape::Octagon(2, center);
    ASSERT_EQ(octagon.get_center(), center);
    ASSERT_EQ(double(octagon), 2 * pow(2, 2) * (std::sqrt(2) + 1));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}