


#include "P2PMessage.h"
#include "Common.h"

using namespace dev;
using namespace dev::p2p;

void P2PMessage::encode(bytes& buffer)
{
    buffer.clear();  ///< It is not allowed to be assembled outside.
    m_length = HEADER_LENGTH + m_buffer->size();

    uint32_t length = htonl(m_length);
    PROTOCOL_ID protocolID = htons(m_protocolID);
    PACKET_TYPE packetType = htons(m_packetType);
    uint32_t seq = htonl(m_seq);

    buffer.insert(buffer.end(), (byte*)&length, (byte*)&length + 4);
    buffer.insert(buffer.end(), (byte*)&protocolID, (byte*)&protocolID + 2);
    buffer.insert(buffer.end(), (byte*)&packetType, (byte*)&packetType + 2);
    buffer.insert(buffer.end(), (byte*)&seq, (byte*)&seq + 4);
    buffer.insert(buffer.end(), m_buffer->begin(), m_buffer->end());
}

ssize_t P2PMessage::decode(const byte* buffer, size_t size)
{
    if (size < HEADER_LENGTH)
    {
        return dev::network::PACKET_INCOMPLETE;
    }

    int32_t offset = 0;
    m_length = ntohl(*((uint32_t*)&buffer[offset]));

    /*if (m_length > MAX_LENGTH)
    {
        return PACKET_ERROR;
    }*/

    if (size < m_length)
    {
        return dev::network::PACKET_INCOMPLETE;
    }

    offset += 4;
    m_protocolID = ntohs(*((PROTOCOL_ID*)&buffer[offset]));
    offset += 2;
    m_packetType = ntohs(*((PACKET_TYPE*)&buffer[offset]));
    offset += 2;
    m_seq = ntohl(*((uint32_t*)&buffer[offset]));
    ///< TODO: assign to std::move
    m_buffer->assign(&buffer[HEADER_LENGTH], &buffer[HEADER_LENGTH] + m_length - HEADER_LENGTH);

    return m_length;
}
