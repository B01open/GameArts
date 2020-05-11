 
/**
 * @brief : block status gossip implementation
 * @author: yujiechen
 * @date: 2019-10-08
 */
#pragma once
#include <libdevcore/Worker.h>
#include <libethcore/Protocol.h>

#define GOSSIP_LOG(_OBV) LOG(_OBV) << LOG_BADGE("GossipBlockStatus")

namespace dev
{
namespace sync
{
class GossipBlockStatus : public Worker
{
public:
    using Ptr = std::shared_ptr<GossipBlockStatus>;
    GossipBlockStatus(dev::PROTOCOL_ID const& _protocolId, int64_t const& _gossipInterval,
        int64_t const& _gossipPeersNumber)
      : Worker("gossip-" + std::to_string(dev::eth::getGroupAndProtocol(_protocolId).first),
            _gossipInterval),
        m_gossipPeersNumber(_gossipPeersNumber)
    {}
    void registerGossipHandler(std::function<void(int64_t const&)> const& _gossipBlockStatusHandler)
    {
        m_gossipBlockStatusHandler = _gossipBlockStatusHandler;
    }
    // start gossip thread
    virtual void start();
    // stop the gossip thread
    virtual void stop();

    // gossip block status
    void doWork() override;

private:
    // send block status to random neighbors every m_gossipInterval
    std::atomic_bool m_running = {false};
    std::int64_t m_gossipPeersNumber = 3;
    std::function<void(int64_t const&)> m_gossipBlockStatusHandler = nullptr;
};
}  // namespace sync
}  // namespace dev