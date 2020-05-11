/**
 
 *
 * @file JsonHelper.h
 * @author: caryliao
 * @date 2018-10-26
 */
#pragma once

#include <json/json.h>
#include <libethcore/Common.h>

namespace dev
{
namespace rpc
{
Json::Value toJson(dev::eth::Transaction const& _t, std::pair<h256, unsigned> _location,
    dev::eth::BlockNumber _blockNumber);
dev::eth::TransactionSkeleton toTransactionSkeleton(Json::Value const& _json);

}  // namespace rpc

}  // namespace dev
