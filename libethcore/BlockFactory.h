

#pragma once
#include "Block.h"
#include "PartiallyBlock.h"

namespace dev
{
namespace eth
{
class BlockFactory
{
public:
    using Ptr = std::shared_ptr<BlockFactory>;
    BlockFactory() = default;
    virtual ~BlockFactory() {}
    virtual Block::Ptr createBlock() { return std::make_shared<Block>(); }
};

class PartiallyBlockFactory : public BlockFactory
{
public:
    PartiallyBlockFactory() = default;
    ~PartiallyBlockFactory() override {}
    Block::Ptr createBlock() override { return std::make_shared<PartiallyBlock>(); }
};

}  // namespace eth
}  // namespace dev