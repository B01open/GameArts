

#pragma once

#include "Storage.h"

namespace dev
{
namespace storage
{
class BinLogHandler;
class BinaryLogStorage : public Storage
{
public:
    typedef std::shared_ptr<BinaryLogStorage> Ptr;
    BinaryLogStorage();

    virtual ~BinaryLogStorage();

    Entries::Ptr select(int64_t num, TableInfo::Ptr tableInfo, const std::string& key,
        Condition::Ptr condition = nullptr) override;

    size_t commit(int64_t num, const std::vector<TableData::Ptr>& datas) override;

    void setBackend(Storage::Ptr backend) { m_backend = backend; }
    virtual void setBinaryLogger(std::shared_ptr<BinLogHandler> _logger)
    {
        m_binaryLogger = _logger;
    }
    void stop() override;

private:
    Storage::Ptr m_backend;
    std::shared_ptr<BinLogHandler> m_binaryLogger = nullptr;
};

}  // namespace storage

}  // namespace dev
