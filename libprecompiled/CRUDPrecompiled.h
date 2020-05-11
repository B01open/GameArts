
#pragma once
#include "Common.h"
#include "libstorage/Table.h"

namespace dev
{
namespace storage
{
class Table;
}

namespace precompiled
{
class CRUDPrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<CRUDPrecompiled> Ptr;
    CRUDPrecompiled();
    virtual ~CRUDPrecompiled(){};

    std::string toString() override;

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& _sender = Address()) override;

private:
    int parseEntry(const std::string& entryStr, storage::Entry::Ptr& entry);
    int parseCondition(const std::string& conditionStr, storage::Condition::Ptr& condition);
};

}  // namespace precompiled

}  // namespace dev
