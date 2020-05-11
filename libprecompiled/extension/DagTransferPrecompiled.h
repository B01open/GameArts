 
/** @file DagTransferPrecompiled.h
 *  @author octopuswang
 *  @date 20190111
 */
#pragma once
#include <libblockverifier/ExecutiveContext.h>
#include <libprecompiled/Common.h>

#include <libdevcore/Common.h>
#include <libethcore/Common.h>

namespace dev
{
namespace storage
{
class Table;
}

namespace precompiled
{
class DagTransferPrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<DagTransferPrecompiled> Ptr;
    DagTransferPrecompiled();
    virtual ~DagTransferPrecompiled(){};

    std::string toString() override;

    bytes call(dev::blockverifier::ExecutiveContext::Ptr context, bytesConstRef param,
        Address const& origin = Address(), Address const& sender = Address()) override;

public:
    // is this precompiled need parallel processing, default false.
    virtual bool isParallelPrecompiled() override { return true; }
    virtual std::vector<std::string> getParallelTag(bytesConstRef param) override;

protected:
    std::shared_ptr<storage::Table> openTable(
        dev::blockverifier::ExecutiveContext::Ptr context, Address const& origin);

public:
    bool invalidUserName(const std::string& user);
    void userAddCall(dev::blockverifier::ExecutiveContext::Ptr context, bytesConstRef data,
        Address const& origin, bytes& out);
    void userSaveCall(dev::blockverifier::ExecutiveContext::Ptr context, bytesConstRef data,
        Address const& origin, bytes& out);
    void userDrawCall(dev::blockverifier::ExecutiveContext::Ptr context, bytesConstRef data,
        Address const& origin, bytes& out);
    void userBalanceCall(dev::blockverifier::ExecutiveContext::Ptr context, bytesConstRef data,
        Address const& origin, bytes& out);
    void userTransferCall(dev::blockverifier::ExecutiveContext::Ptr context, bytesConstRef data,
        Address const& origin, bytes& out);
};

}  // namespace precompiled

}  // namespace dev
