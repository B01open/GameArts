
#pragma once

#include "libprecompiled/Precompiled.h"

namespace dev
{
namespace storage
{
class MemoryTableFactory;
}

namespace precompiled
{
#if 0
contract KVTableFactory {
    function openTable(string) public constant returns (KVTable);
    function createTable(string, string, string) public returns (bool,int);
}
#endif

class KVTableFactoryPrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<KVTableFactoryPrecompiled> Ptr;
    KVTableFactoryPrecompiled();
    virtual ~KVTableFactoryPrecompiled(){};

    std::string toString() override;

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& _sender = Address()) override;

    void setMemoryTableFactory(std::shared_ptr<dev::storage::TableFactory> memoryTableFactory)
    {
        m_memoryTableFactory = memoryTableFactory;
    }

    std::shared_ptr<dev::storage::TableFactory> getMemoryTableFactory()
    {
        return m_memoryTableFactory;
    }

    h256 hash();

private:
    std::shared_ptr<dev::storage::TableFactory> m_memoryTableFactory;
};

}  // namespace precompiled

}  // namespace dev
