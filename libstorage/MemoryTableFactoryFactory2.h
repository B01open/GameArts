 
/** @file MemoryTableFactoryFactory.h
 *  @author ancelmo
 *  @date 20190328
 */

#pragma once

#include "MemoryTableFactory2.h"
#include "Storage.h"
#include "Table.h"
#include <libdevcore/FixedHash.h>

namespace dev
{
namespace storage
{
class MemoryTableFactoryFactory2 : public TableFactoryFactory
{
public:
    TableFactory::Ptr newTableFactory(const dev::h256& hash, int64_t number) override
    {
        MemoryTableFactory2::Ptr tableFactory = std::make_shared<MemoryTableFactory2>();
        tableFactory->setStateStorage(m_stroage);
        tableFactory->setBlockHash(hash);
        tableFactory->setBlockNum(number);
        // TODO: check if need handle exception
        tableFactory->init();

        return tableFactory;
    }

    void setStorage(dev::storage::Storage::Ptr storage) { m_stroage = storage; }

private:
    dev::storage::Storage::Ptr m_stroage;
};

}  // namespace storage

}  // namespace dev
