
#pragma once
#include "Common.h"

#if 0
contract CNS
{
    function insert(string name, string version, string addr, string abi) public returns(uint256);
    function selectByName(string name) public constant returns(string);
    function selectByNameAndVersion(string name, string version) public constant returns(string);
}
#endif

namespace dev
{
const std::string SYS_CNS_FIELD_NAME = "name";
const std::string SYS_CNS_FIELD_VERSION = "version";
const std::string SYS_CNS_FIELD_ADDRESS = "address";
const std::string SYS_CNS_FIELD_ABI = "abi";

namespace precompiled
{
class CNSPrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<CNSPrecompiled> Ptr;
    CNSPrecompiled();
    virtual ~CNSPrecompiled(){};

    std::string toString() override;

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& _sender = Address()) override;
};

}  // namespace precompiled

}  // namespace dev