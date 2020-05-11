

#pragma once

#include "StateFace.h"
#include <libethcore/Common.h>
#include <libstorage/MemoryTableFactory.h>
#include <memory>

namespace dev
{
namespace executive
{
class StateFactoryInterface
{
public:
    using Ptr = std::shared_ptr<StateFactoryInterface>;

    StateFactoryInterface() = default;
    virtual ~StateFactoryInterface(){};
    virtual std::shared_ptr<StateFace> getState(
        h256 const& _root, std::shared_ptr<dev::storage::TableFactory> _factory) = 0;
};

}  // namespace executive
}  // namespace dev
