
#pragma once
#include <json/json.h>
#include <libblockverifier/BlockVerifierInterface.h>
#include <libblockverifier/ExecutiveContext.h>
#include <libdevcore/FixedHash.h>
#include <libethcore/BlockFactory.h>

#define SEAL_LOG(LEVEL) LOG(LEVEL) << LOG_BADGE("CONSENSUS") << LOG_BADGE("SEALER")
#define ENGINE_LOG(LEVEL) LOG(LEVEL) << LOG_BADGE("CONSENSUS") << LOG_BADGE("ConsensusEngine")
namespace dev
{
namespace consensus
{
typedef uint16_t IDXTYPE;
typedef int64_t VIEWTYPE;
static const IDXTYPE MAXIDX = UINT16_MAX;
static const VIEWTYPE MAXVIEW = INT64_MAX;
static const uint8_t MAXTTL = 2;
DEV_SIMPLE_EXCEPTION(DisabledFutureTime);
DEV_SIMPLE_EXCEPTION(OverThresTransNum);
DEV_SIMPLE_EXCEPTION(InvalidBlockHeight);
DEV_SIMPLE_EXCEPTION(ExistedBlock);
DEV_SIMPLE_EXCEPTION(ParentNoneExist);
DEV_SIMPLE_EXCEPTION(WrongParentHash);
DEV_SIMPLE_EXCEPTION(BlockSealerListWrong);

enum NodeAccountType
{
    ObserverAccount = 0,
    SealerAccount
};

class Sealing
{
public:
    Sealing() {}
    Sealing(dev::eth::BlockFactory::Ptr _blockFactory) { setBlockFactory(_blockFactory); }
    void setBlockFactory(dev::eth::BlockFactory::Ptr _blockFactory)
    {
        m_blockFactory = _blockFactory;
        block = m_blockFactory->createBlock();
    }

    std::shared_ptr<dev::eth::Block> block;
    /// hash set for filter fetched transactions
    h256Hash m_transactionSet;
    dev::blockverifier::ExecutiveContext::Ptr p_execContext;
    dev::eth::BlockFactory::Ptr m_blockFactory;
};

}  // namespace consensus
}  // namespace dev
