 
/** @file RingSigPrecompiled.h
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
contract RingSig
{
    function ringSigVerify(string signature, string message, string paramInfo) public constant returns(bool);
}
#endif

class RingSigPrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<RingSigPrecompiled> Ptr;
    RingSigPrecompiled();
    virtual ~RingSigPrecompiled(){};

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& sender = Address()) override;
};

}  // namespace precompiled
}  // namespace dev
