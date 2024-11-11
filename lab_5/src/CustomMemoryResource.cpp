#include <memory>
#include "CustomMemoryResource.h"
#include <algorithm>

namespace CustomContainers {
    const size_t BASE_BLOCK_SIZE = 256;

    void *CustomMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
        size_t prev_end = 0;
        size_t block_idx = 0;
        for (auto& block : used_blocks){
            if (block.blockId != block_idx) {
                block_idx = block.blockId;
                prev_end = 0;
            }
            if (block.start - prev_end >= bytes) break;
            prev_end = block.end + 1;
        }

        size_t start = prev_end;
        size_t end = prev_end + bytes - 1;
        size_t block_size = BASE_BLOCK_SIZE + BASE_BLOCK_SIZE * block_idx;

        if ((end > block_size && block_idx == blocksCount - 1) || blocksCount == 0) {
            blocksCount++;
            buffer.emplace_back((char *)std::malloc(block_size + BASE_BLOCK_SIZE));
        }

        if (end > block_size){
            block_idx++;
            start = 0;
            end = start + bytes - 1;
        }

        auto block = Block{start, end, block_idx};

        used_blocks.push_back(block);
        used_blocks.sort([](auto& rval, auto& lval) { return rval.start <= lval.start; });
        return buffer[block_idx].get() + block.start;
    }

    void CustomMemoryResource::do_deallocate(void *p, std::size_t bytes, std::size_t alignment) {
        for (auto& item : used_blocks){
            if (p == buffer[item.blockId].get() + item.start){
                used_blocks.remove(item);
                return;
            }
        }
        throw std::logic_error("Can't free unused memory");
    }

    bool CustomMemoryResource::do_is_equal(const std::pmr::memory_resource &other) const noexcept {
        return this == &other;
    }
}