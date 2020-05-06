


#include "BasicLevelDB.h"

using namespace dev;
using namespace dev::db;
using namespace std;

inline leveldb::Slice toLDBSlice(Slice _slice)
{
    return leveldb::Slice(_slice.data(), _slice.size());
}

void LevelDBWriteBatch::insert(Slice _key, Slice _value)
{
    this->insertSlice(toLDBSlice(_key), toLDBSlice(_value));
}

/*
void LevelDBWriteBatch::append(const LevelDBWriteBatch& _batch)
{
    m_writeBatch.Append(_batch.writeBatch());
}
*/

void LevelDBWriteBatch::insertSlice(const leveldb::Slice& _key, const leveldb::Slice& _value)
{
    dev::WriteGuard l(x_writeBatch);
    m_writeBatch.Put(_key, _value);
}

void LevelDBWriteBatch::kill(Slice _key)
{
    m_writeBatch.Delete(toLDBSlice(_key));
}

BasicLevelDB::BasicLevelDB(const leveldb::Options& _options, const std::string& _name)
  : m_name(_name)
{
    // Basic leveldb initralization(No encryption)
    auto db = static_cast<leveldb::DB*>(nullptr);
    m_openStatus = leveldb::DB::Open(_options, _name, &db);

    if (!m_openStatus.ok() || !db)
    {
        std::stringstream exitInfo;
        exitInfo << "Database open error"
                 << ", path=" << _name << ", error_info=" << m_openStatus.ToString() << endl;
        errorExit(exitInfo, OpenDBFailed());
    }
    m_db.reset(db);

    if (!empty())
    {
        // If the DB is encrypted. Exit
        std::string key;
        leveldb::Status status =
            m_db->Get(leveldb::ReadOptions(), leveldb::Slice(c_cipherDataKeyName), &key);
        if (!key.empty())
        {
            std::stringstream exitInfo;
            exitInfo << "[ENCDB] Database is encrypted" << endl;
            errorExit(exitInfo, EncryptedDB());
        }
    }
}

leveldb::Status BasicLevelDB::Open(
    const leveldb::Options& _options, const std::string& _name, BasicLevelDB** _dbptr)
{
    *_dbptr = new BasicLevelDB(_options, _name);
    leveldb::Status status = (*_dbptr)->OpenStatus();

    if (!status.ok())
    {
        if (*_dbptr != NULL)
            delete *_dbptr;
        *_dbptr = NULL;
    }

    return status;
}

leveldb::Status BasicLevelDB::Write(
    const leveldb::WriteOptions& _options, leveldb::WriteBatch* _updates)
{
    if (!m_db)
        return leveldb::Status::IOError(leveldb::Slice("DB not open"));
    return m_db->Write(_options, _updates);
}

leveldb::Status BasicLevelDB::Get(
    const leveldb::ReadOptions& _options, const leveldb::Slice& _key, std::string* _value)
{
    if (!m_db)
        return leveldb::Status::IOError(leveldb::Slice("DB not open"));
    return m_db->Get(_options, _key, _value);
}
leveldb::Status BasicLevelDB::Put(
    const leveldb::WriteOptions& _options, const leveldb::Slice& _key, const leveldb::Slice& _value)
{
    if (!m_db)
        return leveldb::Status::IOError(leveldb::Slice("DB not open"));
    return m_db->Put(_options, _key, _value);
}

leveldb::Status BasicLevelDB::Delete(
    const leveldb::WriteOptions& _options, const leveldb::Slice& _key)
{
    if (!m_db)
        return leveldb::Status::IOError(leveldb::Slice("DB not open"));
    return m_db->Delete(_options, _key);
}

leveldb::Iterator* BasicLevelDB::NewIterator(const leveldb::ReadOptions& _options)
{
    if (!m_db)
        return NULL;
    return m_db->NewIterator(_options);
}

std::unique_ptr<LevelDBWriteBatch> BasicLevelDB::createWriteBatch() const
{
    return std::unique_ptr<LevelDBWriteBatch>(new LevelDBWriteBatch());
}

bool BasicLevelDB::empty()
{
    if (!m_db)
        BOOST_THROW_EXCEPTION(DBNotOpened() << errinfo_comment(
                                  "LevelDB not opened before calling function: empty()"));

    leveldb::Iterator* it = m_db->NewIterator(leveldb::ReadOptions());
    if (it == NULL)
        BOOST_THROW_EXCEPTION(
            DBNotOpened() << errinfo_comment("LevelDB not opened before getting iterator"));

    it->SeekToFirst();
    bool isEmpty = !it->Valid();
    delete it;
    return isEmpty;
}