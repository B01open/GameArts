
#pragma once
#include "Common.h"
namespace dev
{
namespace precompiled
{
const char* const SYSTEM_CONFIG_KEY = "key";
const char* const SYSTEM_CONFIG_VALUE = "value";
const char* const SYSTEM_CONFIG_ENABLENUM = "enable_num";
const char* const SYSTEM_KEY_TX_COUNT_LIMIT = "tx_count_limit";
const char* const SYSTEM_INIT_VALUE_TX_COUNT_LIMIT = "1000";
const char* const SYSTEM_KEY_TX_GAS_LIMIT = "tx_gas_limit";

// system configuration for RPBFT
const char* const SYSTEM_KEY_RPBFT_EPOCH_SEALER_NUM = "rpbft_epoch_sealer_num";
const char* const SYSTEM_KEY_RPBFT_EPOCH_BLOCK_NUM = "rpbft_epoch_block_num";

const char* const SYSTEM_INIT_VALUE_TX_GAS_LIMIT = "300000000";

const int TX_COUNT_LIMIT_MIN = 1;
const int TX_GAS_LIMIT_MIN = 100000;

const int RPBFT_EPOCH_SEALER_NUM_MIN = 1;
const int RPBFT_EPOCH_BLOCK_NUM_MIN = 1;

#if 0
contract SystemConfigTable
{
    // Return 1 means successful setting, and 0 means cannot find the config key.
    function setValueByKey(string key, string value) public returns(int256);
}
#endif

class SystemConfigPrecompiled : public dev::precompiled::Precompiled
{
public:
    typedef std::shared_ptr<SystemConfigPrecompiled> Ptr;
    SystemConfigPrecompiled();
    virtual ~SystemConfigPrecompiled(){};

    bytes call(std::shared_ptr<dev::blockverifier::ExecutiveContext> context, bytesConstRef param,
        Address const& origin = Address(), Address const& _sender = Address()) override;

private:
    bool checkValueValid(std::string const& key, std::string const& value);
};

}  // namespace precompiled

}  // namespace dev
