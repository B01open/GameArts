
#pragma once
#include "Common.h"
#include <libethcore/BlockFactory.h>
#include <libethcore/Protocol.h>
namespace dev
{
namespace consensus
{
class ConsensusInterface
{
public:
    using Ptr = std::shared_ptr<ConsensusInterface>;
    ConsensusInterface() = default;
    virtual ~ConsensusInterface(){};

    /// start the consensus module
    virtual void start() = 0;
    /// stop the consensus module
    virtual void stop() = 0;

    /// get sealer list
    virtual h512s sealerList() const = 0;
    virtual h512s consensusList() const = 0;
    /// set the sealer list
    /// virtual void setSealerList(h512s const& _sealerList) = 0;
    virtual void appendSealer(h512 const& _sealer) = 0;
    /// get status of consensus
    virtual const std::string consensusStatus() = 0;

    /// protocol id used when register handler to p2p module
    virtual PROTOCOL_ID const& protocolId() const = 0;
    virtual GROUP_ID groupId() const { return 0; };
    /// get node account type
    virtual NodeAccountType accountType() = 0;
    /// set the node account type
    virtual void setNodeAccountType(NodeAccountType const&) = 0;
    virtual IDXTYPE nodeIdx() const = 0;
    /// update the context of PBFT after commit a block into the block-chain
    virtual void reportBlock(dev::eth::Block const& block) = 0;
    virtual uint64_t maxBlockTransactions() { return 1000; }
    virtual VIEWTYPE view() const { return 0; }
    virtual VIEWTYPE toView() const { return 0; }
    virtual void setBlockFactory(dev::eth::BlockFactory::Ptr) {}
};
}  // namespace consensus
}  // namespace dev
