

#pragma once
#include "Common.h"
#include <boost/beast.hpp>
namespace dev
{
namespace network
{
class SocketFace
{
public:
    SocketFace() = default;

    virtual ~SocketFace(){};
    virtual bool isConnected() const = 0;
    virtual void close() = 0;
    virtual bi::tcp::endpoint remoteEndpoint(
        boost::system::error_code ec = boost::system::error_code()) = 0;

    virtual bi::tcp::socket& ref() = 0;
    virtual ba::ssl::stream<bi::tcp::socket>& sslref() = 0;
    virtual boost::beast::websocket::stream<ba::ssl::stream<bi::tcp::socket>>& wsref() = 0;

    virtual const NodeIPEndpoint& nodeIPEndpoint() const = 0;
    virtual void setNodeIPEndpoint(NodeIPEndpoint _nodeIPEndpoint) = 0;
};
}  // namespace network
}  // namespace dev
