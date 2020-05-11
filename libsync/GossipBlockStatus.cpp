 
/**
 * @brief : block status gossip implementation
 * @author: yujiechen
 * @date: 2019-10-08
 */
#include "GossipBlockStatus.h"

using namespace dev;
using namespace dev::sync;

// start gossip thread
void GossipBlockStatus::start()
{
    if (m_running)
    {
        GOSSIP_LOG(INFO) << LOG_DESC("GossipBlockStatus already started");
        return;
    }
    // start gossipBlockStatus worker
    startWorking();
    m_running = true;
    GOSSIP_LOG(INFO) << LOG_DESC("start GossipBlockStatus succ");
}

// stop the gossip thread
void GossipBlockStatus::stop()
{
    if (!m_running)
    {
        GOSSIP_LOG(INFO) << LOG_DESC("GossipBlockStatus already stopped");
        return;
    }
    GOSSIP_LOG(INFO) << LOG_DESC("stop GossipBlockStatus succ");
    m_running = false;
    doneWorking();
    if (isWorking())
    {
        stopWorking();
        terminate();
    }
}

void GossipBlockStatus::doWork()
{
    assert(m_gossipBlockStatusHandler);
    m_gossipBlockStatusHandler(m_gossipPeersNumber);
}