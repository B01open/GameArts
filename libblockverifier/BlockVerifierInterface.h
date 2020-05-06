
#pragma once

#include "Common.h"
#include "ExecutiveContext.h"

#include <libdevcore/FixedHash.h>
#include <libdevcrypto/Common.h>
#include <libethcore/Block.h>
#include <libethcore/Transaction.h>
#include <libethcore/TransactionReceipt.h>
#include <libevm/ExtVMFace.h>
#include <libexecutive/ExecutionResult.h>
#include <libmptstate/State.h>
#include <memory>

namespace dev
{
namespace eth
{
class PrecompiledContract;

}  // namespace eth
namespace blockverifier
{
class BlockVerifierInterface
{
public:
    using Ptr = std::shared_ptr<BlockVerifierInterface>;
    BlockVerifierInterface() = default;

    virtual ~BlockVerifierInterface(){};

    virtual ExecutiveContext::Ptr executeBlock(
        dev::eth::Block& block, BlockInfo const& parentBlockInfo) = 0;

    virtual dev::eth::TransactionReceipt::Ptr executeTransaction(
        const dev::eth::BlockHeader& blockHeader, dev::eth::Transaction::Ptr _t) = 0;
};
}  // namespace blockverifier
}  // namespace dev
