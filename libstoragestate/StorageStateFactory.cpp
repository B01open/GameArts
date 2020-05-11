 

/**
 * @brief : StorageStateFactory
 * @author: xingqiangbai
 * @date: 2018-10-26
 */

#include "StorageStateFactory.h"
#include "StorageState.h"

using namespace std;
using namespace dev;
using namespace dev::storagestate;
using namespace dev::executive;
std::shared_ptr<StateFace> StorageStateFactory::getState(
    h256 const&, std::shared_ptr<dev::storage::TableFactory> _factory)
{
    auto storageState = make_shared<StorageState>(m_accountStartNonce);
    storageState->setMemoryTableFactory(_factory);
    return storageState;
}
