#pragma once
#include <memory_resource>
#include <list>
#include <memory>
namespace CustomContainers {

    class Block {
        public:
            size_t start, end, blockId;
            Block() = default;
            Block(size_t start, size_t end, size_t blockId) : start(start), end(end), blockId(blockId) {}

            Block(const Block& block) = default;
            Block(Block&& block) noexcept = default;
            Block& operator=(const Block& block) = default;
            Block& operator=(Block&& block) noexcept {
                start = block.start;
                end = block.end;
                blockId = block.blockId;
                return *this;
            };

            ~Block() = default;

            bool operator==(const Block& other) const {
                return start == other.start && end == other.end && blockId == other.blockId;
            }
    };

    class CustomMemoryResource : public std::pmr::memory_resource {
        std::vector<std::unique_ptr<char[]>> buffer;
        std::list<Block> used_blocks;
        size_t blocksCount;

        public:
            CustomMemoryResource(): buffer(), used_blocks({}), blocksCount(0) {}
            void * do_allocate(std::size_t bytes, std::size_t alignment) override;
            void do_deallocate(void *p, std::size_t bytes, std::size_t alignment) override;
            bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override;
    };

}
