

#pragma once

#include "Storage.h"
#include <atomic>

namespace dev
{
namespace storage
{
class ScalableStorage : public Storage
{
public:
    typedef std::shared_ptr<ScalableStorage> Ptr;
    explicit ScalableStorage(int64_t _scrollThreshold);

    virtual ~ScalableStorage();

    Entries::Ptr select(int64_t num, TableInfo::Ptr tableInfo, const std::string& key,
        Condition::Ptr condition = nullptr) override;

    size_t commit(int64_t num, const std::vector<TableData::Ptr>& datas) override;

    void setRemoteStorage(Storage::Ptr _remote) { m_remote = _remote; }
    void setStateStorage(Storage::Ptr _state) { m_state = _state; }
    void setArchiveStorage(Storage::Ptr _archive, int64_t _dbIndex)
    {
        m_archive = _archive;
        m_archiveDBName = _dbIndex;
    }
    void setStorageFactory(StorageFactory::Ptr _storageFactory)
    {
        m_storageFactory = _storageFactory;
    }
    int64_t setRemoteBlockNumber(int64_t _blockNumber);
    int64_t getRemoteBlockNumber() { return m_remoteBlockNumber.load(); }
    void stop() override;
    std::string getDBNameOfArchivedBlock(int64_t _blockNumber);

    bool isStateData(const std::string& _tableName);

private:
    Entries::Ptr selectFromArchive(int64_t num, TableInfo::Ptr tableInfo, const std::string& key,
        Condition::Ptr condition = nullptr);
    void separateData(const std::vector<TableData::Ptr>& datas,
        std::vector<TableData::Ptr>& stateData, std::vector<TableData::Ptr>& archiveData);
    TableData::Ptr getNumberToDBNameData(int64_t _blockNumber);
    Storage::Ptr m_remote = nullptr;
    Storage::Ptr m_state = nullptr;
    Storage::Ptr m_archive = nullptr;
    int64_t m_archiveDBName = -1;  ///< also the start block of DB
    std::mutex m_archiveMutex;
    StorageFactory::Ptr m_storageFactory = nullptr;
    const int64_t m_scrollThreshold;
    std::atomic<int64_t> m_remoteBlockNumber;
    const std::vector<std::string> m_archiveTables = {SYS_HASH_2_BLOCK, SYS_BLOCK_2_NONCES};
};
}  // namespace storage
}  // namespace dev
