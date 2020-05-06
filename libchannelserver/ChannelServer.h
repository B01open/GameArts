

#pragma once

#include <libdevcore/FixedHash.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <queue>
#include <string>
#include <thread>

#include "ChannelException.h"
#include "ChannelSession.h"
#include "Message.h"
#include "libdevcore/ThreadPool.h"

namespace dev
{
namespace channel
{
class ChannelServer : public std::enable_shared_from_this<ChannelServer>
{
public:
    typedef std::shared_ptr<ChannelServer> Ptr;
    virtual ~ChannelServer() = default;
    virtual void run();

    void onAccept(const boost::system::error_code& error, ChannelSession::Ptr session);

    void startAccept();

    void setBind(const std::string& host, int port)
    {
        m_listenHost = host;
        m_listenPort = port;
    };

    void setEnableSSL(bool enableSSL) { m_enableSSL = enableSSL; };

    void setConnectionHandler(
        std::function<void(dev::channel::ChannelException, ChannelSession::Ptr)> handler)
    {
        m_connectionHandler = handler;
    };

    void setIOService(std::shared_ptr<boost::asio::io_service> ioService)
    {
        m_ioService = ioService;
    };
    void setSSLContext(std::shared_ptr<boost::asio::ssl::context> sslContext)
    {
        m_sslContext = sslContext;
    };

    MessageFactory::Ptr messageFactory() { return m_messageFactory; }
    void setMessageFactory(MessageFactory::Ptr messageFactory)
    {
        m_messageFactory = messageFactory;
    }

    virtual void stop();

private:
    void onHandshake(const boost::system::error_code& error, ChannelSession::Ptr session);

    std::shared_ptr<boost::asio::io_service> m_ioService;
    std::shared_ptr<boost::asio::ssl::context> m_sslContext;

    std::shared_ptr<std::thread> m_serverThread;

    std::shared_ptr<boost::asio::ip::tcp::acceptor> m_acceptor;
    ThreadPool::Ptr m_requestThreadPool;
    ThreadPool::Ptr m_responseThreadPool;

    std::function<void(dev::channel::ChannelException, ChannelSession::Ptr)> m_connectionHandler;
    MessageFactory::Ptr m_messageFactory;

    std::string m_listenHost = "";
    int m_listenPort = 0;
    bool m_enableSSL = false;
};

}  // namespace channel

}  // namespace dev
