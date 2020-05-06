

#include "TrieHash2.h"
#include "Log.h"
#include "TrieCommon.h"
#include "TrieDB.h"  // @TODO replace ASAP!
#include <tbb/parallel_for.h>
#include <mutex>


#define TRIEHASH_SESSION_LOG(LEVEL) \
    LOG(LEVEL) << "[TrieHash]"      \
               << "[line:" << __LINE__ << "]"

static const uint32_t MAX_CHILD_COUNT = 16;

namespace dev
{
h256 getHash256(const std::vector<dev::bytes>& _bytesCaches)
{
    if (_bytesCaches.empty())
    {
        return dev::sha3(bytes());
    }
    std::vector<dev::bytes> bytesCachesTemp;
    bytesCachesTemp.insert(bytesCachesTemp.end(),
        std::make_move_iterator(const_cast<std::vector<dev::bytes>&>(_bytesCaches).begin()),
        std::make_move_iterator(const_cast<std::vector<dev::bytes>&>(_bytesCaches).end()));

    while (bytesCachesTemp.size() > 1)
    {
        std::vector<dev::bytes> higherLevelList;
        int size = (bytesCachesTemp.size() + MAX_CHILD_COUNT - 1) / MAX_CHILD_COUNT;
        higherLevelList.resize(size);
        tbb::parallel_for(
            tbb::blocked_range<size_t>(0, size), [&](const tbb::blocked_range<size_t>& _r) {
                for (uint32_t i = _r.begin(); i < _r.end(); ++i)
                {
                    bytes byteValue;
                    for (uint32_t j = 0; j < MAX_CHILD_COUNT; j++)
                    {
                        uint32_t index = i * MAX_CHILD_COUNT + j;
                        if (index < bytesCachesTemp.size())
                        {
                            byteValue.insert(byteValue.end(), bytesCachesTemp[index].begin(),
                                bytesCachesTemp[index].end());
                        }
                    }
                    higherLevelList[i] = dev::sha3(byteValue).asBytes();
                }
            });
        bytesCachesTemp = std::move(higherLevelList);
    }
    return dev::sha3(bytesCachesTemp[0]);
}

void getMerkleProof(const std::vector<dev::bytes>& _bytesCaches,
    std::shared_ptr<std::map<std::string, std::vector<std::string>>> _parent2ChildList)
{
    if (_bytesCaches.empty())
    {
        return;
    }
    std::vector<dev::bytes> bytesCachesTemp;
    bytesCachesTemp.insert(bytesCachesTemp.end(),
        std::make_move_iterator(const_cast<std::vector<dev::bytes>&>(_bytesCaches).begin()),
        std::make_move_iterator(const_cast<std::vector<dev::bytes>&>(_bytesCaches).end()));
    std::mutex mapMutex;
    while (bytesCachesTemp.size() > 1)
    {
        std::vector<dev::bytes> higherLevelList;
        int size = (bytesCachesTemp.size() + MAX_CHILD_COUNT - 1) / MAX_CHILD_COUNT;
        higherLevelList.resize(size);
        tbb::parallel_for(
            tbb::blocked_range<size_t>(0, size), [&](const tbb::blocked_range<size_t>& _r) {
                for (uint32_t i = _r.begin(); i < _r.end(); ++i)
                {
                    bytes byteValue;
                    std::vector<dev::bytes> childList;
                    for (uint32_t j = 0; j < MAX_CHILD_COUNT; j++)
                    {
                        uint32_t index = i * MAX_CHILD_COUNT + j;
                        if (index < bytesCachesTemp.size())
                        {
                            byteValue.insert(byteValue.end(), bytesCachesTemp[index].begin(),
                                bytesCachesTemp[index].end());
                            childList.push_back(bytesCachesTemp[index]);
                        }
                    }
                    higherLevelList[i] = dev::sha3(byteValue).asBytes();
                    std::lock_guard<std::mutex> l(mapMutex);
                    std::string parentNode = toHex(higherLevelList[i]);
                    for (const auto& child : childList)
                    {
                        (*_parent2ChildList)[parentNode].emplace_back(toHex(child));
                    }
                }
            });
        bytesCachesTemp = std::move(higherLevelList);
    }

    (*_parent2ChildList)[toHex(dev::sha3(bytesCachesTemp[0]).asBytes())].push_back(
        toHex(bytesCachesTemp[0]));
}

}  // namespace dev
