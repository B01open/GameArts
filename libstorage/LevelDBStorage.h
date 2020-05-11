 
/** @file SealerPrecompiled.h
 *  @author ancelmo
 *  @date 20180921
 */
#pragma once

#include "Storage.h"
#include "StorageException.h"
#include "Table.h"
#include <json/json.h>
#include <leveldb/db.h>
#include <libdevcore/BasicLevelDB.h>
#include <libdevcore/FixedHash.h>
#include <libdevcore/Guards.h>

namespace dev
{
namespace storage
{
class LevelDBStorage : public Storage
{
public:
    typedef std::shared_ptr<LevelDBStorage> Ptr;

    virtual ~LevelDBStorage(){};

    Entries::Ptr select(int64_t num, TableInfo::Ptr tableInfo, const std::string& key,
        Condition::Ptr condition = nullptr) override;
    size_t commit(int64_t num, const std::vector<TableData::Ptr>& datas) override;

    void setDB(std::shared_ptr<dev::db::BasicLevelDB> db);

private:
    size_t commitTableDataRange(std::shared_ptr<dev::db::LevelDBWriteBatch>& batch,
        TableData::Ptr tableData, int64_t num, size_t from, size_t to);
    std::shared_ptr<dev::db::BasicLevelDB> m_db;
    dev::SharedMutex m_remoteDBMutex;
};

}  // namespace storage

}  // namespace dev
