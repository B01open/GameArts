
#pragma once
#include <libdevcore/Common.h>
#include <libdevcore/Exceptions.h>

namespace dev
{
namespace consensus
{
enum RPBFTPacketType : byte
{
    RawPrepareResponsePacket = 0x05,
};

DEV_SIMPLE_EXCEPTION(RequestedRawPrepareNotFound);

}  // namespace consensus
}  // namespace dev