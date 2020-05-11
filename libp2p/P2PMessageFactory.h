
#pragma once

#include "P2PMessage.h"
#include "P2PMessageRC2.h"
#include <libconfig/GlobalConfigure.h>
#include <libnetwork/Common.h>
namespace dev
{
namespace p2p
{
class P2PMessageFactory : public dev::network::MessageFactory
{
public:
    typedef std::shared_ptr<P2PMessageFactory> Ptr;

    virtual ~P2PMessageFactory() {}
    dev::network::Message::Ptr buildMessage() override
    {
        auto message = std::make_shared<P2PMessage>();
        return message;
    }

    virtual uint32_t newSeq()
    {
        uint32_t seq = ++m_seq;
        return seq;
    }
    std::atomic<uint32_t> m_seq = {1};
};

class P2PMessageFactoryRC2 : public P2PMessageFactory
{
public:
    virtual ~P2PMessageFactoryRC2() {}
    dev::network::Message::Ptr buildMessage() override
    {
        auto message = std::make_shared<P2PMessageRC2>();
        return message;
    }
};

}  // namespace p2p
}  // namespace dev