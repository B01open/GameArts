

#pragma once
#include <libconfig/GlobalConfigure.h>
#include <stdint.h>
#include <iosfwd>

namespace dev
{
typedef int16_t GROUP_ID;
typedef uint16_t MODULE_ID;
typedef int32_t PROTOCOL_ID;
typedef uint16_t PACKET_TYPE;
typedef uint16_t VERSION_TYPE;
static const GROUP_ID maxGroupID = 32767;
namespace eth
{
enum ProtocolID
{
    AMOP = 1,
    Topic = 2,
    PBFT = 8,
    BlockSync = 9,
    TxPool = 10,
    Raft = 11
};

enum VersionFlag
{
    CompressFlag = 0x8000  /// compressFlag
};

enum ExtraIndex
{
    PBFTExtraData = 0,
    ExtraIndexNum
};

// check if groupID valid groupID
inline bool validGroupID(int _groupID)
{
    return _groupID > 0 && _groupID <= maxGroupID;
}

inline PROTOCOL_ID getGroupProtoclID(GROUP_ID groupID, MODULE_ID moduleID)
{
    if (groupID < 0)
        return 0;
    if (g_BCOSConfig.version() <= RC1_VERSION)
    {
        return (groupID << 8) | moduleID;
    }
    return (groupID << (8 * sizeof(MODULE_ID))) | moduleID;
}

inline std::pair<GROUP_ID, MODULE_ID> getGroupAndProtocol(PROTOCOL_ID id)
{
    ///< The base should be 1, not 2.
    if (g_BCOSConfig.version() <= RC1_VERSION)
    {
        int32_t high = (1 << 8) - 1;
        int32_t low = (1 << 8) - 1;
        return std::make_pair((id >> 8) & high, id & low);
    }
    else
    {
        int32_t high = (1 << (8 * sizeof(GROUP_ID))) - 1;
        int32_t low = (1 << (8 * sizeof(MODULE_ID))) - 1;
        return std::make_pair((id >> (8 * sizeof(MODULE_ID))) & high, id & low);
    }
}

}  // namespace eth
}  // namespace dev
