
#pragma once

#include <libdevcore/Exceptions.h>
#include <libdevcrypto/Common.h>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#define INITIALIZER_LOG(LEVEL) LOG(LEVEL) << "[INITIALIZER]"
#define ERROR_OUTPUT std::cout << "[INITIALIZER]"

namespace dev
{
DEV_SIMPLE_EXCEPTION(InvalidListenPort);
DEV_SIMPLE_EXCEPTION(ListenPortIsUsed);
DEV_SIMPLE_EXCEPTION(ConfigNotExist);
DEV_SIMPLE_EXCEPTION(InvalidConfig);
DEV_SIMPLE_EXCEPTION(InitFailed);
namespace initializer
{
inline bool isValidPort(int port)
{
    if (port <= 1024 || port > 65535)
        return false;
    return true;
}
}  // namespace initializer
}  // namespace dev
