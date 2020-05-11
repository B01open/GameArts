 
/** @file Common.cpp
 *  @author bxq
 *  @date 20191218
 */
#include "Common.h"
#include "libconfig/GlobalConfigure.h"
#include <string>

using namespace std;
using namespace dev;
using namespace dev::storage;

bool dev::storage::isHashField(const std::string& _key)
{
    if (!_key.empty())
    {
        if (g_BCOSConfig.version() < RC3_VERSION)
        {
            return ((_key.substr(0, 1) != "_" && _key.substr(_key.size() - 1, 1) != "_") ||
                    (_key == STATUS));
        }
        return ((_key.substr(0, 1) != "_" && _key.substr(_key.size() - 1, 1) != "_"));
    }
    return false;
}
