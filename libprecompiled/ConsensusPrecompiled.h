
#pragma once
#include "Common.h"
namespace dev
{
namespace precompiled
{
/// \brief Sign of the sealer is valid or not
const char* const NODE_TYPE = "type";
const char* const NODE_TYPE_SEALER = "sealer";
const char* const NODE_TYPE_OBSERVER = "observer";
const char* const NODE_KEY_NODEID = "node_id";
const char* const NODE_KEY_ENABLENUM = "enable_num";
const char* const PRI_COLUMN = "name";
const char* const PRI_KEY = "node";

class ConsensusPrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<ConsensusPrecompiled> Ptr;
    ConsensusPrecompiled();
    virtual ~ConsensusPrecompiled(){};

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& _sender = Address()) override;

private:
    void showConsensusTable(std::shared_ptr<dev::blockverifier::ExecutiveContext> context);
    bool checkIsLastSealer(std::shared_ptr<storage::Table> table, std::string const& nodeID);
};

}  // namespace precompiled

}  // namespace dev
