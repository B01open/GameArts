 
/**
 * @file: TransactionNonceCheck.h
 * @author: toxotguo
 *
 * @date: 2017
 */

#pragma once
#include "CommonTransactionNonceCheck.h"
#include <libblockchain/BlockChainInterface.h>
#include <boost/timer.hpp>
#include <thread>

using namespace dev::eth;
using namespace dev::blockchain;

#define NONCECHECKER_LOG(LEVEL) \
    LOG(LEVEL) << LOG_BADGE("TXPOOL") << LOG_BADGE("TransactionNonceChecker")

namespace dev
{
namespace txpool
{
using NonceVec = std::vector<dev::eth::NonceKeyType>;
class TransactionNonceCheck : public CommonTransactionNonceCheck
{
public:
    TransactionNonceCheck(std::shared_ptr<dev::blockchain::BlockChainInterface> const& _blockChain)
      : CommonTransactionNonceCheck(), m_blockChain(_blockChain)
    {
        init();
    }
    ~TransactionNonceCheck() {}
    void init();
    bool ok(dev::eth::Transaction const& _transaction);
    void updateCache(bool _rebuild = false);
    unsigned const& maxBlockLimit() const { return m_maxBlockLimit; }
    void setBlockLimit(unsigned const& limit) { m_maxBlockLimit = limit; }

    bool isBlockLimitOk(dev::eth::Transaction const& _trans);

    std::shared_ptr<dev::txpool::NonceVec> getNonceAndUpdateCache(
        int64_t const& blockNumber, bool const& update = true);

private:
    std::shared_ptr<dev::blockchain::BlockChainInterface> m_blockChain;
    std::vector<NonceVec> nonce_vec;
    /// cache the block nonce to in case of accessing the DB to get nonces of given block frequently
    /// key: block number
    /// value: all the nonces of a given block
    /// we cache at most m_maxBlockLimit entries(occuppy about 32KB)
    std::map<int64_t, std::shared_ptr<NonceVec> > m_blockNonceCache;

    int64_t m_startblk;
    int64_t m_endblk;
    unsigned m_maxBlockLimit = 1000;
    int64_t m_blockNumber;
};
}  // namespace txpool
}  // namespace dev
