

#pragma once
#include "Common.h"                             // for INITIALIZER_LOG
#include "librpc/ModularServer.h"               // for ModularServer
#include <libchannelserver/ChannelRPCServer.h>  // for ChannelRPCServer
#include <boost/property_tree/ptree_fwd.hpp>    // for ptree
#include <vector>                               // for vector

namespace boost
{
namespace asio
{
namespace ssl
{
class context;
}
}  // namespace asio
}  // namespace boost


namespace dev
{
class SafeHttpServer;
namespace ledger
{
class LedgerManager;
}
namespace p2p
{
class P2PInterface;
}
namespace rpc
{
class Rpc;
}
namespace initializer
{
class RPCInitializer : public std::enable_shared_from_this<RPCInitializer>
{
public:
    typedef std::shared_ptr<RPCInitializer> Ptr;

    virtual ~RPCInitializer() { stop(); }

    void stop()
    {
        /// stop channel first
        if (m_channelRPCHttpServer)
        {
            m_channelRPCHttpServer->StopListening();
            delete m_channelRPCHttpServer;
            m_channelRPCHttpServer = nullptr;
            INITIALIZER_LOG(INFO) << "ChannelRPCHttpServer deleted.";
        }
        if (m_jsonrpcHttpServer)
        {
            m_jsonrpcHttpServer->StopListening();
            delete m_jsonrpcHttpServer;
            m_jsonrpcHttpServer = nullptr;
            INITIALIZER_LOG(INFO) << "JsonrpcHttpServer deleted.";
        }
    }

    void initChannelRPCServer(boost::property_tree::ptree const& _pt);

    void initConfig(boost::property_tree::ptree const& _pt);
    void setP2PService(std::shared_ptr<p2p::P2PInterface> _p2pService)
    {
        m_p2pService = _p2pService;
    }
    void setSSLContext(std::shared_ptr<boost::asio::ssl::context> sslContext)
    {
        m_sslContext = sslContext;
    }
    void setLedgerManager(std::shared_ptr<ledger::LedgerManager> _ledgerManager)
    {
        m_ledgerManager = _ledgerManager;
    }

    ChannelRPCServer::Ptr channelRPCServer() { return m_channelRPCServer; }
    std::shared_ptr<ledger::LedgerManager> getLedgerManager() { return m_ledgerManager; }

private:
    std::shared_ptr<p2p::P2PInterface> m_p2pService;
    std::shared_ptr<ledger::LedgerManager> m_ledgerManager;
    std::shared_ptr<boost::asio::ssl::context> m_sslContext;
    std::shared_ptr<dev::rpc::Rpc> m_rpcForChannel;
    std::shared_ptr<dev::SafeHttpServer> m_safeHttpServer;
    ChannelRPCServer::Ptr m_channelRPCServer;
    ModularServer<>* m_channelRPCHttpServer;
    ModularServer<>* m_jsonrpcHttpServer;
};

}  // namespace initializer

}  // namespace dev
