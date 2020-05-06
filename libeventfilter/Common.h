

#pragma once

#include <libdevcore/Log.h>
#include <libethcore/LogEntry.h>
#include <libethcore/TransactionReceipt.h>

#define EVENT_LOG(LEVEL) LOG(LEVEL) << "[EVENT]"

namespace dev
{
namespace event
{
using MatchedLogEntry = std::pair<eth::LogEntry, eth::TransactionReceipt>;
using MatchedLogEntries = std::vector<MatchedLogEntry>;

enum ResponseCode
{
    SUCCESS = 0,
    PUSH_COMPLETED = 1,
    INVALID_PARAMS = -41000,
    INVALID_REQUEST = -41001,
    GROUP_NOT_EXIST = -41002,
    INVALID_REQUEST_RANGE = -41003,
    INVALID_RESPONSE = -41004,
    REQUST_TIMEOUT = -41005,
    UNKNOWN_ERROR = -41006
};
}  // namespace event
}  // namespace dev
