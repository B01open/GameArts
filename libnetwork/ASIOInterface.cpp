
#include "ASIOInterface.h"

namespace ba = boost::asio;
namespace bi = ba::ip;
using namespace dev::network;

void ASIOInterface::asyncResolveConnect(std::shared_ptr<SocketFace> socket, Handler_Type handler,
    const bi::tcp::resolver::protocol_type& _protocol)
{
    m_resolver->async_resolve(_protocol, socket->nodeIPEndpoint().host,
        socket->nodeIPEndpoint().port,
        [=](const boost::system::error_code& ec, bi::tcp::resolver::results_type results) {
            if (!ec)
            {
                // results is a iterator, but only use first endpoint.
                socket->ref().async_connect(results->endpoint(), handler);
                ASIO_LOG(INFO) << LOG_DESC("asyncResolveConnect")
                               << LOG_KV("endpoint", results->endpoint());
            }
            else
            {
                ASIO_LOG(WARNING) << LOG_DESC("asyncResolve failed")
                                  << LOG_KV("host", socket->nodeIPEndpoint().host)
                                  << LOG_KV("port", socket->nodeIPEndpoint().port);
            }
        });
}
