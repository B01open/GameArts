
#pragma once
#include "PBFTReqCache.h"
#include <libethcore/PartiallyBlock.h>

#define PartiallyPBFTReqCache_LOG(LEVEL) \
    LOG(LEVEL) << LOG_BADGE("CONSENSUS") << LOG_BADGE("PartiallyPBFTReqCache")


namespace dev
{
namespace consensus
{
class PartiallyPBFTReqCache : public PBFTReqCache
{
public:
    using Ptr = std::shared_ptr<PartiallyPBFTReqCache>;

    PartiallyPBFTReqCache() : PBFTReqCache() {}
    ~PartiallyPBFTReqCache() override {}

    virtual bool addPartiallyRawPrepare(PrepareReq::Ptr _partiallyRawPrepare);
    PrepareReq::Ptr partiallyRawPrepare() { return m_partiallyRawPrepare; }
    virtual void transPartiallyPrepareIntoRawPrepare()
    {
        WriteGuard l(x_rawPrepareCache);
        m_rawPrepareCache = m_partiallyRawPrepare;
        m_partiallyRawPrepare.reset();
        m_rawPrepareCache->pBlock->encode(*m_rawPrepareCache->block);
        if (m_randomSendRawPrepareStatusCallback)
        {
            m_randomSendRawPrepareStatusCallback(m_rawPrepareCache);
        }
    }

    // fetch missed transaction
    virtual bool fetchMissedTxs(std::shared_ptr<bytes> _encodedBytes, bytesConstRef _missInfo);
    // fill block with fetched transaction
    virtual bool fillBlock(bytesConstRef _txsData);
    bool fillBlock(PrepareReq::Ptr _prepareReq, RLP const& _txsRLP);
    bool fillPrepareCacheBlock(RLP const& _txsRLP);
    virtual void addPreRawPrepare(PrepareReq::Ptr _preRawPrepare);

    virtual void clearPreRawPrepare();

    virtual void addPartiallyFuturePrepare(PrepareReq::Ptr _futurePrepare);
    bool existInFuturePrepare(dev::h256 const& _blockHash);
    void fillFutureBlock(RLP const& _txsRLP);

private:
    PrepareReq::Ptr m_partiallyRawPrepare;
    // add the prepareReq into m_preRawPrepare once leader generate the prepareReq
    // this cache is used to response txs to the request-sealers after generate prepareReq while
    // before addRawPrepareReq clear this cache when addRawPrepare
    PrepareReq::Ptr m_preRawPrepare;
    mutable SharedMutex x_preRawPrepare;
    PrepareReq::Ptr m_partiallyFuturePrepare;
};
}  // namespace consensus
}  // namespace dev