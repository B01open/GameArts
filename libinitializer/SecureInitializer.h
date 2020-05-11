

#pragma once

#include "Common.h"
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <map>

namespace bas = boost::asio::ssl;
namespace dev
{
namespace initializer
{
DEV_SIMPLE_EXCEPTION(SecureInitializerNotInitConfig);
DEV_SIMPLE_EXCEPTION(PrivateKeyError);
DEV_SIMPLE_EXCEPTION(PrivateKeyNotExists);
DEV_SIMPLE_EXCEPTION(CertificateError);
DEV_SIMPLE_EXCEPTION(CertificateNotExists);

class SecureInitializer : public std::enable_shared_from_this<SecureInitializer>
{
public:
    typedef std::shared_ptr<SecureInitializer> Ptr;

    enum class Usage
    {
        Default,
        ForP2P,
        ForRPC
    };

    void initConfig(const boost::property_tree::ptree& _pt);

    std::shared_ptr<bas::context> SSLContext(Usage _usage = Usage::Default);
    const KeyPair& keyPair() { return m_key; }

private:
    void completePath(std::string& _path);
    KeyPair m_key;
    std::map<Usage, std::shared_ptr<boost::asio::ssl::context>> m_sslContexts;
};

}  // namespace initializer

}  // namespace dev
