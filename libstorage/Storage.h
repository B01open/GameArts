 
/** @file storage.h
 *  @author monan
 *  @date 20180921
 */
#pragma once

#include "Table.h"
#include <libdevcore/FixedHash.h>
#include <libethcore/Protocol.h>

namespace dev
{
namespace storage
{
class Storage : public std::enable_shared_from_this<Storage>
{
public:
    typedef std::shared_ptr<Storage> Ptr;

    virtual ~Storage(){};

    virtual Entries::Ptr select(int64_t num, TableInfo::Ptr tableInfo, const std::string& key,
        Condition::Ptr condition = nullptr) = 0;
    virtual size_t commit(int64_t num, const std::vector<TableData::Ptr>& datas) = 0;
    // Dicide if CachedStorage can commit modified part of Entries
    virtual bool onlyCommitDirty() { return false; };

    virtual void stop() {}
};

class StorageFactory : public std::enable_shared_from_this<StorageFactory>
{
public:
    typedef std::shared_ptr<StorageFactory> Ptr;
    virtual ~StorageFactory(){};
    virtual Storage::Ptr getStorage(const std::string& _dbName, bool _createIfMissing = false) = 0;
};

}  // namespace storage

}  // namespace dev
