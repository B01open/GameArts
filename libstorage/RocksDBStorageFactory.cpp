 
/** @file RocksDBStorageFactory.h
 *  @author xingqiangbai
 *  @date 20180423
 */

#include "RocksDBStorageFactory.h"
#include "BasicRocksDB.h"
#include "RocksDBStorage.h"
#include "libdevcore/Guards.h"
#include <boost/filesystem.hpp>

using namespace std;
using namespace dev;
using namespace dev::storage;

void RocksDBStorageFactory::setDBOpitons(rocksdb::Options _options)
{
    m_options = _options;
}

Storage::Ptr RocksDBStorageFactory::getStorage(const std::string& _dbName, bool _createIfMissing)
{
    auto dbName = m_DBPath + "/" + _dbName;
    if (!_createIfMissing && !boost::filesystem::exists(dbName))
    {
        return nullptr;
    }
    boost::filesystem::create_directories(dbName);

    RecursiveGuard l(x_cache);
    if (m_cache.first == dbName)
    {
        return m_cache.second;
    }
    std::shared_ptr<BasicRocksDB> rocksDB = std::make_shared<BasicRocksDB>();
    rocksDB->Open(m_options, dbName);
    std::shared_ptr<RocksDBStorage> rocksdbStorage =
        std::make_shared<RocksDBStorage>(m_disableWAL, m_completeDirty);
    rocksdbStorage->setDB(rocksDB);
    m_cache = make_pair(dbName, rocksdbStorage);
    return rocksdbStorage;
}
