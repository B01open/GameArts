 
/** @file ParallelConfigPrecompiled.h
 *  @author jimmyshi
 *  @date 20190315
 */
#pragma once
#include "Common.h"
#include <libblockverifier/ExecutiveContext.h>
#include <libethcore/ABI.h>

#include <libdevcore/Common.h>
#include <libethcore/Common.h>

namespace dev
{
namespace storage
{
class Table;
}

namespace precompiled
{
struct ParallelConfig
{
    typedef std::shared_ptr<ParallelConfig> Ptr;
    std::string functionName;
    u256 criticalSize;
};

const std::string PARA_CONFIG_TABLE_PREFIX = "_contract_parafunc_";
const std::string PARA_CONFIG_TABLE_PREFIX_SHORT = "cp_";

class ParallelConfigPrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<ParallelConfigPrecompiled> Ptr;
    ParallelConfigPrecompiled();
    virtual ~ParallelConfigPrecompiled(){};

    std::string toString() override;

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& _sender = Address()) override;

    dev::storage::Table::Ptr openTable(dev::blockverifier::ExecutiveContext::Ptr context,
        Address const& contractAddress, Address const& origin, bool needCreate = true);

private:
    void registerParallelFunction(dev::blockverifier::ExecutiveContext::Ptr context,
        bytesConstRef data, Address const& origin, bytes& out);
    void unregisterParallelFunction(dev::blockverifier::ExecutiveContext::Ptr context,
        bytesConstRef data, Address const& origin, bytes& out);

public:
    /// get paralllel config, return nullptr if not found
    ParallelConfig::Ptr getParallelConfig(dev::blockverifier::ExecutiveContext::Ptr context,
        Address const& contractAddress, uint32_t selector, Address const& origin);
};

}  // namespace precompiled

}  // namespace dev