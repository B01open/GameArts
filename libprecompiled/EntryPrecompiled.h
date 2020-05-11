
#pragma once

#include "libprecompiled/Precompiled.h"
#include "libstorage/Table.h"

namespace dev
{
namespace storage
{
class Entry;
}
namespace precompiled
{
#if 0
contract Entry {
    function getInt(string) public constant returns(int);
    function getBytes32(string) public constant returns(bytes32);
    function getBytes64(string) public constant returns(byte[64]);
    function getAddress(string) public constant returns(address);

    function set(string, int) public;
    function set(string, string) public;
}
{
    "fda69fae": "getInt(string)",
    "d52decd4": "getBytes64(string)",
    "27314f79": "getBytes32(string)",
    "bf40fac1": "getAddress(string)"
    "2ef8ba74": "set(string,int256)",
    "e942b516": "set(string,string)",
}
#endif

class EntryPrecompiled : public Precompiled
{
public:
    typedef std::shared_ptr<EntryPrecompiled> Ptr;
    EntryPrecompiled();
    virtual ~EntryPrecompiled(){};

    std::string toString() override;

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& _sender = Address()) override;

    void setEntry(dev::storage::Entry::Ptr entry) { m_entry = entry; }
    dev::storage::Entry::Ptr getEntry() const { return m_entry; };

private:
    dev::storage::Entry::Ptr m_entry;
};

}  // namespace precompiled

}  // namespace dev
