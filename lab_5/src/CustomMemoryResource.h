#pragma once
#include <memory_resource>
#include <list>
#include <memory>
#include <cmath>

namespace CustomContainers {

    class Block {
        size_t start, end, blockId;

        public:
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

            size_t get_start() { return start; }
            size_t get_end() { return end; }
            size_t get_block_id() { return blockId; }


            ~Block() = default;

            bool operator==(const Block& other) const {
                return start == other.start && end == other.end && blockId == other.blockId;
            }
    };

    template<size_t baseBlockSize = 256, double growthRate = 1.4>
    class CustomMemoryResource : public std::pmr::memory_resource {
        std::vector<std::unique_ptr<char[]>> buffer;
        std::list<Block> used_blocks;
        size_t blocksCount;

        public:
            CustomMemoryResource(): buffer(), used_blocks({}), blocksCount(0) {}

            void * do_allocate(std::size_t bytes, std::size_t alignment) override {
                size_t prev_end = 0;
                long long block_idx = -1;
                for (auto& block : used_blocks){
                    if (block.get_block_id() != block_idx) {
                        block_idx = block.get_block_id();
                        prev_end = 0;
                    }
                    if (block.get_start() - prev_end >= bytes) break;
                    prev_end = block.get_end() + 1;
                }

                size_t start = prev_end;
                size_t end = prev_end + bytes - 1;
                size_t block_size = block_idx < 0 ? 0 : baseBlockSize * std::pow(growthRate, block_idx);

                while (end > block_size){
                    block_idx++;
                    start = 0;
                    end = start + bytes - 1;
                    if (block_size == 0) block_size += baseBlockSize;
                    else block_size *= growthRate;
                }

                size_t end_block_size = blocksCount < 0 ? 0 : baseBlockSize * std::pow(growthRate, blocksCount - 1);

                for (int i = blocksCount; i < block_idx + 1; ++i){
                    blocksCount++;
                    if (end_block_size == 0) end_block_size += baseBlockSize;
                    else end_block_size *= growthRate;
                    buffer.emplace_back((char *)std::malloc(end_block_size));
                }

                auto block = Block{start, end, static_cast<size_t>(block_idx)};

                used_blocks.push_back(block);
                used_blocks.sort([](auto& rval, auto& lval) {
                    if (rval.get_start() != lval.get_start()) return rval.get_start() < lval.get_start();
                    return rval.get_block_id() <= lval.get_block_id();
                });
                return buffer[block_idx].get() + block.get_start();
            }

            void do_deallocate(void *p, std::size_t bytes, std::size_t alignment) override {
                for (auto& item : used_blocks){
                    if (p == buffer[item.get_block_id()].get() + item.get_start()){
                        used_blocks.remove(item);
                        return;
                    }
                }
                throw std::logic_error("Can't free unused memory");
            }

            bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override {
                return this == &other;
            }

            std::list<Block> get_used_blocks() {
                return used_blocks;
            }
    };

}
