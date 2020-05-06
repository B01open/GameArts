
#pragma once
#include "Common.h"

namespace dev
{
namespace consensus
{
class PBFTMsgFactory
{
public:
    using Ptr = std::shared_ptr<PBFTMsgFactory>;
    PBFTMsgFactory() = default;
    virtual ~PBFTMsgFactory() {}
    virtual PBFTMsgPacket::Ptr createPBFTMsgPacket() { return std::make_shared<PBFTMsgPacket>(); }
};

// create ttl-optimized pbftMsgPacket
class OPBFTMsgFactory : public PBFTMsgFactory
{
public:
    using Ptr = std::shared_ptr<OPBFTMsgFactory>;
    OPBFTMsgFactory() = default;
    virtual ~OPBFTMsgFactory() {}
    PBFTMsgPacket::Ptr createPBFTMsgPacket() override { return std::make_shared<OPBFTMsgPacket>(); }
};
}  // namespace consensus
}  // namespace dev