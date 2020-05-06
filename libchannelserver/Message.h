
#pragma once


#include <libdevcore/Common.h>
#include <libdevcore/FixedHash.h>
#include <boost/lexical_cast.hpp>
#include <memory>
#include <queue>
#include <string>
#include <thread>

namespace dev
{
namespace channel
{
class Message : public std::enable_shared_from_this<Message>
{
public:
    typedef std::shared_ptr<Message> Ptr;

    Message() { m_data = std::make_shared<bytes>(); }
    virtual ~Message(){};

    virtual void encode(bytes& buffer) = 0;

    virtual ssize_t decode(const byte* buffer, size_t size) = 0;

    virtual uint32_t length() { return m_length; }

    virtual uint16_t type() { return m_type; }
    virtual void setType(uint16_t type) { m_type = type; }

    virtual std::string seq() { return m_seq; }
    virtual void setSeq(std::string seq) { m_seq = seq; }

    virtual int result() { return m_result; }
    virtual void setResult(int result) { m_result = result; }

    virtual byte* data() { return m_data->data(); }
    virtual size_t dataSize() { return m_data->size(); }

    virtual void setData(const byte* p, size_t size) { m_data->assign(p, p + size); }

    virtual void clearData() { m_data->clear(); }

protected:
    uint32_t m_length = 0;
    uint16_t m_type = 0;
    std::string m_seq = std::string(32, '0');
    int m_result = 0;

    std::shared_ptr<bytes> m_data;
};

class MessageFactory : public std::enable_shared_from_this<MessageFactory>
{
public:
    typedef std::shared_ptr<MessageFactory> Ptr;

    virtual ~MessageFactory(){};
    virtual Message::Ptr buildMessage() = 0;
};

}  // namespace channel

}  // namespace dev
