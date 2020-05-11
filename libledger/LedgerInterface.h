
#pragma once
#include "LedgerParamInterface.h"
#include <libblockchain/BlockChainInterface.h>
#include <libblockverifier/BlockVerifierInterface.h>
#include <libchannelserver/ChannelRPCServer.h>
#include <libconsensus/ConsensusInterface.h>
#include <libethcore/Protocol.h>
#include <libsync/SyncInterface.h>
#include <libtxpool/TxPoolInterface.h>
#include <memory>
namespace dev
{
namespace event
{
class EventLogFilterManager;
}

namespace ledger
{
class LedgerInterface
{
public:
    LedgerInterface(dev::KeyPair const& keyPair) : m_keyPair(keyPair) {}

    virtual ~LedgerInterface(){};
    /// init the ledger(called by initializer)
    virtual bool initLedger(std::shared_ptr<LedgerParamInterface> _ledgerParams) = 0;

    virtual std::shared_ptr<dev::txpool::TxPoolInterface> txPool() const = 0;
    virtual std::shared_ptr<dev::blockverifier::BlockVerifierInterface> blockVerifier() const = 0;
    virtual std::shared_ptr<dev::blockchain::BlockChainInterface> blockChain() const = 0;
    virtual std::shared_ptr<dev::consensus::ConsensusInterface> consensus() const = 0;
    virtual std::shared_ptr<dev::sync::SyncInterface> sync() const = 0;
    virtual dev::GROUP_ID const& groupId() const = 0;
    virtual std::shared_ptr<LedgerParamInterface> getParam() const = 0;
    virtual void startAll() = 0;
    virtual void stopAll() = 0;
    virtual dev::KeyPair const& keyPair() const { return m_keyPair; };
    virtual void setChannelRPCServer(ChannelRPCServer::Ptr channelRPCServer)
    {
        (void)channelRPCServer;
    };
    virtual std::shared_ptr<dev::event::EventLogFilterManager> getEventLogFilterManager() = 0;

protected:
    dev::KeyPair m_keyPair;
};
}  // namespace ledger
}  // namespace dev
