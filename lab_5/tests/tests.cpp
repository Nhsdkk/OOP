#include <gtest/gtest.h>
#include "../src/CustomVector.h"
#include "../src/CustomMemoryResource.h"

template<class T>
bool cmp(CustomContainers::CustomVector<T, std::pmr::polymorphic_allocator<T>> vec1, std::vector<T> vec2){
    if (vec1.get_size() != vec2.size()) return false;
    for (auto i = 0; i < vec1.get_size(); ++i){
        if (vec1[i] != vec2[i]) return false;
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

TEST(VectorTests, ShouldPopBackItemCorrectly){
    CustomContainers::CustomMemoryResource customResource;
    std::pmr::polymorphic_allocator<int> allocator(&customResource);

    auto vec1 = CustomContainers::CustomVector<int, std::pmr::polymorphic_allocator<std::pair<int, int>>>({1,2,3}, allocator);
    vec1.pop_back();
    auto vec2 = std::vector<int>({1,2});

    ASSERT_TRUE(cmp(vec1, vec2));
}

TEST(AllocatorTests, ShouldCreateUsedBlocksCorrectly){
    CustomContainers::CustomMemoryResource customResource;
    std::pmr::polymorphic_allocator<int> allocator(&customResource);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}