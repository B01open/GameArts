
#pragma once
#include "Common.h"
namespace dev
{
namespace precompiled
{
enum ContractStatus
{
    Invalid = 0,
    Available,
    Frozen,
    AddressNonExistent,
    NotContractAddress,
    Count
};

const std::string CONTRACT_STATUS_DESC[ContractStatus::Count] = {"Invalid",
    "The contract is available.",
    "The contract has been frozen. You can invoke this contract after unfreezing it.",
    "The address is nonexistent.", "This is not a contract address."};

const std::string STATUS_TRUE = "true";
const std::string STATUS_FALSE = "false";

class ContractLifeCyclePrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<ContractLifeCyclePrecompiled> Ptr;
    ContractLifeCyclePrecompiled();
    virtual ~ContractLifeCyclePrecompiled(){};

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& _sender = Address()) override;

private:
    bool checkPermission(std::shared_ptr<blockverifier::ExecutiveContext> context,
        std::string const& tableName, Address const& origin);
    ContractStatus getContractStatus(
        std::shared_ptr<blockverifier::ExecutiveContext> context, std::string const& tableName);
    int updateFrozenStatus(std::shared_ptr<blockverifier::ExecutiveContext> context,
        std::string const& tableName, std::string const& frozen, Address const& origin);
    void freeze(std::shared_ptr<blockverifier::ExecutiveContext> context, bytesConstRef data,
        Address const& origin, bytes& out);
    void unfreeze(std::shared_ptr<blockverifier::ExecutiveContext> context, bytesConstRef data,
        Address const& origin, bytes& out);
    void grantManager(std::shared_ptr<blockverifier::ExecutiveContext> context, bytesConstRef data,
        Address const& origin, bytes& out);
    void getStatus(
        std::shared_ptr<blockverifier::ExecutiveContext> context, bytesConstRef data, bytes& out);
    void listManager(
        std::shared_ptr<blockverifier::ExecutiveContext> context, bytesConstRef data, bytes& out);
};

}  // namespace precompiled

}  // namespace dev
