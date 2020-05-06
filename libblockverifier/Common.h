

#pragma once


#include <libdevcore/Common.h>
#include <libdevcore/CommonData.h>
#include <libdevcore/FixedHash.h>
#include <memory>

#define BLOCKVERIFIER_LOG(LEVEL) LOG(LEVEL) << LOG_BADGE("BLOCKVERIFIER")
#define EXECUTIVECONTEXT_LOG(LEVEL) LOG(LEVEL) << LOG_BADGE("EXECUTIVECONTEXT")
#define PARA_LOG(LEVEL) LOG(LEVEL) << LOG_BADGE("PARA") << LOG_BADGE(utcTime())

namespace dev
{
namespace blockverifier
{
struct BlockInfo
{
    dev::h256 hash;
    int64_t number;
    dev::h256 stateRoot;
};
}  // namespace blockverifier
}  // namespace dev
