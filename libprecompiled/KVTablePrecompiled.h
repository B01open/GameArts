

#pragma once

#include "libprecompiled/Precompiled.h"

namespace dev
{
namespace precompiled
{
#if 0
contract KVTable {
    function get(string) public constant returns(bool, Entry);
    function set(string, Entry) public returns(bool, int);
    function newEntry() public constant returns(Entry);
}
#endif

class KVTablePrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<KVTablePrecompiled> Ptr;
    KVTablePrecompiled();
    virtual ~KVTablePrecompiled(){};


    std::string toString() override;

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& _sender = Address()) override;

    std::shared_ptr<dev::storage::Table> getTable() { return m_table; }
    void setTable(std::shared_ptr<dev::storage::Table> table) { m_table = table; }

    h256 hash();

private:
    std::shared_ptr<storage::Table> m_table;
};

}  // namespace precompiled

}  // namespace dev
