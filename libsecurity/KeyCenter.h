 
/**
 * @brief : keycenter for disk encrytion
 * @author: jimmyshi
 * @date: 2018-12-03
 */
#pragma once
#include "Common.h"
#include <libdevcore/Common.h>
#include <libdevcore/Guards.h>
#include <libethcore/CommonJS.h>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <cstdlib>
#include <memory>
#include <string>

namespace Json
{
class Value;
}

namespace dev
{
#define KC_LOG(_OBV)        \
    LOG(_OBV) << "[g:null]" \
              << "[p:null][KeyManager]"

class KeyCenterHttpClientInterface
{
public:
    using Ptr = std::shared_ptr<KeyCenterHttpClientInterface>;
    virtual ~KeyCenterHttpClientInterface(){};
    virtual void connect() = 0;
    virtual void close() = 0;
    virtual Json::Value callMethod(const std::string& _method, Json::Value _params) = 0;
};

class KeyCenterHttpClient : public KeyCenterHttpClientInterface
{
public:
    using Ptr = std::shared_ptr<KeyCenterHttpClient>;

    KeyCenterHttpClient(const std::string& _ip, int _port);
    ~KeyCenterHttpClient();
    void connect() override;
    void close() override;
    Json::Value callMethod(const std::string& _method, Json::Value _params) override;

private:
    std::string m_ip;
    int m_port;
    boost::asio::io_context m_ioc;
    boost::asio::ip::tcp::socket m_socket;
    mutable SharedMutex x_clinetSocket;
};

class KeyCenter
{
public:
    using Ptr = std::shared_ptr<KeyCenter>;

    KeyCenter(){};
    virtual ~KeyCenter(){};
    virtual const dev::bytes getDataKey(const std::string& _cipherDataKey);
    void setIpPort(const std::string& _ip, int _port);
    const std::string url() { return m_ip + ":" + std::to_string(m_port); }
    void setKcClient(KeyCenterHttpClientInterface::Ptr _kcclient) { m_kcclient = _kcclient; };
    dev::bytes uniformDataKey(const dev::bytes& _readableDataKey);

    void clearCache()
    {
        m_lastQueryCipherDataKey.clear();
        m_lastRcvDataKey.clear();
    }

private:
    std::string m_ip;
    int m_port;
    std::string m_url;

    KeyCenterHttpClientInterface::Ptr m_kcclient = nullptr;

    // Query cache
    std::string m_lastQueryCipherDataKey;
    dev::bytes m_lastRcvDataKey;
};

}  // namespace dev