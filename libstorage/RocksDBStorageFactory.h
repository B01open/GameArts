 
/** @file RocksDBStorageFactory.h
 *  @author xingqiangbai
 *  @date 20180423
 */
#pragma once

#include "Storage.h"
#include "rocksdb/options.h"

namespace rocksdb
{
class DB;
}
namespace dev
{
namespace storage
{
class RocksDBStorageFactory : public StorageFactory
{
public:
    RocksDBStorageFactory(const std::string& _dbPath, bool _disableWAL, bool _enableCompleteDirty)
      : m_DBPath(_dbPath), m_disableWAL(_disableWAL), m_completeDirty(_enableCompleteDirty)
    {}
    virtual ~RocksDBStorageFactory() {}
    void setDBOpitons(rocksdb::Options _options);
    Storage::Ptr getStorage(const std::string& _dbName, bool _createIfMissing = true) override;

private:
    const std::string m_DBPath;
    bool m_disableWAL = false;
    bool m_completeDirty = false;
    rocksdb::Options m_options;
    std::recursive_mutex x_cache;
    std::pair<std::string, Storage::Ptr> m_cache;
};
}  // namespace storage
}  // namespace dev
