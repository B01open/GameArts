

#pragma once

#include "BoostLogInitializer.h"
#include "Common.h"
#include "InitializerInterface.h"
#include "LedgerInitializer.h"
#include "P2PInitializer.h"
#include "RPCInitializer.h"
#include "SecureInitializer.h"

namespace dev
{
namespace initializer
{
class Initializer : public InitializerInterface, public std::enable_shared_from_this<Initializer>
{
public:
    typedef std::shared_ptr<Initializer> Ptr;

    virtual ~Initializer();
    void init(std::string const& _path);

    SecureInitializer::Ptr secureInitializer() { return m_secureInitializer; }
    P2PInitializer::Ptr p2pInitializer() { return m_p2pInitializer; }
    LedgerInitializer::Ptr ledgerInitializer() { return m_ledgerInitializer; }
    RPCInitializer::Ptr rpcInitializer() { return m_rpcInitializer; }
    LogInitializer::Ptr logInitializer() { return m_logInitializer; }

private:
    LogInitializer::Ptr m_logInitializer;
    RPCInitializer::Ptr m_rpcInitializer;
    LedgerInitializer::Ptr m_ledgerInitializer;
    P2PInitializer::Ptr m_p2pInitializer;

    SecureInitializer::Ptr m_secureInitializer;
};

}  // namespace initializer

}  // namespace dev
