

#pragma once

#include <string>
#define CHANNEL_LOG(LEVEL) LOG(LEVEL) << "[CHANNEL]"
#define CHANNEL_SESSION_LOG(LEVEL) LOG(LEVEL) << "[CHANNEL][SESSION]"
#pragma warning(push)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#include <boost/exception/diagnostic_information.hpp>
#pragma warning(pop)
#pragma GCC diagnostic pop
namespace dev
{
namespace channel
{
class ChannelException : public std::exception
{
public:
    ChannelException(){};
    ChannelException(int _errorCode, const std::string& _msg)
      : m_errorCode(_errorCode), m_msg(_msg){};

    virtual int errorCode() { return m_errorCode; };
    virtual const char* what() const noexcept override { return m_msg.c_str(); };

    bool operator!() const { return m_errorCode == 0; }

private:
    int m_errorCode = 0;
    std::string m_msg = "";
};

}  // namespace channel

}  // namespace dev
