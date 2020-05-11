 
/** @file GroupSigPrecompiled.h
 *  @author shawnhe
 *  @date 20190821
 */

#pragma once
#include <libblockverifier/ExecutiveContext.h>
#include <libprecompiled/Common.h>

namespace dev
{
namespace precompiled
{
#if 0
contract GroupSig
{
    function groupSigVerify(string signature, string message, string gpkInfo, string paramInfo) public constant returns(bool);
}
#endif

class GroupSigPrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<GroupSigPrecompiled> Ptr;
    GroupSigPrecompiled();
    virtual ~GroupSigPrecompiled(){};

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& sender = Address()) override;
};

}  // namespace precompiled
}  // namespace dev
