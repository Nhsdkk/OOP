#include <gtest/gtest.h>
#include "../src/CustomVector.h"
#include "../src/CustomMemoryResource.h"

template<class T>
bool cmp(CustomContainers::CustomVector<T, std::pmr::polymorphic_allocator<T>> vec1, std::vector<T> vec2){
    if (vec1.get_size() != vec2.size()) return false;
    auto i = 0;
    for (auto item1 : vec1){
        if (item1 != vec2[i]) return false;
        ++i;
    }
    return true;
}

TEST(VectorTests, ShouldCreateVectorCorrectly){
    CustomContainers::CustomMemoryResource<16> customResource;
    std::pmr::polymorphic_allocator<int> allocator(&customResource);

    auto vec1 = CustomContainers::CustomVector<int, std::pmr::polymorphic_allocator<int>>({1,2,3}, allocator);
    auto vec2 = std::vector<int>({1,2,3});

    ASSERT_TRUE(cmp(vec1, vec2));
}

TEST(VectorTests, ShouldCreateVectorCorrectlyWithPushBack){
    CustomContainers::CustomMemoryResource customResource;
    std::pmr::polymorphic_allocator<int> allocator(&customResource);

    auto vec1 = CustomContainers::CustomVector<int, std::pmr::polymorphic_allocator<int>>(allocator);

    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    auto vec2 = std::vector<int>({1,2,3});

    ASSERT_TRUE(cmp(vec1, vec2));
}

TEST(VectorTests, ShouldRemoveItemCorrectly){
    CustomContainers::CustomMemoryResource customResource;
    std::pmr::polymorphic_allocator<int> allocator(&customResource);

    auto vec1 = CustomContainers::CustomVector<int, std::pmr::polymorphic_allocator<int>>({1,2,3}, allocator);
    vec1.remove_at(1);
    auto vec2 = std::vector<int>({1,3});

    ASSERT_TRUE(cmp(vec1, vec2));
}

TEST(VectorTests, ShouldCreateCorrectlyWithComplicatedType){
    CustomContainers::CustomMemoryResource customResource;
    std::pmr::polymorphic_allocator<std::pair<int, int>> allocator(&customResource);

    auto vec1 = CustomContainers::CustomVector<std::pair<int, int>, std::pmr::polymorphic_allocator<std::pair<int, int>>>(allocator);

    vec1.push_back(std::pair(1,2));
    vec1.push_back(std::pair(3,4));
    vec1.push_back(std::pair(5,6));

    auto vec2 = std::vector<std::pair<int, int>>({
        std::pair(1,2),
        std::pair(3,4),
        std::pair(5,6)
    });

    ASSERT_TRUE(cmp(vec1, vec2));
}

TEST(AllocatorTests, ShouldCreateUsedBlocksCorrectly){
    CustomContainers::CustomMemoryResource<16> customResource;
    std::pmr::polymorphic_allocator<int> allocator(&customResource);

    auto vec1 = CustomContainers::CustomVector<int, std::pmr::polymorphic_allocator<int>>({1,2,3}, allocator);

    auto blocks = customResource.get_used_blocks();

    ASSERT_EQ(blocks.size(), 1);
    ASSERT_EQ(*blocks.begin(), CustomContainers::Block(0, 15, 0));

    vec1.push_back(4);
    vec1.push_back(5);

    blocks = customResource.get_used_blocks();

    ASSERT_EQ(blocks.size(), 1);
    ASSERT_EQ(*blocks.begin(), CustomContainers::Block(0, 31, 3));

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}