 

/**
 * @brief : StorageStateFactory
 * @author: xingqiangbai
 * @date: 2018-10-26
 */


#pragma once

#include <libexecutive/StateFactoryInterface.h>

namespace dev
{
namespace storagestate
{
class StorageStateFactory : public dev::executive::StateFactoryInterface
{
public:
    StorageStateFactory(u256 const& _accountStartNonce) : m_accountStartNonce(_accountStartNonce) {}
    virtual ~StorageStateFactory() {}
    std::shared_ptr<dev::executive::StateFace> getState(
        h256 const& _root, std::shared_ptr<dev::storage::TableFactory> _factory) override;

private:
    u256 m_accountStartNonce;
};
}  // namespace storagestate
}  // namespace dev
