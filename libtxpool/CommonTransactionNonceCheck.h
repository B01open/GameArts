 
/**
 * @file: CommonTransactonNonceCheck.h
 * @author: yujiechen
 *
 * @date: 2018-11-08
 */
#pragma once

#include <libdevcore/Common.h>
#include <libdevcore/CommonIO.h>
#include <libdevcore/Guards.h>
#include <libethcore/Block.h>
#include <libethcore/Protocol.h>
#include <libethcore/Transaction.h>
#include <unordered_set>
namespace dev
{
namespace txpool
{
class CommonTransactionNonceCheck
{
public:
    CommonTransactionNonceCheck() {}
    virtual ~CommonTransactionNonceCheck() = default;
    virtual void delCache(dev::eth::NonceKeyType const& key);
    virtual void delCache(dev::eth::Transactions const& _transactions);
    virtual void insertCache(dev::eth::Transaction const& _transaction);
    virtual bool isNonceOk(dev::eth::Transaction const& _trans, bool needInsert = false);

protected:
    mutable SharedMutex m_lock;
    std::unordered_set<dev::eth::NonceKeyType> m_cache;
};
}  // namespace txpool
}  // namespace dev