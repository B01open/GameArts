

#pragma once

#include "Common.h"
#include "SocketFace.h"
#include <libdevcore/FileSystem.h>
#include <openssl/ec.h>
#include <openssl/ssl.h>
#include <boost/beast.hpp>
#include <boost/filesystem.hpp>

namespace dev
{
namespace network
{
class Socket : public SocketFace, public std::enable_shared_from_this<Socket>
{
public:
    Socket(
        ba::io_service& _ioService, ba::ssl::context& _sslContext, NodeIPEndpoint _nodeIPEndpoint)
      : m_nodeIPEndpoint(_nodeIPEndpoint)
    {
        try
        {
            m_wsSocket =
                std::make_shared<boost::beast::websocket::stream<ba::ssl::stream<bi::tcp::socket>>>(
                    _ioService, _sslContext);
        }
        catch (Exception const& _e)
        {
            SESSION_LOG(ERROR) << "ERROR: " << diagnostic_information(_e);
            SESSION_LOG(ERROR) << "Ssl Socket Init Fail! Please Check CERTIFICATE!";
        }
    }
    ~Socket() { close(); }

    virtual bool isConnected() const override { return m_wsSocket->lowest_layer().is_open(); }

    virtual void close() override
    {
        try
        {
            boost::system::error_code ec;
            m_wsSocket->lowest_layer().shutdown(bi::tcp::socket::shutdown_both, ec);
            if (m_wsSocket->lowest_layer().is_open())
                m_wsSocket->lowest_layer().close();
        }
        catch (...)
        {
        }
    }

    virtual bi::tcp::endpoint remoteEndpoint(
        boost::system::error_code ec = boost::system::error_code()) override
    {
        return m_wsSocket->lowest_layer().remote_endpoint(ec);
    }

    virtual bi::tcp::socket& ref() override { return m_wsSocket->next_layer().next_layer(); }
    virtual ba::ssl::stream<bi::tcp::socket>& sslref() override { return m_wsSocket->next_layer(); }
    virtual boost::beast::websocket::stream<ba::ssl::stream<bi::tcp::socket>>& wsref() override
    {
        return *m_wsSocket;
    }

    virtual const NodeIPEndpoint& nodeIPEndpoint() const override { return m_nodeIPEndpoint; }
    virtual void setNodeIPEndpoint(NodeIPEndpoint _nodeIPEndpoint) override
    {
        m_nodeIPEndpoint = _nodeIPEndpoint;
    }

protected:
    NodeIPEndpoint m_nodeIPEndpoint;
    std::shared_ptr<boost::beast::websocket::stream<ba::ssl::stream<bi::tcp::socket>>> m_wsSocket;
};

}  // namespace network
}  // namespace dev
