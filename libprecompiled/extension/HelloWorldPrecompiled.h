 
/** @file DagTransferPrecompiled.h
 *  @author octopuswang
 *  @date 20190111
 */
#pragma once
#include <libprecompiled/Common.h>

namespace dev
{
namespace precompiled
{
class HelloWorldPrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<HelloWorldPrecompiled> Ptr;
    HelloWorldPrecompiled();
    virtual ~HelloWorldPrecompiled(){};

    std::string toString() override;

    virtual bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> _context,
        bytesConstRef _param, Address const& _origin = Address(),
        Address const& _sender = Address()) override;
};

}  // namespace precompiled

}  // namespace dev