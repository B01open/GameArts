

#pragma once

#include "MPTState.h"
#include <libdevcore/OverlayDB.h>
#include <libexecutive/StateFactoryInterface.h>
#include <libstorage/Storage.h>
#include <boost/filesystem.hpp>

namespace dev
{
namespace mptstate
{
class MPTStateFactory : public dev::executive::StateFactoryInterface
{
public:
    MPTStateFactory(u256 const& _accountStartNonce, boost::filesystem::path const& _basePath,
        h256 const& _genesisHash, WithExisting _we)
      : m_accountStartNonce(_accountStartNonce), m_basePath(_basePath), m_genesisHash(_genesisHash)
    {
        m_db = MPTState::openDB(m_basePath, m_genesisHash, _we);
    };
    virtual ~MPTStateFactory(){};
    virtual std::shared_ptr<dev::executive::StateFace> getState(
        h256 const& _root, std::shared_ptr<dev::storage::TableFactory> _factory) override;

private:
    dev::OverlayDB m_db;
    u256 m_accountStartNonce;
    boost::filesystem::path m_basePath;
    h256 m_genesisHash;
};

}  // namespace mptstate

}  // namespace dev
