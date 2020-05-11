

#pragma once
#include "Common.h"
#include <libethcore/PrecompiledContract.h>
#include <libledger/Ledger.h>
#include <libledger/LedgerManager.h>
#include <libp2p/Service.h>
#include <functional>
#include <vector>

using namespace dev::ledger;

namespace dev
{
namespace initializer
{
class LedgerInitializer : public std::enable_shared_from_this<LedgerInitializer>
{
public:
    typedef std::shared_ptr<LedgerInitializer> Ptr;

    void initConfig(boost::property_tree::ptree const& _pt);
    void startMoreLedger();

    std::shared_ptr<LedgerManager> ledgerManager() { return m_ledgerManager; }

    void setP2PService(std::shared_ptr<dev::p2p::P2PInterface> _p2pService)
    {
        m_p2pService = _p2pService;
    }
    void setChannelRPCServer(ChannelRPCServer::Ptr _channelRPCServer)
    {
        m_channelRPCServer = _channelRPCServer;
    }
    void setKeyPair(KeyPair const& _keyPair) { m_keyPair = _keyPair; }

    ~LedgerInitializer() { stopAll(); }

    void startAll()
    {
        if (m_ledgerManager)
            m_ledgerManager->startAll();
    }

    void stopAll()
    {
        if (m_ledgerManager)
            m_ledgerManager->stopAll();
    }

private:
    std::vector<dev::GROUP_ID> initLedgers();
    std::vector<dev::GROUP_ID> foreachLedgerConfigure(const std::string& _groupConfigPath,
        std::function<bool(dev::GROUP_ID const&, const std::string&)> _f);
    bool initLedger(dev::GROUP_ID const& _groupId, std::string const& _dataDir = "data",
        std::string const& _configFileName = "");
    std::shared_ptr<LedgerManager> m_ledgerManager;
    std::shared_ptr<dev::p2p::P2PInterface> m_p2pService;
    ChannelRPCServer::Ptr m_channelRPCServer;
    KeyPair m_keyPair;
    std::string m_groupDataDir;
    std::string m_groupConfigPath;
};

}  // namespace initializer

}  // namespace dev
