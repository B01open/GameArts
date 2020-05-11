 
/** @file PaillierPrecompiled.h
 *  @author shawnhe
 *  @date 20190808
 */

#pragma once
#include <libblockverifier/ExecutiveContext.h>
#include <libprecompiled/Common.h>

class CallPaillier;
namespace dev
{
namespace precompiled
{
#if 0
contract Paillier 
{
    function paillierAdd(string cipher1, string cipher2) public constant returns(string);
}
#endif

class PaillierPrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<PaillierPrecompiled> Ptr;
    PaillierPrecompiled();
    virtual ~PaillierPrecompiled(){};

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& sender = Address()) override;

private:
    std::shared_ptr<CallPaillier> m_callPaillier;
};

}  // namespace precompiled
}  // namespace dev
