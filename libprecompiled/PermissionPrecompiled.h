
#pragma once
#include "Common.h"

namespace dev
{
namespace precompiled
{
#if 0
contract PermissionPrecompiled {
    function insert(string table_name, string addr) public returns(int256);
    function remove(string table_name, string addr) public returns(int256);
    function queryByName(string table_name) public constant returns(string);
}
#endif

/// _sys_table_access_ table fields
const std::string SYS_AC_TABLE_NAME = "table_name";
const std::string SYS_AC_ADDRESS = "address";
const std::string SYS_AC_ENABLENUM = "enable_num";

class PermissionPrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<PermissionPrecompiled> Ptr;
    PermissionPrecompiled();
    virtual ~PermissionPrecompiled(){};

    std::string toString() override;

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& _sender = Address()) override;

protected:
    void addPrefixToUserTable(std::string& tableName);

private:
    std::string queryPermission(std::shared_ptr<dev::blockverifier::ExecutiveContext> context,
        const std::string& tableName);
    int revokeWritePermission(std::shared_ptr<dev::blockverifier::ExecutiveContext> context,
        const std::string& tableName, const std::string& user, Address const& origin);
};

}  // namespace precompiled

}  // namespace dev
