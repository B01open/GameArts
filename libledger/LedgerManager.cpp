
#include "LedgerManager.h"
#include <algorithm>

namespace dev
{
namespace ledger
{
std::set<dev::GROUP_ID> LedgerManager::getGroupListForRpc() const
{
    std::set<dev::GROUP_ID> groupList;
    for (auto const& ledger : m_ledgerMap)
    {
        // check sealer list
        auto sealerList = ledger.second->blockChain()->sealerList();
        auto it_sealer = find(sealerList.begin(), sealerList.end(), ledger.second->keyPair().pub());
        if (it_sealer != sealerList.end())
        {
            groupList.insert(ledger.second->groupId());
            continue;
        }
        /// check observer list
        auto observerList = ledger.second->blockChain()->observerList();
        auto it_observer =
            find(observerList.begin(), observerList.end(), ledger.second->keyPair().pub());
        if (it_observer != observerList.end())
        {
            groupList.insert(ledger.second->groupId());
        }
    }
    return groupList;
}
}  // namespace ledger
}  // namespace dev
