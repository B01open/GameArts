
#pragma once

#include "Common.h"
#include "libprecompiled/Precompiled.h"
#include <libdevcore/Common.h>
#include <libdevcore/FixedHash.h>
#include <libdevcrypto/Common.h>
#include <libethcore/Block.h>
#include <libethcore/ChainOperationParams.h>
#include <libethcore/PrecompiledContract.h>
#include <libethcore/Protocol.h>
#include <libethcore/Transaction.h>
#include <libexecutive/StateFace.h>
#include <libstorage/Table.h>
#include <tbb/concurrent_unordered_map.h>
#include <atomic>
#include <functional>
#include <memory>

namespace dev
{
namespace storage
{
class Table;
}  // namespace storage

namespace executive
{
class StateFace;
}
namespace precompiled
{
class Precompiled;
}
namespace blockverifier
{
class ExecutiveContext : public std::enable_shared_from_this<ExecutiveContext>
{
public:
    typedef std::shared_ptr<ExecutiveContext> Ptr;

    ExecutiveContext() : m_addressCount(0x10000) {}

    virtual ~ExecutiveContext()
    {
        if (m_memoryTableFactory)
        {
            m_memoryTableFactory->commit();
        }
    };

    virtual bytes call(
        Address const& address, bytesConstRef param, Address const& origin, Address const& sender);

    virtual Address registerPrecompiled(std::shared_ptr<precompiled::Precompiled> p);

    virtual bool isPrecompiled(Address address) const;

    std::shared_ptr<precompiled::Precompiled> getPrecompiled(Address address) const;

    void setAddress2Precompiled(
        Address address, std::shared_ptr<precompiled::Precompiled> precompiled)
    {
        m_address2Precompiled.insert(std::make_pair(address, precompiled));
    }

    BlockInfo blockInfo() { return m_blockInfo; }
    void setBlockInfo(BlockInfo blockInfo) { m_blockInfo = blockInfo; }

    std::shared_ptr<dev::executive::StateFace> getState();
    void setState(std::shared_ptr<dev::executive::StateFace> state);

    virtual bool isOrginPrecompiled(Address const& _a) const;

    virtual std::pair<bool, bytes> executeOriginPrecompiled(
        Address const& _a, bytesConstRef _in) const;

    void setPrecompiledContract(
        std::unordered_map<Address, dev::eth::PrecompiledContract> const& precompiledContract);

    void dbCommit(dev::eth::Block& block);

    void setMemoryTableFactory(std::shared_ptr<dev::storage::TableFactory> memoryTableFactory)
    {
        m_memoryTableFactory = memoryTableFactory;
    }

    std::shared_ptr<dev::storage::TableFactory> getMemoryTableFactory()
    {
        return m_memoryTableFactory;
    }

    uint64_t txGasLimit() const { return m_txGasLimit; }
    void setTxGasLimit(uint64_t _txGasLimit) { m_txGasLimit = _txGasLimit; }

    // Get transaction criticals, return nullptr if critical to all
    std::shared_ptr<std::vector<std::string>> getTxCriticals(const dev::eth::Transaction& _tx);

private:
    tbb::concurrent_unordered_map<Address, std::shared_ptr<precompiled::Precompiled>,
        std::hash<Address>>
        m_address2Precompiled;
    std::atomic<int> m_addressCount;
    BlockInfo m_blockInfo;
    std::shared_ptr<dev::executive::StateFace> m_stateFace;
    std::unordered_map<Address, dev::eth::PrecompiledContract> m_precompiledContract;
    std::shared_ptr<dev::storage::TableFactory> m_memoryTableFactory;
    uint64_t m_txGasLimit = 300000000;
};

}  // namespace blockverifier

}  // namespace dev
