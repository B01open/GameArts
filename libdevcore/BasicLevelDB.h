

#pragma once

#include "db.h"
#include <leveldb/db.h>
#include <leveldb/status.h>
#include <leveldb/write_batch.h>
#include <libdevcore/Guards.h>
#include <memory>
#include <string>

namespace dev
{
namespace db
{
class LevelDBWriteBatch : public WriteBatchFace
{
public:
    void insert(Slice _key, Slice _value) override;
    void kill(Slice _key) override;
    // void append(const LevelDBWriteBatch& _batch);
    const leveldb::WriteBatch& writeBatch() const { return m_writeBatch; }
    leveldb::WriteBatch& writeBatch() { return m_writeBatch; }

    // For Encrypted level DB
    virtual void insertSlice(const leveldb::Slice& _key, const leveldb::Slice& _value);

protected:
    leveldb::WriteBatch m_writeBatch;
    dev::SharedMutex x_writeBatch;
};

class BasicLevelDB
{
public:
    BasicLevelDB() {}
    BasicLevelDB(const leveldb::Options& _options, const std::string& _name);
    virtual ~BasicLevelDB(){};

    static leveldb::Status Open(
        const leveldb::Options& _options, const std::string& _name, BasicLevelDB** _dbptr);

    virtual leveldb::Status Write(
        const leveldb::WriteOptions& _options, leveldb::WriteBatch* _updates);

    virtual leveldb::Status Get(
        const leveldb::ReadOptions& _options, const leveldb::Slice& _key, std::string* _value);

    virtual leveldb::Status Put(const leveldb::WriteOptions& _options, const leveldb::Slice& _key,
        const leveldb::Slice& _value);

    virtual leveldb::Status Delete(
        const leveldb::WriteOptions& _options, const leveldb::Slice& _key);

    virtual leveldb::Iterator* NewIterator(const leveldb::ReadOptions& _options);

    virtual std::unique_ptr<LevelDBWriteBatch> createWriteBatch() const;

    leveldb::Status OpenStatus() { return m_openStatus; }

    bool empty();

protected:
    std::shared_ptr<leveldb::DB> m_db;
    leveldb::Status m_openStatus;
    std::string m_name;
};
}  // namespace db
}  // namespace dev
