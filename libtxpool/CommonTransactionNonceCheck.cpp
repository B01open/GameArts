 
/**
 * @file: CommonTransactionNonceCheck.cpp
 * @author: yujiechen
 *
 * @date: 2018-11-08
 */
#include "CommonTransactionNonceCheck.h"
using namespace dev::eth;
namespace dev
{
namespace txpool
{
bool CommonTransactionNonceCheck::isNonceOk(dev::eth::Transaction const& _trans, bool needInsert)
{
    UpgradableGuard l(m_lock);
    {
        const auto& key = _trans.nonce();
        if (m_cache.count(key))
        {
            // dupulated transaction sync may cause duplicated nonce
            LOG(TRACE) << LOG_DESC("CommonTransactionNonceCheck: isNonceOk: duplicated nonce")
                       << LOG_KV("transHash", _trans.sha3().abridged());

            return false;
        }
        if (needInsert)
        {
            UpgradeGuard ul(l);
            m_cache.insert(key);
        }
        return true;
    }
    /// obtain lock failed
    return false;
}

void CommonTransactionNonceCheck::delCache(dev::eth::NonceKeyType const& key)
{
    UpgradableGuard l(m_lock);
    {
        auto iter = m_cache.find(key);
        if (iter != m_cache.end())
        {
            UpgradeGuard ul(l);
            m_cache.erase(iter);
        }
    }
}

void CommonTransactionNonceCheck::delCache(Transactions const& _transactions)
{
    UpgradableGuard l(m_lock);
    {
        std::vector<dev::eth::NonceKeyType> delList;
        for (unsigned i = 0; i < _transactions.size(); i++)
        {
            const auto& key = _transactions[i]->nonce();
            if (m_cache.count(key))
            {
                delList.push_back(key);
            }
        }

        if (delList.size() > 0)
        {
            UpgradeGuard ul(l);
            for (auto key : delList)
            {
                m_cache.erase(key);
            }
        }
    }
}

void CommonTransactionNonceCheck::insertCache(dev::eth::Transaction const& _transaction)
{
    WriteGuard l(m_lock);
    {
        m_cache.insert(_transaction.nonce());
    }
}

}  // namespace txpool
}  // namespace dev
