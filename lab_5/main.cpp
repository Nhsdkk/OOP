#include "src/CustomMemoryResource.h"
int main() {
    CustomContainers::CustomMemoryResource customResource;
    std::pmr::polymorphic_allocator<int> allocator(&customResource);

}