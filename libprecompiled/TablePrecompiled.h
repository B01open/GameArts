 
/** @file TablePrecompiled.h
 *  @author ancelmo
 *  @date 20180921
 */
#pragma once

#include "libprecompiled/Precompiled.h"

namespace dev
{
#if 0
contract Table {
    function select(string, Condition) public constant returns(Entries);
    function insert(string, Entry) public returns(int);
    function update(string, Entry, Condition) public returns(int);
    function remove(string, Condition) public returns(int);
    function newEntry() public constant returns(Entry);
    function newCondition() public constant returns(Condition);
}
{
    "31afac36": "insert(string,address)",
    "7857d7c9": "newCondition()",
    "13db9346": "newEntry()",
    "28bb2117": "remove(string,address)",
    "e8434e39": "select(string,address)",
    "bf2b70a1": "update(string,address,address)"
}
#endif
namespace precompiled
{
class TablePrecompiled : public Precompiled
{
public:
    typedef std::shared_ptr<TablePrecompiled> Ptr;
    TablePrecompiled();
    virtual ~TablePrecompiled(){};


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
