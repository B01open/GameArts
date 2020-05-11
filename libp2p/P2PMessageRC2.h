

#pragma once

#include "P2PMessage.h"

namespace dev
{
namespace p2p
{
class P2PMessageRC2 : public P2PMessage
{
public:
    /// m_length(4bytes) + m_version(2bytes) + m_protocolID(2bytes) + m_groupID(2bytes) +
    /// m_packetType(2bytes) + m_seq(4bytes)
    const static size_t HEADER_LENGTH = 16;
    const static size_t MAX_LENGTH = 1024 * 1024;  ///< The maximum length of data is 1M.

    P2PMessageRC2()
    {
        m_buffer = std::make_shared<bytes>();
        m_cache = std::make_shared<bytes>();
    }
    bool isRequestPacket() override { return (m_protocolID > 0); }

    virtual ~P2PMessageRC2() {}
    void encode(bytes& buffer) override;
    /// < If the decoding is successful, the length of the decoded data is returned; otherwise, 0 is
    /// returned.
    ssize_t decode(const byte* buffer, size_t size) override;

    virtual void setVersion(VERSION_TYPE const& _version) { setField(m_version, _version); }
    virtual VERSION_TYPE version() const { return m_version; }

    uint32_t deliveredLength() override { return m_deliveredLength; }

protected:
    virtual void encode(std::shared_ptr<bytes> encodeBuffer);

    VERSION_TYPE m_version = 0;

private:
    /// compress the data to be sended
    bool compress(std::shared_ptr<bytes>);
    std::shared_ptr<dev::bytes> m_cache;
    // the packet length delivered by the network
    uint32_t m_deliveredLength = 0;
};
}  // namespace p2p
}  // namespace dev
