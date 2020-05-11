

#pragma once

#include "Common.h"
#include <libconfig/GlobalConfigure.h>

namespace dev
{
namespace initializer
{
void initGlobalConfig(const boost::property_tree::ptree& _pt);
uint32_t getVersionNumber(const std::string& _version);

}  // namespace initializer

void version();
}  // namespace dev
