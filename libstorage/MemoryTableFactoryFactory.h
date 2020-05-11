 
/** @file MemoryTableFactoryFactory.h
 *  @author ancelmo
 *  @date 20190328
 */

#pragma once

#include "MemoryTableFactory.h"
#include "Storage.h"
#include "Table.h"
#include <libdevcore/FixedHash.h>

namespace dev
{
namespace storage
{
class MemoryTableFactoryFactory : public TableFactoryFactory
{
public:
    TableFactory::Ptr newTableFactory(dev::h256 const& hash, int64_t number) override
    {
        MemoryTableFactory::Ptr tableFactory = std::make_shared<MemoryTableFactory>();
        tableFactory->setStateStorage(m_stroage);
        tableFactory->setBlockHash(hash);
        tableFactory->setBlockNum(number);

        return tableFactory;
    }

    void setStorage(dev::storage::Storage::Ptr storage) { m_stroage = storage; }

private:
    dev::storage::Storage::Ptr m_stroage;
};

}  // namespace storage

}  // namespace dev
