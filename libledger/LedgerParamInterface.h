
#pragma once
#include <libdevcrypto/Common.h>
#include <libethcore/Common.h>
#include <memory>
#include <vector>
namespace dev
{
namespace blockchain
{
struct GenesisBlockParam;
}
namespace ledger
{
/// forward class declaration
struct TxPoolParam;
struct ConsensusParam;
struct BlockChainParam;
struct SyncParam;
struct P2pParam;
/// struct GenesisParam;
struct GenesisParam;
struct AMDBParam;
struct StorageParam;
struct StateParam;
struct TxParam;
struct EventLogFilterManagerParams;

class LedgerParamInterface
{
public:
    LedgerParamInterface() = default;
    virtual ~LedgerParamInterface() {}
    virtual TxPoolParam& mutableTxPoolParam() = 0;
    virtual ConsensusParam& mutableConsensusParam() = 0;
    virtual SyncParam& mutableSyncParam() = 0;
    virtual GenesisParam& mutableGenesisParam() = 0;
    virtual AMDBParam& mutableAMDBParam() = 0;
    virtual std::string const& baseDir() const = 0;
    virtual void setBaseDir(std::string const& baseDir) = 0;
    virtual StorageParam& mutableStorageParam() = 0;
    virtual StateParam& mutableStateParam() = 0;
    virtual TxParam& mutableTxParam() = 0;
    virtual EventLogFilterManagerParams& mutableEventLogFilterManagerParams() = 0;
    virtual blockchain::GenesisBlockParam& mutableGenesisBlockParam() = 0;
};
}  // namespace ledger
}  // namespace dev
