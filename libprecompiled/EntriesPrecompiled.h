
#pragma once

#include "libstorage/Table.h"
#include <libblockverifier/ExecutiveContext.h>

namespace dev
{
namespace precompiled
{
#if 0
contract Entries {
    function get(int) public constant returns(Entry);
    function size() public constant returns(int);
}
{
    "846719e0": "get(int256)",
    "949d225d": "size()"
}
#endif

class EntriesPrecompiled : public Precompiled
{
public:
    typedef std::shared_ptr<EntriesPrecompiled> Ptr;
    EntriesPrecompiled();
    virtual ~EntriesPrecompiled(){};

    std::string toString() override;

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& _sender = Address()) override;

    void setEntries(dev::storage::Entries::ConstPtr entries) { m_entriesConst = entries; }
    dev::storage::Entries::Ptr getEntries()
    {
        return std::const_pointer_cast<dev::storage::Entries>(m_entriesConst);
    }
    dev::storage::Entries::ConstPtr getEntries() const { return m_entriesConst; }

private:
    dev::storage::Entries::ConstPtr m_entriesConst;
};

}  // namespace precompiled

}  // namespace dev
